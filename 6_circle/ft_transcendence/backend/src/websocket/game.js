const { v4: uuidv4 } = require('uuid');
const { ethers } = require('ethers');
const { verifyToken } = require('../middleware/auth');
const livechat = require('./livechat/livechat');
const db = require('../config/database');
const { usersModel } = require('../models/users');
const { tournamentsModel } = require('../models/tournaments');
const { gamesModel } = require('../models/games');
const { tournamentParticipantsModel } = require('../models/tournament_participants');
const blockchainService = require('../services/BlockchainService');
const initBlockchain = require('../utils/initBlockchain');

const users = usersModel(db);
const tournaments = tournamentsModel(db);
const games = gamesModel(db);
const tournamentParticipants = tournamentParticipantsModel(db);

// Game rooms storage
const gameRooms = new Map();

// Game constants
const GAME_CONFIG = {
    WIDTH: 800,
    HEIGHT: 600,
    PADDLE_WIDTH: 10,
    PADDLE_HEIGHT: 100,
    BALL_SIZE: 10,
    PADDLE_SPEED: 8,
    BALL_SPEED: 5,
    WINNING_SCORE: 11,
    TICK_RATE: 1000 / 60, // 60 FPS
    // Custom game mode settings
    OBSTACLE_COUNT: 3,
    OBSTACLE_MIN_SIZE: 30,
    OBSTACLE_MAX_SIZE: 60,
    OBSTACLE_MIN_GAP: 80
};

class GameRoom {
    constructor(id, player1, tournamentId = null, matchId = null, roomName = null, gameMode = 'classic') {
        this.id = id;
        this.player1 = player1;
        this.player2 = null;
        this.state = 'waiting'; // waiting, playing, finished
        this.gameMode = gameMode; // 'classic' or 'custom'
        this.gameState = this.initGameState();
        this.lastUpdate = Date.now();
        this.startTime = null;
        this.gameLoop = null;
        this.tournamentId = tournamentId;
        this.matchId = matchId;
        this.roomName = roomName || 'Game Room';
    }

    initGameState() {
        const state = {
            ball: {
                x: GAME_CONFIG.WIDTH / 2,
                y: GAME_CONFIG.HEIGHT / 2,
                dx: GAME_CONFIG.BALL_SPEED / Math.sqrt(2),
                dy: GAME_CONFIG.BALL_SPEED / Math.sqrt(2)
            },
            paddle1: {
                y: GAME_CONFIG.HEIGHT / 2 - GAME_CONFIG.PADDLE_HEIGHT / 2,
                dy: 0
            },
            paddle2: {
                y: GAME_CONFIG.HEIGHT / 2 - GAME_CONFIG.PADDLE_HEIGHT / 2,
                dy: 0
            },
            score: {
                player1: 0,
                player2: 0
            },
            obstacles: []
        };

        // Generate obstacles for custom mode
        if (this.gameMode === 'custom') {
            state.obstacles = this.generateObstacles();
        }

        return state;
    }

    generateObstacles() {
        const obstacles = [];
        const centerX = GAME_CONFIG.WIDTH / 2;
        
        // Generate obstacles for left side (player 1)
        for (let i = 0; i < GAME_CONFIG.OBSTACLE_COUNT; i++) {
            const size = Math.random() * (GAME_CONFIG.OBSTACLE_MAX_SIZE - GAME_CONFIG.OBSTACLE_MIN_SIZE) + GAME_CONFIG.OBSTACLE_MIN_SIZE;
            const x = Math.random() * (centerX - GAME_CONFIG.OBSTACLE_MIN_GAP * 2 - GAME_CONFIG.PADDLE_WIDTH - size) + GAME_CONFIG.OBSTACLE_MIN_GAP + GAME_CONFIG.PADDLE_WIDTH;
            const y = Math.random() * (GAME_CONFIG.HEIGHT - size - GAME_CONFIG.OBSTACLE_MIN_GAP * 2) + GAME_CONFIG.OBSTACLE_MIN_GAP;
            obstacles.push({ x, y, width: size, height: size });
        }
        
        // Generate obstacles for right side (player 2) - random, not mirrored
        for (let i = 0; i < GAME_CONFIG.OBSTACLE_COUNT; i++) {
            const size = Math.random() * (GAME_CONFIG.OBSTACLE_MAX_SIZE - GAME_CONFIG.OBSTACLE_MIN_SIZE) + GAME_CONFIG.OBSTACLE_MIN_SIZE;
            const x = Math.random() * (centerX - GAME_CONFIG.OBSTACLE_MIN_GAP * 2 - GAME_CONFIG.PADDLE_WIDTH - size) + centerX + GAME_CONFIG.OBSTACLE_MIN_GAP;
            const y = Math.random() * (GAME_CONFIG.HEIGHT - size - GAME_CONFIG.OBSTACLE_MIN_GAP * 2) + GAME_CONFIG.OBSTACLE_MIN_GAP;
            obstacles.push({ x, y, width: size, height: size });
        }
        
        return obstacles;
    }

