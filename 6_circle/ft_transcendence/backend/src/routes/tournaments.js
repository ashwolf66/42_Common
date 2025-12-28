const livechat = require('../websocket/livechat/livechat');

async function routes(fastify, options) {
    const db = fastify.db;
    const ErrorCodes = require('../utils/errorCodes');

    // Create tournament
    fastify.post('/', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const { name, max_players } = request.body;

        if (!name || !max_players) {
            return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.NAME_AND_MAX_PLAYERS_REQUIRED });
        }

        // Validate tournament name
        const { validateTournamentName } = require('../utils/sanitize');
        const nameValidation = validateTournamentName(name);
        if (!nameValidation.valid) {
            return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.INVALID_NAME });
        }

        // Validate max_players (must be power of 2)
        if (![2, 4, 8, 16].includes(max_players)) {
            return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.INVALID_MAX_PLAYERS });
        }

        try {
            const total_rounds = Math.log2(max_players);

            const result = db.prepare(`
                INSERT INTO tournaments (name, max_players, total_rounds, created_by)
                VALUES (?, ?, ?, ?)
            `).run(nameValidation.value, max_players, total_rounds, request.user.id);

            const tournament = db.prepare('SELECT * FROM tournaments WHERE id = ?').get(result.lastInsertRowid);

            // Broadcast tournament creation to livechat
            try {
                const handler = livechat.getHandler();
                if (handler) {
                    await handler.sendAll({
                        type: 'tournament',
                        action: 'created',
                        tournamentId: tournament.id,
                        name: tournament.name,
                        user: request.user.username,
                        createdBy: request.user.username,
                        url: `/tournament/${tournament.id}`
                    });
                }
            } catch (error) {
                console.error('Failed to broadcast tournament creation:', error);
            }

            return reply.status(201).send({ message: 'Tournament created', tournament });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.TOURNAMENTS.CREATE_TOURNAMENT_FAILED });
        }
    });

    // Get tournament by ID
    fastify.get('/:id', async (request, reply) => {
        try {
            const tournament = db.prepare(`
                SELECT t.*, u.username as creator_username
                FROM tournaments t
                LEFT JOIN users u ON t.created_by = u.id
                WHERE t.id = ?
            `).get(request.params.id);

            if (!tournament) {
                return reply.status(404).send({ errorCode: ErrorCodes.TOURNAMENTS.TOURNAMENT_NOT_FOUND });
            }

            // Try to get user ID from token if provided
            let userId = null;
            const authHeader = request.headers.authorization;
            if (authHeader) {
                const token = authHeader.replace('Bearer ', '');
                const jwt = require('jsonwebtoken');
                const JWT_SECRET = process.env.JWT_SECRET || 'your-secret-key';
                try {
                    const decoded = jwt.verify(token, JWT_SECRET);
                    userId = decoded.id;
                } catch (err) {
                    // Token invalid, but we don't block access
                }
            }

            // Check if current user is creator
            tournament.is_creator = userId && tournament.created_by === userId;

            // Get participants
            const participants = db.prepare(`
                SELECT tp.*, u.username, u.display_name,
                       CASE WHEN tp.user_id = ? THEN 1 ELSE 0 END as is_creator
                FROM tournament_participants tp
                LEFT JOIN users u ON tp.user_id = u.id
                WHERE tp.tournament_id = ?
                ORDER BY tp.seed
            `).all(tournament.created_by, request.params.id);

            tournament.participants = participants;

            // Get matches - include alias from tournament_participants
            const matches = db.prepare(`
                SELECT g.*,
                       u1.username as player1_username, u1.display_name as player1_display_name,
                       u2.username as player2_username, u2.display_name as player2_display_name,
                       tp1.alias as player1_alias,
                       tp2.alias as player2_alias
                FROM games g
                LEFT JOIN users u1 ON g.player1_id = u1.id
                LEFT JOIN users u2 ON g.player2_id = u2.id
                LEFT JOIN tournament_participants tp1 ON tp1.tournament_id = g.tournament_id AND tp1.user_id = g.player1_id
                LEFT JOIN tournament_participants tp2 ON tp2.tournament_id = g.tournament_id AND tp2.user_id = g.player2_id
                WHERE g.tournament_id = ?
                ORDER BY g.started_at
            `).all(request.params.id);

            return reply.send({ tournament, matches });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.TOURNAMENTS.FETCH_TOURNAMENT_FAILED });
        }
    });

    // Join tournament
    fastify.post('/:id/join', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const tournamentId = request.params.id;
        let alias = request.body?.alias || null;

        // Sanitize alias if provided
        if (alias) {
            const { sanitizeString } = require('../utils/sanitize');
            alias = sanitizeString(alias, 50);
            if (alias.length > 50) {
                return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.ALIAS_TOO_LONG });
            }
        }

        try {
            const tournament = db.prepare('SELECT * FROM tournaments WHERE id = ? AND status = ?').get(tournamentId, 'pending');

            if (!tournament) {
                return reply.status(404).send({ errorCode: ErrorCodes.TOURNAMENTS.TOURNAMENT_NOT_FOUND_OR_STARTED });
            }

            // Check participant count
            const count = db.prepare('SELECT COUNT(*) as count FROM tournament_participants WHERE tournament_id = ?').get(tournamentId);

            if (count.count >= tournament.max_players) {
                return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.TOURNAMENT_FULL });
            }

            // Check if already joined
            const existing = db.prepare('SELECT id FROM tournament_participants WHERE tournament_id = ? AND user_id = ?').get(tournamentId, request.user.id);

            if (existing) {
                return reply.status(409).send({ errorCode: ErrorCodes.TOURNAMENTS.ALREADY_JOINED });
            }

            // Add participant
            const seed = count.count + 1;
            db.prepare(`
                INSERT INTO tournament_participants (tournament_id, user_id, alias, seed)
                VALUES (?, ?, ?, ?)
            `).run(tournamentId, request.user.id, alias, seed);

            // Broadcast participant joined to livechat
            try {
                const handler = livechat.getHandler();
                if (handler) {
                    await handler.sendAll({
                        type: 'tournament',
                        action: 'joined',
                        tournamentId,
                        name: tournament.name,
                        username: request.user.username,
                        user: request.user.username,
                        url: `/tournament/${tournamentId}`
                    });
                }
            } catch (error) {
                console.error('Failed to broadcast participant joined:', error);
            }

            return reply.status(201).send({ message: 'Joined tournament' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.TOURNAMENTS.JOIN_TOURNAMENT_FAILED });
        }
    });

    // Join tournament with alias (no account)
    fastify.post('/:id/join-alias', async (request, reply) => {
        const { alias } = request.body;
        const tournamentId = request.params.id;

        if (!alias || alias.length < 2) {
            return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.ALIAS_REQUIRED });
        }

        // Sanitize alias input
        const { sanitizeString } = require('../utils/sanitize');
        const sanitizedAlias = sanitizeString(alias, 50);

        if (sanitizedAlias.length < 2 || sanitizedAlias.length > 50) {
            return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.INVALID_ALIAS_LENGTH });
        }

        try {
            const tournament = db.prepare('SELECT * FROM tournaments WHERE id = ? AND status = ?').get(tournamentId, 'pending');

            if (!tournament) {
                return reply.status(404).send({ errorCode: ErrorCodes.TOURNAMENTS.TOURNAMENT_NOT_FOUND_OR_STARTED });
            }

            const count = db.prepare('SELECT COUNT(*) as count FROM tournament_participants WHERE tournament_id = ?').get(tournamentId);

            if (count.count >= tournament.max_players) {
                return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.TOURNAMENT_FULL });
            }

            const seed = count.count + 1;
            db.prepare(`
                INSERT INTO tournament_participants (tournament_id, alias, seed)
                VALUES (?, ?, ?)
            `).run(tournamentId, sanitizedAlias, seed);

            return reply.status(201).send({ message: 'Joined tournament' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.TOURNAMENTS.JOIN_TOURNAMENT_FAILED });
        }
    });

    // Start tournament
    fastify.post('/:id/start', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const tournamentId = request.params.id;

        try {
            const tournament = db.prepare('SELECT * FROM tournaments WHERE id = ?').get(tournamentId);

            if (!tournament) {
                return reply.status(404).send({ errorCode: ErrorCodes.TOURNAMENTS.TOURNAMENT_NOT_FOUND });
            }

            if (tournament.created_by !== request.user.id) {
                return reply.status(403).send({ errorCode: ErrorCodes.TOURNAMENTS.NOT_CREATOR });
            }

            if (tournament.status !== 'pending') {
                return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.TOURNAMENT_ALREADY_STARTED });
            }

            const participants = db.prepare(`
                SELECT * FROM tournament_participants
                WHERE tournament_id = ?
                ORDER BY seed
            `).all(tournamentId);

            // Minimum players is 2 (allows for 1v1 tournament)
            if (participants.length < 2) {
                return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.NOT_ENOUGH_PLAYERS });
            }

            // Check if we have enough players for the tournament size
            if (participants.length < tournament.max_players) {
                return reply.status(400).send({ errorCode: ErrorCodes.TOURNAMENTS.NOT_ENOUGH_PLAYERS_FOR_MAX });
            }

            // Update tournament status
            db.prepare(`
                UPDATE tournaments 
                SET status = 'active', started_at = CURRENT_TIMESTAMP, current_round = 1 
                WHERE id = ?
            `).run(tournamentId);

            // Create first round matches
            const numMatches = Math.floor(participants.length / 2);
            for (let i = 0; i < numMatches; i++) {
                const player1 = participants[i * 2];
                const player2 = participants[i * 2 + 1];

                db.prepare(`
                    INSERT INTO games (player1_id, player2_id, game_mode, tournament_id, started_at)
                    VALUES (?, ?, 'remote', ?, CURRENT_TIMESTAMP)
                `).run(player1.user_id, player2.user_id, tournamentId);
            }

            return reply.send({ message: 'Tournament started', matches_created: numMatches });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.TOURNAMENTS.START_TOURNAMENT_FAILED });
        }
    });

    // Get all tournaments
    fastify.get('/', async (request, reply) => {
        const { status, limit = 20, offset = 0 } = request.query;

        try {
            let query = `
                SELECT t.*, u.username as creator_username,
                       (SELECT COUNT(*) FROM tournament_participants WHERE tournament_id = t.id) as participant_count
                FROM tournaments t
                LEFT JOIN users u ON t.created_by = u.id
            `;

            const params = [];

            if (status) {
                query += ` WHERE t.status = ?`;
                params.push(status);
            }

            query += ` ORDER BY t.created_at DESC LIMIT ? OFFSET ?`;
            params.push(parseInt(limit), parseInt(offset));

            const tournaments = db.prepare(query).all(...params);

            return reply.send({ tournaments });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.TOURNAMENTS.FETCH_TOURNAMENTS_FAILED });
        }
    });
}

module.exports = routes;
