async function routes(fastify, options) {
    const db = fastify.db;
    const { usersModel } = require('../models/users');
    const users = usersModel(db);
    const ErrorCodes = require('../utils/errorCodes');

    // Get current user profile
    fastify.get('/me', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        try {
            const user = users.findProfileById(request.user.id);
            if (!user) {
                return reply.status(404).send({ errorCode: ErrorCodes.USERS.USER_NOT_FOUND });
            }

            return reply.send({ user });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.USERS.FETCH_USER_FAILED });
        }
    });

    // Get user by ID
    fastify.get('/:id', async (request, reply) => {
        try {
            const user = users.findPublicProfileById(request.params.id);

            if (!user) {
                return reply.status(404).send({ errorCode: ErrorCodes.USERS.USER_NOT_FOUND });
            }

            return reply.send({ user });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.USERS.FETCH_USER_FAILED });
        }
    });

    // Search users
    fastify.get('/search', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const { q } = request.query;

        if (!q || q.length < 2) {
            return reply.status(400).send({ errorCode: ErrorCodes.USERS.QUERY_TOO_SHORT });
        }

        try {
            // Sanitize search query to prevent SQL injection
            const { sanitizeString } = require('../utils/sanitize');
            const sanitizedQuery = sanitizeString(q, 50);

            // Escape special LIKE characters (%, _)
            const escapedQuery = sanitizedQuery.replace(/[%_]/g, '\\$&');

            const users = db.prepare(`
                SELECT id, username, display_name, is_online
                FROM users
                WHERE (username LIKE ? ESCAPE '\\' OR display_name LIKE ? ESCAPE '\\')
                AND id != ?
                LIMIT 20
            `).all(`%${escapedQuery}%`, `%${escapedQuery}%`, request.user.id);

            return reply.send({ users });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.USERS.SEARCH_FAILED });
        }
    });

    // Update profile
    fastify.put('/me', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const { display_name, email } = request.body;

        try {
            const updates = [];
            const values = [];

            // Whitelist allowed columns to prevent SQL injection
            const allowedUpdates = {
                'display_name': display_name,
                'email': email
            };

            if (display_name !== undefined) {
                // Validate display_name
                const { validateDisplayName } = require('../utils/sanitize');
                const validation = validateDisplayName(display_name);
                if (!validation.valid) {
                    return reply.status(400).send({ errorCode: ErrorCodes.USERS.INVALID_FIELD });
                }
                updates.push('display_name = ?');
                values.push(validation.value);
            }

            if (email !== undefined) {
                // Validate email
                const { validateEmail } = require('../utils/sanitize');
                const emailValidation = validateEmail(email);
                if (!emailValidation.valid) {
                    return reply.status(400).send({ errorCode: ErrorCodes.USERS.INVALID_FIELD });
                }

                // Check if email is taken
                const existing = db.prepare('SELECT id FROM users WHERE email = ? AND id != ?').get(emailValidation.value, request.user.id);
                if (existing) {
                    return reply.status(409).send({ errorCode: ErrorCodes.USERS.EMAIL_IN_USE });
                }
                updates.push('email = ?');
                values.push(emailValidation.value);
            }

            if (updates.length === 0) {
                return reply.status(400).send({ errorCode: ErrorCodes.USERS.NO_UPDATES_PROVIDED });
            }

            values.push(request.user.id);

            db.prepare(`UPDATE users SET ${updates.join(', ')} WHERE id = ?`).run(...values);

            const user = db.prepare('SELECT id, username, email, display_name FROM users WHERE id = ?').get(request.user.id);

            return reply.send({ message: 'Profile updated', user });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.USERS.UPDATE_FAILED });
        }
    });

    // Upload avatar
    fastify.post('/me/avatar', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        try {
            const data = await request.file();

            if (!data) {
                return reply.status(400).send({ errorCode: ErrorCodes.USERS.NO_FILE_UPLOADED });
            }

            // Validate file type
            const allowedTypes = ['image/jpeg', 'image/jpg', 'image/png', 'image/gif', 'image/webp'];
            if (!allowedTypes.includes(data.mimetype)) {
                return reply.status(400).send({ errorCode: ErrorCodes.USERS.INVALID_FILE_TYPE });
            }

            // Validate file size (5MB max)
            const buffer = await data.toBuffer();
            if (buffer.length > 5 * 1024 * 1024) {
                return reply.status(400).send({ errorCode: ErrorCodes.USERS.FILE_TOO_LARGE });
            }

            const fs = require('fs');
            const path = require('path');
            const crypto = require('crypto');

            // Generate unique filename
            const ext = data.filename.split('.').pop();
            const filename = `avatar-${request.user.id}-${crypto.randomBytes(8).toString('hex')}.${ext}`;
            const uploadsDir = path.join(__dirname, '../../uploads/avatars');
            const filepath = path.join(uploadsDir, filename);

            // Create directory if it doesn't exist
            if (!fs.existsSync(uploadsDir)) {
                fs.mkdirSync(uploadsDir, { recursive: true });
            }

            // Delete old avatar if exists
            const oldUser = db.prepare('SELECT avatar_url FROM users WHERE id = ?').get(request.user.id);
            if (oldUser && oldUser.avatar_url) {
                const oldFilename = oldUser.avatar_url.split('/').pop();
                const oldPath = path.join(uploadsDir, oldFilename);
                if (fs.existsSync(oldPath)) {
                    fs.unlinkSync(oldPath);
                }
            }

            // Save new avatar
            fs.writeFileSync(filepath, buffer);

            const avatar_url = `/uploads/avatars/${filename}`;

            // Update user record
            db.prepare('UPDATE users SET avatar_url = ? WHERE id = ?').run(avatar_url, request.user.id);

            return reply.send({ message: 'Avatar uploaded successfully', avatar_url });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.USERS.UPLOAD_AVATAR_FAILED });
        }
    });

    // Delete avatar
    fastify.delete('/me/avatar', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        try {
            const user = db.prepare('SELECT avatar_url FROM users WHERE id = ?').get(request.user.id);

            if (!user || !user.avatar_url) {
                return reply.status(404).send({ errorCode: ErrorCodes.USERS.NO_AVATAR_TO_DELETE });
            }

            const fs = require('fs');
            const path = require('path');

            // Delete file
            const filename = user.avatar_url.split('/').pop();
            const filepath = path.join(__dirname, '../../uploads/avatars', filename);
            if (fs.existsSync(filepath)) {
                fs.unlinkSync(filepath);
            }

            // Update user record
            db.prepare('UPDATE users SET avatar_url = NULL WHERE id = ?').run(request.user.id);

            return reply.send({ message: 'Avatar deleted successfully' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.USERS.DELETE_AVATAR_FAILED });
        }
    });

    // Get user stats
    fastify.get('/:id/stats', async (request, reply) => {
        try {
            let stats = db.prepare(`
                SELECT * FROM user_stats WHERE user_id = ?
            `).get(request.params.id);

            if (!stats) {
                stats = {
                    user_id: parseInt(request.params.id),
                    total_games: 0,
                    total_wins: 0,
                    total_losses: 0,
                    win_rate: 0,
                    highest_score: 0,
                    total_playtime_seconds: 0
                };
            }

            return reply.send({ stats });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.USERS.FETCH_STATS_FAILED });
        }
    });
}

module.exports = routes;