    async addPlayer2(player2) {
        this.player2 = player2;
        this.state = 'playing';
        this.startTime = Date.now();
        // Send game start with player positions and game mode
        this.player1.socket.send(JSON.stringify({
            type: 'gameStart',
            roomId: this.id,
            config: GAME_CONFIG,
            playerPosition: 'player1',
            opponentId: player2.userId,
            gameMode: this.gameMode,
            obstacles: this.gameState.obstacles
        }));
        this.player2.socket.send(JSON.stringify({
            type: 'gameStart',
            roomId: this.id,
            config: GAME_CONFIG,
            playerPosition: 'player2',
            opponentId: this.player1.userId,
            gameMode: this.gameMode,
            obstacles: this.gameState.obstacles
        }));
        // Broadcast tournament start to livechat if this is the first match
        if (this.tournamentId) {
            try {
                const tournament = tournaments.findById(this.tournamentId);

                if (tournament && tournament.current_round === 1) {
                    // Check if this is the first match to start
                    const startedMatches = games.countFinishedByTournamentId(this.tournamentId);

                    if (startedMatches.count === 0) {
                        const totalMatches = games.countByTournamentId(this.tournamentId);

                        // Get player names for this match
                        const player1Info = users.findUsernameById(this.player1.userId);
                        const player2Info = users.findUsernameById(this.player2.userId);

                        const handler = livechat.getHandler();
                        if (handler) {
                            await handler.sendAll({
                                type: 'tournament',
                                action: 'started',
                                tournamentId: this.tournamentId,
                                name: tournament.name,
                                tournamentName: tournament.name,
                                matchCount: totalMatches.count,
                                player1: player1Info?.username,
                                player2: player2Info?.username,
                                url: `/tournament/${this.tournamentId}`
                            });
                        }
                    }
                }
            } catch (error) {
                console.error('Failed to broadcast tournament start:', error);
            }
        }

        this.startGameLoop();
    }

    updatePaddleInput(playerId, direction) {
        // Only accept -1, 0, 1 as valid inputs
        if (direction !== '-1' && direction !== '0' && direction !== '1') {
            return;
        }
        if (playerId === this.player1.userId) {
            this.gameState.paddle1.dy = direction * GAME_CONFIG.PADDLE_SPEED;
        } else if (this.player2 && playerId === this.player2.userId) {
            this.gameState.paddle2.dy = direction * GAME_CONFIG.PADDLE_SPEED;
        }
    }

