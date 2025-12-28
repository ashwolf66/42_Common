const jwt = require('jsonwebtoken');
const ErrorCodes = require('../utils/errorCodes');

const JWT_SECRET = process.env.JWT_SECRET || 'your-secret-key';
const JWT_EXPIRATION = process.env.JWT_EXPIRATION || '1h';

function generateToken(user, sessionId) {
    return jwt.sign(
        { id: user.id, username: user.username, email: user.email, session_id: sessionId },
        JWT_SECRET,
        { expiresIn: JWT_EXPIRATION }
    );
}

function verifyToken(token) {
    try {
        return jwt.verify(token, JWT_SECRET);
    } catch (error) {
        return null;
    }
}

function authenticateToken(request, reply, done) {
    const authHeader = request.headers['authorization'];
    const token = authHeader && authHeader.split(' ')[1];

    if (!token) {
        return reply.status(401).send({ errorCode: ErrorCodes.MIDDLEWARE.ACCESS_TOKEN_REQUIRED });
    }

    const decoded = verifyToken(token);
    if (!decoded) {
        return reply.status(403).send({ errorCode: ErrorCodes.MIDDLEWARE.INVALID_OR_EXPIRED_TOKEN });
    }

    // Check session_id
    try {
        const db = request.server.db;
        if (db) {
            const user = db.prepare('SELECT session_id FROM users WHERE id = ?').get(decoded.id);
            // If user has no session_id in DB (e.g. old user), or session_id doesn't match
            // We allow if both are null/undefined? No, we want to enforce session_id.
            // But for migration, if DB has null, and token has undefined (old token), it might pass?
            // New tokens will have session_id.
            // If token has session_id, it MUST match DB.
            // If token does NOT have session_id (old token), it should probably be invalid if we want to enforce this.
            
            if (!user || user.session_id !== decoded.session_id) {
                return reply.status(401).send({ errorCode: ErrorCodes.MIDDLEWARE.SESSION_EXPIRED });
            }
        }
    } catch (err) {
        request.log.error(err);
        return reply.status(500).send({ errorCode: ErrorCodes.GENERIC.INTERNAL_SERVER_ERROR });
    }

    request.user = decoded;
    done();
}

module.exports = {
    generateToken,
    verifyToken,
    authenticateToken
};
