async function routes(fastify, options) {
    const db = fastify.db;
    const { updateUserStats } = require('../utils/updateUserStats');
    const initBlockchain = require('../utils/initBlockchain');
    const blockchainService = require('../services/BlockchainService');
    const ErrorCodes = require('../utils/errorCodes');

    // Create game record
    fastify.post('/', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const { player1_id, player2_id, player1_score, player2_score, game_mode, difficulty, duration_seconds, tournament_id } = request.body;

        try {
            const winner_id = player1_score > player2_score ? player1_id : player2_id;

            const result = db.prepare(`
                INSERT INTO games (player1_id, player2_id, player1_score, player2_score, winner_id, game_mode, difficulty, duration_seconds, tournament_id, finished_at)
                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, CURRENT_TIMESTAMP)
            `).run(player1_id, player2_id, player1_score, player2_score, winner_id, game_mode, difficulty, duration_seconds, tournament_id);

            const game = db.prepare('SELECT * FROM games WHERE id = ?').get(result.lastInsertRowid);

            // Update user stats for remote and tournament games only
            if (game_mode === 'remote' || tournament_id) {
                updateUserStats(db, player1_id);
                if (player2_id) {
                    updateUserStats(db, player2_id);
                }

                // Record scores on blockchain if it's a tournament game
                if (tournament_id) {
                    // Ensure contract exists (deploy if missing) before recording
                    const contractAddress = await initBlockchain(db, { autoDeploy: true });

                    if (!contractAddress) {
                        console.warn('[Blockchain] No contract address available. Skipping on-chain recording.');
                        return reply.status(201).send({ message: 'Game created', game });
                    }

                    // Refresh service connection to pick up a newly set env/contract
                    blockchainService.connect(true);

                    // Since wallet_address was removed from users, we generate a deterministic address from user ID
                    // This allows us to track scores per user on-chain without requiring users to have real wallets.
                    // We use the ethers library to pad the ID to an address format.
                    const { ethers } = require('ethers');
                    
                    const getAddressFromId = (id) => {
                        return ethers.zeroPadValue(ethers.toBeHex(id), 20);
                    };

                    const p1Address = getAddressFromId(player1_id);
                    const p2Address = player2_id ? getAddressFromId(player2_id) : null;

                    // Record on-chain and persist transaction hash to blockchain_config
                    const saveTxHash = (key, hash) => {
                        if (!hash) return;
                        db.prepare(`INSERT OR REPLACE INTO blockchain_config (key, value) VALUES (?, ?)`).run(key, hash);
                    };

                    const tx1 = await blockchainService.recordGameScore(tournament_id, game.id, p1Address, player1_score);
                    saveTxHash(`game_${game.id}_player_${player1_id}_tx`, tx1);
                    
                    if (p2Address) {
                        const tx2 = await blockchainService.recordGameScore(tournament_id, game.id, p2Address, player2_score);
                        saveTxHash(`game_${game.id}_player_${player2_id}_tx`, tx2);
                    }
                }
            }

            // If tournament game, check if round is complete and create next round
            if (tournament_id) {
                const tournament = db.prepare('SELECT * FROM tournaments WHERE id = ?').get(tournament_id);
                
                if (tournament && tournament.status === 'active') {
                    // Get all finished games in current round
                    const currentRound = tournament.current_round;
                    const participants = db.prepare(`
                        SELECT COUNT(*) as count FROM tournament_participants WHERE tournament_id = ?
                    `).get(tournament_id);

                    // Calculate expected games in this round
                    const playersInRound = participants.count / Math.pow(2, currentRound - 1);
                    const expectedGamesInRound = playersInRound / 2;

                    // Get all games in tournament ordered by creation
                    const allGames = db.prepare(`
                        SELECT * FROM games WHERE tournament_id = ? ORDER BY id ASC
                    `).all(tournament_id);

                    // Calculate how many games should exist before current round
                    let gamesBeforeRound = 0;
                    for (let r = 1; r < currentRound; r++) {
                        const playersInPrevRound = participants.count / Math.pow(2, r - 1);
                        gamesBeforeRound += playersInPrevRound / 2;
                    }

                    // Get games in current round
                    const gamesInCurrentRound = allGames.slice(gamesBeforeRound, gamesBeforeRound + expectedGamesInRound);
                    const finishedGamesInRound = gamesInCurrentRound.filter(g => g.finished_at !== null);

                    console.log(`Tournament ${tournament_id} - Round ${currentRound}: ${finishedGamesInRound.length}/${expectedGamesInRound} games finished`);

                    // If current round is complete, create next round or finish tournament
                    if (finishedGamesInRound.length === expectedGamesInRound) {
                        if (expectedGamesInRound === 1) {
                            // This was the final game - tournament finished
                            db.prepare(`
                                UPDATE tournaments 
                                SET status = 'finished', winner_id = ?, finished_at = CURRENT_TIMESTAMP 
                                WHERE id = ?
                            `).run(winner_id, tournament_id);

                            console.log(`Tournament ${tournament_id} finished. Winner: ${winner_id}`);

                            if (fastify.livechat) {
                                fastify.livechat.broadcastTournament({
                                    action: 'finished',
                                    tournamentId: tournament_id,
                                    winnerId: winner_id,
                                    url: `/tournament/${tournament_id}`
                                });
                            }
                        } else {
                            // Create next round
                            const winners = finishedGamesInRound.map(g => g.winner_id);
                            const nextRound = currentRound + 1;

                            console.log(`Creating round ${nextRound} with ${winners.length} winners`);

                            // Create next round matches
                            for (let i = 0; i < winners.length / 2; i++) {
                                db.prepare(`
                                    INSERT INTO games (player1_id, player2_id, game_mode, tournament_id, started_at)
                                    VALUES (?, ?, 'remote', ?, CURRENT_TIMESTAMP)
                                `).run(winners[i * 2], winners[i * 2 + 1], tournament_id);
                            }

                            // Update tournament round
                            db.prepare(`
                                UPDATE tournaments SET current_round = ? WHERE id = ?
                            `).run(nextRound, tournament_id);

                            console.log(`Tournament ${tournament_id} advanced to round ${nextRound}`);

                            if (fastify.livechat) {
                                fastify.livechat.broadcastTournament({
                                    action: 'round_advanced',
                                    tournamentId: tournament_id,
                                    round: nextRound,
                                    url: `/tournament/${tournament_id}`
                                });
                            }
                        }
                    }
                }
            }

            return reply.status(201).send({ message: 'Game created', game });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.GAMES.CREATE_GAME_FAILED });
        }
    });

    // Get game by ID
    fastify.get('/:id', async (request, reply) => {
        try {
            const game = db.prepare(`
                SELECT g.*,
                       u1.username as player1_username, u1.display_name as player1_display_name,
                       u2.username as player2_username, u2.display_name as player2_display_name,
                       w.username as winner_username
                FROM games g
                LEFT JOIN users u1 ON g.player1_id = u1.id
                LEFT JOIN users u2 ON g.player2_id = u2.id
                LEFT JOIN users w ON g.winner_id = w.id
                WHERE g.id = ?
            `).get(request.params.id);

            if (!game) {
                return reply.status(404).send({ errorCode: ErrorCodes.GAMES.GAME_NOT_FOUND });
            }

            return reply.send({ game });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.GAMES.FETCH_GAME_FAILED });
        }
    });

    // Get user match history
    fastify.get('/user/:id', async (request, reply) => {
        const { limit = 20, offset = 0 } = request.query;

        try {
            const games = db.prepare(`
                SELECT g.*,
                       u1.username as player1_username, u1.display_name as player1_display_name,
                       u2.username as player2_username, u2.display_name as player2_display_name,
                       w.username as winner_username
                FROM games g
                LEFT JOIN users u1 ON g.player1_id = u1.id
                LEFT JOIN users u2 ON g.player2_id = u2.id
                LEFT JOIN users w ON g.winner_id = w.id
                WHERE g.player1_id = ? OR g.player2_id = ?
                ORDER BY g.finished_at DESC
                LIMIT ? OFFSET ?
            `).all(request.params.id, request.params.id, parseInt(limit), parseInt(offset));

            const total = db.prepare(`
                SELECT COUNT(*) as count FROM games WHERE player1_id = ? OR player2_id = ?
            `).get(request.params.id, request.params.id);

            return reply.send({ games, total: total.count });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.GAMES.FETCH_MATCH_HISTORY_FAILED });
        }
    });

    // Get recent games
    fastify.get('/recent', async (request, reply) => {
        const { limit = 10 } = request.query;

        try {
            const games = db.prepare(`
                SELECT g.*,
                       u1.username as player1_username, u1.display_name as player1_display_name,
                       u2.username as player2_username, u2.display_name as player2_display_name,
                       w.username as winner_username
                FROM games g
                LEFT JOIN users u1 ON g.player1_id = u1.id
                LEFT JOIN users u2 ON g.player2_id = u2.id
                LEFT JOIN users w ON g.winner_id = w.id
                WHERE g.finished_at IS NOT NULL
                ORDER BY g.finished_at DESC
                LIMIT ?
            `).all(parseInt(limit));

            return reply.send({ games });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.GAMES.FETCH_RECENT_GAMES_FAILED });
        }
    });
}

module.exports = routes;