    update() {
        const gs = this.gameState;

        // Update paddle positions
        gs.paddle1.y += gs.paddle1.dy;
        gs.paddle2.y += gs.paddle2.dy;

        // Clamp paddles
        gs.paddle1.y = Math.max(0, Math.min(GAME_CONFIG.HEIGHT - GAME_CONFIG.PADDLE_HEIGHT, gs.paddle1.y));
        gs.paddle2.y = Math.max(0, Math.min(GAME_CONFIG.HEIGHT - GAME_CONFIG.PADDLE_HEIGHT, gs.paddle2.y));

        // Update ball position
        gs.ball.x += gs.ball.dx;
        gs.ball.y += gs.ball.dy;

        // Ball collision with obstacles (custom mode only) - Check FIRST
        if (this.gameMode === 'custom') {
            this.checkObstacleCollisions();
        }

        // Ball collision with top/bottom walls
        if (gs.ball.y <= 0 || gs.ball.y >= GAME_CONFIG.HEIGHT - GAME_CONFIG.BALL_SIZE) {
            gs.ball.dy = -gs.ball.dy;
            // Clamp position
            if (gs.ball.y <= 0) {
                gs.ball.y = 0;
            } else {
                gs.ball.y = GAME_CONFIG.HEIGHT - GAME_CONFIG.BALL_SIZE;
            }
        }

        // Ball collision with paddles
        // Left paddle
        if (gs.ball.x <= GAME_CONFIG.PADDLE_WIDTH &&
            gs.ball.y + GAME_CONFIG.BALL_SIZE >= gs.paddle1.y &&
            gs.ball.y <= gs.paddle1.y + GAME_CONFIG.PADDLE_HEIGHT) {
            const paddleCenter = gs.paddle1.y + GAME_CONFIG.PADDLE_HEIGHT / 2;
            const ballCenter = gs.ball.y + GAME_CONFIG.BALL_SIZE / 2;
            const offset = (ballCenter - paddleCenter) / (GAME_CONFIG.PADDLE_HEIGHT / 2);
            const angle = offset * (Math.PI / 4);
            
            gs.ball.dx = Math.abs(Math.cos(angle)) * GAME_CONFIG.BALL_SPEED;
            gs.ball.dy = Math.sin(angle) * GAME_CONFIG.BALL_SPEED;
            gs.ball.x = GAME_CONFIG.PADDLE_WIDTH;
        }

        // Right paddle
        if (gs.ball.x >= GAME_CONFIG.WIDTH - GAME_CONFIG.PADDLE_WIDTH - GAME_CONFIG.BALL_SIZE &&
            gs.ball.y + GAME_CONFIG.BALL_SIZE >= gs.paddle2.y &&
            gs.ball.y <= gs.paddle2.y + GAME_CONFIG.PADDLE_HEIGHT) {
            const paddleCenter = gs.paddle2.y + GAME_CONFIG.PADDLE_HEIGHT / 2;
            const ballCenter = gs.ball.y + GAME_CONFIG.BALL_SIZE / 2;
            const offset = (ballCenter - paddleCenter) / (GAME_CONFIG.PADDLE_HEIGHT / 2);
            const angle = offset * (Math.PI / 4);
            
            gs.ball.dx = -Math.abs(Math.cos(angle)) * GAME_CONFIG.BALL_SPEED;
            gs.ball.dy = Math.sin(angle) * GAME_CONFIG.BALL_SPEED;
            gs.ball.x = GAME_CONFIG.WIDTH - GAME_CONFIG.PADDLE_WIDTH - GAME_CONFIG.BALL_SIZE;
        }

        // Scoring
        if (gs.ball.x <= 0) {
            gs.score.player2++;
            this.resetBall();
        } else if (gs.ball.x >= GAME_CONFIG.WIDTH) {
            gs.score.player1++;
            this.resetBall();
        }

        // Check for winner
        if (gs.score.player1 >= GAME_CONFIG.WINNING_SCORE || gs.score.player2 >= GAME_CONFIG.WINNING_SCORE) {
            this.endGame();
        }
    }

    checkObstacleCollisions() {
        const gs = this.gameState;
        const margin = 1;
        
        for (const obstacle of gs.obstacles) {
            if (gs.ball.x < obstacle.x + obstacle.width + margin &&
                gs.ball.x + GAME_CONFIG.BALL_SIZE > obstacle.x - margin &&
                gs.ball.y < obstacle.y + obstacle.height + margin &&
                gs.ball.y + GAME_CONFIG.BALL_SIZE > obstacle.y - margin) {
                
                const ballCenterX = gs.ball.x + GAME_CONFIG.BALL_SIZE / 2;
                const ballCenterY = gs.ball.y + GAME_CONFIG.BALL_SIZE / 2;
                const obstacleCenterX = obstacle.x + obstacle.width / 2;
                const obstacleCenterY = obstacle.y + obstacle.height / 2;
                
                const overlapLeft = (gs.ball.x + GAME_CONFIG.BALL_SIZE) - obstacle.x;
                const overlapRight = (obstacle.x + obstacle.width) - gs.ball.x;
                const overlapTop = (gs.ball.y + GAME_CONFIG.BALL_SIZE) - obstacle.y;
                const overlapBottom = (obstacle.y + obstacle.height) - gs.ball.y;
                
                const minOverlap = Math.min(overlapLeft, overlapRight, overlapTop, overlapBottom);
                
                let hitHorizontal = false;
                if (minOverlap === overlapLeft || minOverlap === overlapRight) {
                    hitHorizontal = true;
                }
                
                if (hitHorizontal) {
                    if ((ballCenterX < obstacleCenterX && gs.ball.dx > 0) ||
                        (ballCenterX > obstacleCenterX && gs.ball.dx < 0)) {
                        gs.ball.dx = -gs.ball.dx;
                    }
                } else {
                    if ((ballCenterY < obstacleCenterY && gs.ball.dy > 0) ||
                        (ballCenterY > obstacleCenterY && gs.ball.dy < 0)) {
                        gs.ball.dy = -gs.ball.dy;
                    }
                }
                
                // Normalize speed
                const currentSpeed = Math.sqrt(gs.ball.dx * gs.ball.dx + gs.ball.dy * gs.ball.dy);
                if (currentSpeed > 0) {
                    gs.ball.dx = (gs.ball.dx / currentSpeed) * GAME_CONFIG.BALL_SPEED;
                    gs.ball.dy = (gs.ball.dy / currentSpeed) * GAME_CONFIG.BALL_SPEED;
                }
                
                // Push ball out
                const pushDistance = 2;
                if (minOverlap === overlapLeft) {
                    gs.ball.x = obstacle.x - GAME_CONFIG.BALL_SIZE - pushDistance;
                } else if (minOverlap === overlapRight) {
                    gs.ball.x = obstacle.x + obstacle.width + pushDistance;
                } else if (minOverlap === overlapTop) {
                    gs.ball.y = obstacle.y - GAME_CONFIG.BALL_SIZE - pushDistance;
                } else if (minOverlap === overlapBottom) {
                    gs.ball.y = obstacle.y + obstacle.height + pushDistance;
                }
                
                break;
            }
        }
    }

