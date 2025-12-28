async function routes(fastify, options) {
    const db = fastify.db;
    const ErrorCodes = require('../utils/errorCodes');

    // Get friend list
    fastify.get('/', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        try {
            const friends = db.prepare(`
                SELECT u.id, u.username, u.display_name, u.avatar_url, u.is_online, f.status, f.created_at
                FROM friendships f
                JOIN users u ON (f.friend_id = u.id)
                WHERE f.user_id = ? AND f.status IN ('accepted', 'pending')
                UNION
                SELECT u.id, u.username, u.display_name, u.avatar_url, u.is_online, f.status, f.created_at
                FROM friendships f
                JOIN users u ON (f.user_id = u.id)
                WHERE f.friend_id = ? AND f.status = 'accepted'
            `).all(request.user.id, request.user.id);

            // Sort in JavaScript after fetching
            friends.sort((a, b) => new Date(b.created_at) - new Date(a.created_at));

            return reply.send({ friends });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.FRIENDS.FETCH_FRIENDS_FAILED });
        }
    });

    // Send friend request
    fastify.post('/request', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const { friend_id } = request.body;

        if (!friend_id) {
            return reply.status(400).send({ errorCode: ErrorCodes.FRIENDS.FRIEND_ID_REQUIRED });
        }

        if (friend_id === request.user.id) {
            return reply.status(400).send({ errorCode: ErrorCodes.FRIENDS.CANNOT_ADD_SELF });
        }

        try {
            // Check if user exists
            const friendExists = db.prepare('SELECT id FROM users WHERE id = ?').get(friend_id);
            if (!friendExists) {
                return reply.status(404).send({ errorCode: ErrorCodes.FRIENDS.USER_NOT_FOUND });
            }

            // Check if friendship already exists
            const existing = db.prepare(`
                SELECT id, status FROM friendships
                WHERE (user_id = ? AND friend_id = ?) OR (user_id = ? AND friend_id = ?)
            `).get(request.user.id, friend_id, friend_id, request.user.id);

            if (existing) {
                if (existing.status === 'pending') {
                    return reply.status(409).send({ errorCode: ErrorCodes.FRIENDS.FRIEND_REQUEST_PENDING });
                }
                if (existing.status === 'accepted') {
                    return reply.status(409).send({ errorCode: ErrorCodes.FRIENDS.ALREADY_FRIENDS });
                }
                if (existing.status === 'blocked') {
                    return reply.status(403).send({ errorCode: ErrorCodes.FRIENDS.CANNOT_SEND_REQUEST });
                }
            }

            // Create friend request
            db.prepare(`
                INSERT INTO friendships (user_id, friend_id, status)
                VALUES (?, ?, 'pending')
            `).run(request.user.id, friend_id);

            return reply.status(201).send({ message: 'Friend request sent' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.FRIENDS.SEND_FRIEND_REQUEST_FAILED });
        }
    });

    // Accept friend request
    fastify.post('/accept/:id', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const friendshipId = request.params.id;

        try {
            const friendship = db.prepare(`
                SELECT * FROM friendships WHERE id = ? AND friend_id = ? AND status = 'pending'
            `).get(friendshipId, request.user.id);

            if (!friendship) {
                return reply.status(404).send({ errorCode: ErrorCodes.FRIENDS.FRIEND_REQUEST_NOT_FOUND });
            }

            db.prepare(`UPDATE friendships SET status = 'accepted' WHERE id = ?`).run(friendshipId);

            return reply.send({ message: 'Friend request accepted' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.FRIENDS.ACCEPT_FRIEND_REQUEST_FAILED });
        }
    });

    // Reject/Remove friend
    fastify.delete('/:id', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const friendshipId = request.params.id;

        try {
            const friendship = db.prepare(`
                SELECT * FROM friendships 
                WHERE id = ? AND (user_id = ? OR friend_id = ?)
            `).get(friendshipId, request.user.id, request.user.id);

            if (!friendship) {
                return reply.status(404).send({ errorCode: ErrorCodes.FRIENDS.FRIENDSHIP_NOT_FOUND });
            }

            db.prepare(`DELETE FROM friendships WHERE id = ?`).run(friendshipId);

            return reply.send({ message: 'Friendship removed' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.FRIENDS.REMOVE_FRIENDSHIP_FAILED });
        }
    });

    // Get pending friend requests
    fastify.get('/requests', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        try {
            const requests = db.prepare(`
                SELECT f.id, u.id as user_id, u.username, u.display_name, f.created_at
                FROM friendships f
                JOIN users u ON f.user_id = u.id
                WHERE f.friend_id = ? AND f.status = 'pending'
                ORDER BY f.created_at DESC
            `).all(request.user.id);

            return reply.send({ requests });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.FRIENDS.FETCH_FRIEND_REQUESTS_FAILED });
        }
    });

    // Get online friends
    fastify.get('/online', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        try {
            const friends = db.prepare(`
                SELECT u.id, u.username, u.display_name
                FROM friendships f
                JOIN users u ON (f.friend_id = u.id)
                WHERE f.user_id = ? AND f.status = 'accepted' AND u.is_online = 1
                UNION
                SELECT u.id, u.username, u.display_name
                FROM friendships f
                JOIN users u ON (f.user_id = u.id)
                WHERE f.friend_id = ? AND f.status = 'accepted' AND u.is_online = 1
            `).all(request.user.id, request.user.id);

            return reply.send({ friends });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.FRIENDS.FETCH_ONLINE_FRIENDS_FAILED });
        }
    });
}

module.exports = routes;