    resetBall() {
        const angle = (Math.random() * Math.PI / 3) - Math.PI / 6;
        const direction = Math.random() > 0.5 ? 1 : -1;
        
        let dx = Math.cos(angle) * direction;
        let dy = Math.sin(angle);
        
        const magnitude = Math.sqrt(dx * dx + dy * dy);
        if (magnitude > 0) {
            dx = (dx / magnitude) * GAME_CONFIG.BALL_SPEED;
            dy = (dy / magnitude) * GAME_CONFIG.BALL_SPEED;
        }
        
        this.gameState.ball = {
            x: GAME_CONFIG.WIDTH / 2,
            y: GAME_CONFIG.HEIGHT / 2,
            dx: dx,
            dy: dy
        };
    }

    startGameLoop() {
        this.gameLoop = setInterval(() => {
            this.update();
            this.broadcastState();
        }, GAME_CONFIG.TICK_RATE);
    }

    stopGameLoop() {
        if (this.gameLoop) {
            clearInterval(this.gameLoop);
            this.gameLoop = null;
        }
    }

    async recordGameOnBlockchain(gameId, p1Id, p2Id, p1Score, p2Score, p1Result, p2Result) {
        console.log(`[Game] Tournament game finished. Initiating blockchain recording for Tournament ${this.tournamentId}`);
        try {
            // Ensure contract exists (deploy if missing) before recording
            const contractAddress = await initBlockchain(db, { autoDeploy: true });
            console.log(`[Game] Blockchain contract address: ${contractAddress}`);

            if (contractAddress) {
                // Refresh service connection to pick up a newly set env/contract
                blockchainService.connect(true);

                const getAddressFromId = (id) => {
                    return ethers.zeroPadValue(ethers.toBeHex(id), 20);
                };

                const p1Address = getAddressFromId(p1Id);
                const p2Address = getAddressFromId(p2Id);

                // Get display names and format them
                const p1User = users.findById(p1Id);
                const p2User = users.findById(p2Id);
                const p1BaseName = p1User ? (p1User.display_name || p1User.username) : 'Unknown';
                const p2BaseName = p2User ? (p2User.display_name || p2User.username) : 'Unknown';

                const p1Name = `${p1BaseName} - ${p1Score} [${p1Result}]`;
                const p2Name = `${p2BaseName} - ${p2Score} [${p2Result}]`;

                // Record on-chain and persist transaction hash to blockchain_config
                const saveTxHash = (key, hash) => {
                    if (!hash) return;
                    db.prepare(`INSERT OR REPLACE INTO blockchain_config (key, value) VALUES (?, ?)`).run(key, hash);
                };

                console.log(`[Game] Recording blockchain score for Tournament ${this.tournamentId}, Game ${gameId}`);

                // Ensure gameId is valid
                if (!gameId) {
                    console.error('[Game] CRITICAL: gameId is undefined. Cannot record score on blockchain.');
                } else {
                    const tx1 = await blockchainService.recordGameScore(this.tournamentId, gameId, p1Address, p1Score, p1Name);
                    saveTxHash(`game_${gameId}_player_${p1Id}_tx`, tx1);
                    
                    const tx2 = await blockchainService.recordGameScore(this.tournamentId, gameId, p2Address, p2Score, p2Name);
                    saveTxHash(`game_${gameId}_player_${p2Id}_tx`, tx2);
                }
            } else {
                console.warn('[Game] No contract address available. Skipping on-chain recording.');
            }
        } catch (bcError) {
            console.error('[Game] Blockchain recording failed:', bcError);
        }
    }

    async endGame() {
        this.state = 'finished';
        this.stopGameLoop();
        const duration = Math.floor((Date.now() - this.startTime) / 1000);
        const winnerId = this.gameState.score.player1 > this.gameState.score.player2 ?
            this.player1.userId : this.player2.userId;

        // Send to player1 (IMMEDIATELY)
        this.player1.socket.send(JSON.stringify({
            type: 'gameEnd',
            winner: winnerId,
            score: this.gameState.score,
            duration,
            playerPosition: 'player1',
            opponentId: this.player2.userId
        }));

        // Send to player2 (IMMEDIATELY)
        this.player2.socket.send(JSON.stringify({
            type: 'gameEnd',
            winner: winnerId,
            score: this.gameState.score,
            duration,
            playerPosition: 'player2',
            opponentId: this.player1.userId
        }));

        // Save game result to database (server-side only, once per game)
        try {
            const { updateUserStats } = require('../utils/updateUserStats');
            let gameId;
            if (this.matchId) {
                // Update existing tournament match
                games.updateMatchResult({
                    matchId: this.matchId,
                    player1Score: this.gameState.score.player1,
                    player2Score: this.gameState.score.player2,
                    winnerId,
                    durationSeconds: duration
                });
                gameId = this.matchId;
                console.log('Tournament match result updated:', this.matchId);
            } else {
                // Insert new game record
                const result = games.insertGameResult({
                    player1Id: this.player1.userId,
                    player2Id: this.player2.userId,
                    player1Score: this.gameState.score.player1,
                    player2Score: this.gameState.score.player2,
                    winnerId,
                    durationSeconds: duration,
                    tournamentId: this.tournamentId
                });
                gameId = result.lastInsertRowid;
                console.log('Game result saved to database');
            }

            // Update stats for both players
            updateUserStats(db, this.player1.userId);
            updateUserStats(db, this.player2.userId);
            console.log('User stats updated');

            // Record scores on blockchain if it's a tournament game
            if (this.tournamentId) {
                const p1Score = this.gameState.score.player1;
                const p2Score = this.gameState.score.player2;
                const p1Result = p1Score > p2Score ? 'Win' : (p1Score < p2Score ? 'Lose' : 'Draw');
                const p2Result = p2Score > p1Score ? 'Win' : (p2Score < p1Score ? 'Lose' : 'Draw');

                // Fire and forget - do not await to prevent UI blocking
                this.recordGameOnBlockchain(gameId, this.player1.userId, this.player2.userId, p1Score, p2Score, p1Result, p2Result)
                    .catch(err => console.error('[Game] Background blockchain recording failed:', err));
            } else {
                console.log('[Game] Not a tournament game. Skipping blockchain recording.');
            }

            // Broadcast match result to livechat if it's a tournament match (BEFORE tournament progression)
            if (this.tournamentId) {
                try {
                    console.log('[Game] Attempting to broadcast match result for tournament:', this.tournamentId);
                    const handler = livechat.getHandler();
                    console.log('[Game] livechat handler available:', !!handler);

                    if (handler) {
                        const winner = users.findUsernameById(winnerId);
                        const tournament = tournaments.findById(this.tournamentId);
                        const player1Info = users.findUsernameById(this.player1.userId);
                        const player2Info = users.findUsernameById(this.player2.userId);

                        const winnerScore = this.gameState.score.player1 > this.gameState.score.player2
                            ? this.gameState.score.player1
                            : this.gameState.score.player2;
                        const loserScore = this.gameState.score.player1 > this.gameState.score.player2
                            ? this.gameState.score.player2
                            : this.gameState.score.player1;

                        console.log('[Game] Broadcasting match_finished:', {
                            winner: winner?.username,
                            tournamentName: tournament?.name
                        });

                        await handler.sendAll({
                            type: 'tournament',
                            action: 'match_finished',
                            tournamentId: this.tournamentId,
                            name: tournament?.name,
                            tournamentName: tournament?.name,
                            round: tournament?.current_round,
                            winner: winner?.username,
                            player1: player1Info?.username,
                            player2: player2Info?.username,
                            winnerScore: winnerScore,
                            loserScore: loserScore,
                            score: `${this.gameState.score.player1}-${this.gameState.score.player2}`,
                            url: `/tournament/${this.tournamentId}`
                        });
                    } else {
                        console.log('[Game] livechat handler not available yet');
                    }
                } catch (error) {
                    console.error('[Game] Failed to broadcast match result:', error);
                }
            }

            // Handle tournament progression (AFTER match result broadcast)
            if (this.tournamentId) {
                await this.handleTournamentProgression(db, winnerId);
            }
        } catch (error) {
            console.error('Failed to save game result:', error);
        }
    }

    broadcastState() {
        const message = {
            type: 'gameState',
            state: this.gameState,
            timestamp: Date.now()
        };

        this.player1.socket.send(JSON.stringify(message));
        if (this.player2) {
            this.player2.socket.send(JSON.stringify(message));
        }
    }

    broadcastMessage(message) {
        const msg = JSON.stringify(message);
        this.player1.socket.send(msg);
        if (this.player2) {
            this.player2.socket.send(msg);
        }
    }

    async handleTournamentProgression(db, winnerId) {
        try {
            const tournament = tournaments.findById(this.tournamentId);
            
            if (!tournament || tournament.status !== 'active') {
                return;
            }

            // Mark loser as eliminated
            const loserId = winnerId === this.player1.userId ? this.player2.userId : this.player1.userId;
            tournamentParticipants.markEliminated(this.tournamentId, loserId);

            // Get all games in tournament ordered by creation
            const allGames = games.findByTournamentId(this.tournamentId);

            const participants = tournamentParticipants.countByTournamentId(this.tournamentId);

            const currentRound = tournament.current_round;

            // Calculate expected games in this round
            const playersInRound = participants.count / Math.pow(2, currentRound - 1);
            const expectedGamesInRound = playersInRound / 2;

            // Calculate how many games should exist before current round
            let gamesBeforeRound = 0;
            for (let r = 1; r < currentRound; r++) {
                const playersInPrevRound = participants.count / Math.pow(2, r - 1);
                gamesBeforeRound += playersInPrevRound / 2;
            }

            // Get games in current round
            const gamesInCurrentRound = allGames.slice(gamesBeforeRound, gamesBeforeRound + expectedGamesInRound);
            const finishedGamesInRound = gamesInCurrentRound.filter(g => g.finished_at !== null);

            console.log(`Tournament ${this.tournamentId} - Round ${currentRound}: ${finishedGamesInRound.length}/${expectedGamesInRound} games finished`);

            // If current round is complete, create next round or finish tournament
            if (finishedGamesInRound.length === expectedGamesInRound) {
                if (expectedGamesInRound === 1) {
                    // This was the final game - tournament finished
                    tournaments.updateFinished(this.tournamentId, winnerId);

                    console.log(`Tournament ${this.tournamentId} finished. Winner: ${winnerId}`);

                    // Broadcast tournament winner to livechat
                    try {
                        const handler = livechat.getHandler();
                        if (handler) {
                            const winner = users.findUsernameById(winnerId);

                            await handler.sendAll({
                                type: 'tournament',
                                action: 'finished',
                                tournamentId: this.tournamentId,
                                name: tournament.name,
                                tournamentName: tournament.name,
                                winner: winner?.username,
                                url: `/tournament/${this.tournamentId}`
                            });
                        }
                    } catch (error) {
                        console.error('Failed to broadcast tournament winner:', error);
                    }
                } else {
                    // Create next round
                    const winners = finishedGamesInRound.map(g => g.winner_id);
                    const nextRound = currentRound + 1;

                    console.log(`Creating round ${nextRound} with ${winners.length} winners`);

                    // Create next round matches
                    for (let i = 0; i < winners.length / 2; i++) {
                        games.insertTournamentMatch({
                            player1Id: winners[i * 2],
                            player2Id: winners[i * 2 + 1],
                            tournamentId: this.tournamentId
                        });
                    }

                    // Update tournament round
                    tournaments.updateCurrentRound(this.tournamentId, nextRound);

                    console.log(`Tournament ${this.tournamentId} advanced to round ${nextRound}`);

                    // Broadcast round progression to livechat
                    try {
                        const handler = livechat.getHandler();
                        if (handler) {
                            await handler.sendAll({
                                type: 'tournament',
                                action: 'round_advanced',
                                tournamentId: this.tournamentId,
                                name: tournament.name,
                                tournamentName: tournament.name,
                                currentRound: nextRound,
                                totalRounds: tournament.total_rounds,
                                url: `/tournament/${this.tournamentId}`
                            });
                        }
                    } catch (error) {
                        console.error('Failed to broadcast round progression:', error);
                    }
                }
            }
        } catch (error) {
            console.error('Failed to handle tournament progression:', error);
        }
    }

    async removePlayer(socket) {
        this.stopGameLoop();
        
        let isPlayer1 = this.player1 && this.player1.socket === socket;
        let isPlayer2 = this.player2 && this.player2.socket === socket;
        
        // If game is in progress (both players exist), handle forfeit
        if (this.state === 'playing' && this.player1 && this.player2) {
            const leavingPlayer = isPlayer1 ? this.player1 : this.player2;
            const remainingPlayer = isPlayer1 ? this.player2 : this.player1;
            
            // Winner is the remaining player (forfeit win)
            // Keep current scores as they are, just determine winner by forfeit
            const winnerId = remainingPlayer.userId;
            const duration = Math.floor((Date.now() - this.startTime) / 1000);
            
            // Save game result to database
            try {
                const { updateUserStats } = require('../utils/updateUserStats');
                let gameId;
                
                if (this.matchId) {
                    // Update existing tournament match
                    games.updateMatchResult({
                        matchId: this.matchId,
                        player1Score: this.gameState.score.player1,
                        player2Score: this.gameState.score.player2,
                        winnerId,
                        durationSeconds: duration
                    });
                    gameId = this.matchId;
                    console.log('Tournament match result updated (forfeit):', this.matchId);
                } else {
                    // Insert new game record
                    const result = games.insertGameResult({
                        player1Id: this.player1.userId,
                        player2Id: this.player2.userId,
                        player1Score: this.gameState.score.player1,
                        player2Score: this.gameState.score.player2,
                        winnerId,
                        durationSeconds: duration,
                        tournamentId: this.tournamentId
                    });
                    gameId = result.lastInsertRowid;
                    console.log('Game result saved (forfeit)');
                }
                
                // Update stats for both players
                updateUserStats(db, this.player1.userId);
                updateUserStats(db, this.player2.userId);
                console.log('User stats updated after forfeit');

                // Record scores on blockchain if it's a tournament game (FORFEIT CASE)
                if (this.tournamentId) {
                    const p1Result = winnerId === this.player1.userId ? 'Win' : 'Lose';
                    const p2Result = winnerId === this.player2.userId ? 'Win' : 'Lose';
                    
                    // Fire and forget - do not await
                    this.recordGameOnBlockchain(gameId, this.player1.userId, this.player2.userId, this.gameState.score.player1, this.gameState.score.player2, p1Result, p2Result)
                        .catch(err => console.error('[Game] Background blockchain recording failed (Forfeit):', err));
                }
                
                // Handle tournament progression
                if (this.tournamentId) {
                    this.handleTournamentProgression(db, winnerId);
                }
            } catch (error) {
                console.error('Failed to save forfeit game result:', error);
            }
            
            // Notify remaining player with game end (they won)
            if (remainingPlayer && remainingPlayer.socket) {
                remainingPlayer.socket.send(JSON.stringify({ 
                    type: 'gameEnd',
                    winner: winnerId,
                    score: this.gameState.score,
                    duration,
                    playerPosition: isPlayer1 ? 'player2' : 'player1',
                    forfeit: true,
                    message: 'Opponent forfeited - You win!'
                }));
            }
            
            this.state = 'finished';
        } else {
            // Game not started yet, just notify
            if (isPlayer1 && this.player2) {
                this.player2.socket.send(JSON.stringify({ type: 'opponentDisconnected' }));
            } else if (isPlayer2 && this.player1) {
                this.player1.socket.send(JSON.stringify({ type: 'opponentDisconnected' }));
            }
        }
        
        // Remove player
        if (isPlayer1) {
            this.player1 = null;
        }
        if (isPlayer2) {
            this.player2 = null;
        }
    }
}

async function routes(fastify, options) {
    fastify.register(async function (fastify) {
        fastify.get('/', { websocket: true }, (connection, req) => {
            const socket = connection.socket;

            console.log('WebSocket connection established');

            let userId = null;
            let currentRoom = null;

            socket.on('message', (message) => {
                try {
                    const data = JSON.parse(message.toString());

                    switch (data.type) {
                        case 'auth':
                            // Authenticate user
                            const user = verifyToken(data.token);
                            if (!user) {
                                socket.send(JSON.stringify({ type: 'error', message: 'Invalid token' }));
                                socket.close();
                                return;
                            }
                            userId = user.id;
                            socket.send(JSON.stringify({ type: 'authenticated', userId }));
                            break;

                        case 'createRoom':
                            if (!userId) {
                                socket.send(JSON.stringify({ type: 'error', message: 'Not authenticated' }));
                                return;
                            }

                            const tournamentId = data.tournamentId || null;
                            const matchId = data.matchId || null;
                            const gameMode = data.gameMode || 'classic'; // Get gameMode from client
                            let roomName = data.roomName;

                            // If no room name provided, use creator's username
                            if (!roomName || roomName.trim() === '') {
                                try {
                                    const user = users.findUsernameById(userId);
                                    roomName = user ? user.username : 'Game Room';
                                } catch (error) {
                                    console.error('Failed to get username:', error);
                                    roomName = 'Game Room';
                                }
                            }

                            // For tournament matches, use match ID as room ID to ensure both players join same room
                            let roomId;
                            if (tournamentId && matchId) {
                                roomId = `tournament_${tournamentId}_match_${matchId}`;

                                // Check if room already exists
                                const existingRoom = gameRooms.get(roomId);
                                if (existingRoom) {
                                    if (existingRoom.state !== 'waiting') {
                                        socket.send(JSON.stringify({ type: 'error', message: 'Match already in progress' }));
                                        return;
                                    }
                                    // Join existing room as player 2
                                    existingRoom.addPlayer2({ userId, socket });
                                    currentRoom = existingRoom;
                                    break;
                                }
                            } else {
                                // Check if a room with this name already exists (from invite)
                                let existingRoomByName = null;
                                for (const room of gameRooms.values()) {
                                    if (room.roomName === roomName && room.state === 'waiting') {
                                        existingRoomByName = room;
                                        break;
                                    }
                                }

                                // If room exists, join it instead of creating new one
                                if (existingRoomByName) {
                                    existingRoomByName.addPlayer2({ userId, socket });
                                    currentRoom = existingRoomByName;
                                    break;
                                }

                                roomId = uuidv4();
                            }

                            const room = new GameRoom(roomId, { userId, socket }, tournamentId, matchId, roomName, gameMode);
                            gameRooms.set(roomId, room);
                            currentRoom = room;

                            socket.send(JSON.stringify({
                                type: 'roomCreated',
                                roomId,
                                config: GAME_CONFIG,
                                tournamentId,
                                matchId,
                                roomName: room.roomName,
                                gameMode: gameMode
                            }));
                            break;

                        case 'joinRoom':
                            if (!userId) {
                                socket.send(JSON.stringify({ type: 'error', message: 'Not authenticated' }));
                                return;
                            }

                            // Find room by ID or by name
                            let joinRoom = gameRooms.get(data.roomId);

                            // If not found by ID, try to find by room name
                            if (!joinRoom && data.roomName) {
                                for (const room of gameRooms.values()) {
                                    if (room.roomName === data.roomName) {
                                        joinRoom = room;
                                        break;
                                    }
                                }
                            }

                            if (!joinRoom) {
                                socket.send(JSON.stringify({ type: 'error', message: 'Room not found' }));
                                return;
                            }

                            if (joinRoom.state !== 'waiting') {
                                socket.send(JSON.stringify({ type: 'error', message: 'Room is full or game started' }));
                                return;
                            }

                            joinRoom.addPlayer2({ userId, socket });
                            currentRoom = joinRoom;
                            break;

                        case 'paddleMove':
                            if (currentRoom && currentRoom.state === 'playing') {
                                currentRoom.updatePaddleInput(userId, data.direction);
                            }
                            break;

                        case 'listRooms':
                            const rooms = Array.from(gameRooms.values())
                                .filter(r => r.state === 'waiting' && !r.tournamentId) // Exclude tournament rooms
                                .map(r => ({ 
                                    id: r.id, 
                                    players: 1,
                                    name: r.roomName 
                                }));
                            socket.send(JSON.stringify({ type: 'roomList', rooms }));
                            break;

                        default:
                            console.log('Unknown message type:', data.type);
                    }
                } catch (error) {
                    console.error('WebSocket message error:', error);
                    socket.send(JSON.stringify({ type: 'error', message: 'Invalid message format' }));
                }
            });

            socket.on('close', () => {
                console.log('WebSocket connection closed');
                if (currentRoom) {
                    currentRoom.removePlayer(socket);
                    
                    // Clean up empty rooms
                    if (!currentRoom.player1 && !currentRoom.player2) {
                        gameRooms.delete(currentRoom.id);
                    }
                }
            });

            socket.on('error', (error) => {
                console.error('WebSocket error:', error);
            });
        });
    });
}

module.exports = routes;
module.exports.getGameRooms = () => gameRooms;
