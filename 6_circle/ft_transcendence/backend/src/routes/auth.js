const bcrypt = require('bcrypt');
const speakeasy = require('speakeasy');
const QRCode = require('qrcode');
const { v4: uuidv4 } = require('uuid');
const { generateToken } = require('../middleware/auth');
const { validateUsername, validateEmail, validateDisplayName } = require('../utils/sanitize');
const ErrorCodes = require('../utils/errorCodes');

async function routes(fastify, options) {
    const db = fastify.db;

    // Register
    fastify.post('/register', async (request, reply) => {
        fastify.log.info('Register request received:', { body: request.body, headers: request.headers.origin });
        // Defensive: ensure request.body is an object
        const body = request.body || {};
        const { username, email, password, display_name } = body;

        if (!username || !email || !password) {
            return reply.status(400).send({ errorCode: ErrorCodes.AUTH.MISSING_REQUIRED_FIELDS });
        }

        // Validate and sanitize username
        const usernameValidation = validateUsername(username);
        if (!usernameValidation.valid) {
            return reply.status(400).send({ errorCode: ErrorCodes.AUTH.INVALID_USERNAME });
        }

        // Validate and sanitize email
        const emailValidation = validateEmail(email);
        if (!emailValidation.valid) {
            return reply.status(400).send({ errorCode: ErrorCodes.AUTH.INVALID_EMAIL });
        }

        // Validate and sanitize display_name
        const displayNameValidation = validateDisplayName(display_name);
        if (!displayNameValidation.valid) {
            return reply.status(400).send({ errorCode: ErrorCodes.AUTH.INVALID_DISPLAY_NAME });
        }

        if (password.length < 6) {
            return reply.status(400).send({ errorCode: ErrorCodes.AUTH.PASSWORD_TOO_SHORT });
        }

        try {
            // Check if user exists
            const existing = db.prepare('SELECT id FROM users WHERE username = ? OR email = ?').get(usernameValidation.value, emailValidation.value);
            if (existing) {
                return reply.status(409).send({ errorCode: ErrorCodes.AUTH.USER_ALREADY_EXISTS });
            }

            // Hash password
            const password_hash = await bcrypt.hash(password, 12);

            // Insert user
            const result = db.prepare(`
                INSERT INTO users (username, email, password_hash, display_name)
                VALUES (?, ?, ?, ?)
            `).run(usernameValidation.value, emailValidation.value, password_hash, displayNameValidation.value || usernameValidation.value);

            const user = db.prepare('SELECT id, username, email, display_name, created_at FROM users WHERE id = ?').get(result.lastInsertRowid);

            return reply.status(201).send({
                message: 'User registered successfully',
                user
            });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.AUTH.REGISTRATION_FAILED });
        }
    });

    // Login
    fastify.post('/login', async (request, reply) => {
        const { username, password, twofa_code } = request.body;

        if (!username || !password) {
            return reply.status(400).send({ errorCode: ErrorCodes.AUTH.MISSING_CREDENTIALS });
        }

        try {
            // Get user
            const user = db.prepare('SELECT * FROM users WHERE username = ? OR email = ?').get(username, username);

            if (!user) {
                return reply.status(401).send({ errorCode: ErrorCodes.AUTH.INVALID_CREDENTIALS });
            }

            // Verify password
            const validPassword = await bcrypt.compare(password, user.password_hash);
            if (!validPassword) {
                return reply.status(401).send({ errorCode: ErrorCodes.AUTH.INVALID_CREDENTIALS });
            }

            // Check 2FA
            if (user.two_fa_enabled) {
                if (!twofa_code) {
                    return reply.send({ requires_2fa: true });
                }

                const verified = speakeasy.totp.verify({
                    secret: user.two_fa_secret,
                    encoding: 'base32',
                    token: twofa_code,
                    window: 2
                });

                if (!verified) {
                    return reply.status(401).send({ errorCode: ErrorCodes.AUTH.INVALID_2FA_CODE });
                }
            }

            // Check if already logged in
            if (user.is_online === 1) {
                return reply.status(409).send({ errorCode: ErrorCodes.AUTH.ALREADY_LOGGED_IN });
            }

            // Update online status and session_id
            const sessionId = uuidv4();
            db.prepare('UPDATE users SET is_online = 1, session_id = ? WHERE id = ?').run(sessionId, user.id);

            // Generate token
            const token = generateToken(user, sessionId);

            return reply.send({
                message: 'Login successful',
                token,
                user: {
                    id: user.id,
                    username: user.username,
                    email: user.email,
                    display_name: user.display_name,
                    two_fa_enabled: user.two_fa_enabled
                }
            });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.AUTH.LOGIN_FAILED });
        }
    });

    // Logout
    fastify.post('/logout', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        try {
            db.prepare('UPDATE users SET is_online = 0, session_id = NULL WHERE id = ?').run(request.user.id);
            return reply.send({ message: 'Logout successful' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.AUTH.LOGOUT_FAILED });
        }
    });

    // Setup 2FA
    fastify.post('/2fa/setup', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        try {
            const secret = speakeasy.generateSecret({
                name: `${process.env.TWO_FA_ISSUER || 'ft_transcendence'} (${request.user.username})`
            });

            // Store temporary secret (not enabled yet)
            db.prepare('UPDATE users SET two_fa_secret = ? WHERE id = ?').run(secret.base32, request.user.id);

            // Generate QR code
            const qrCode = await QRCode.toDataURL(secret.otpauth_url);

            return reply.send({
                secret: secret.base32,
                qrCode
            });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.AUTH['2FA_SETUP_FAILED'] });
        }
    });

    // Verify and enable 2FA
    fastify.post('/2fa/verify', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const { token } = request.body;

        if (!token) {
            return reply.status(400).send({ errorCode: ErrorCodes.AUTH.TOKEN_REQUIRED });
        }

        try {
            const user = db.prepare('SELECT two_fa_secret FROM users WHERE id = ?').get(request.user.id);

            if (!user.two_fa_secret) {
                return reply.status(400).send({ errorCode: ErrorCodes.AUTH['2FA_NOT_SETUP'] });
            }

            const verified = speakeasy.totp.verify({
                secret: user.two_fa_secret,
                encoding: 'base32',
                token,
                window: 2
            });

            if (!verified) {
                return reply.status(401).send({ errorCode: ErrorCodes.AUTH.INVALID_TOKEN });
            }

            // Enable 2FA
            db.prepare('UPDATE users SET two_fa_enabled = 1 WHERE id = ?').run(request.user.id);

            return reply.send({ message: '2FA enabled successfully' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.AUTH['2FA_VERIFICATION_FAILED'] });
        }
    });

    // Disable 2FA
    fastify.post('/2fa/disable', { preHandler: [fastify.authenticateToken] }, async (request, reply) => {
        const { password } = request.body;

        if (!password) {
            return reply.status(400).send({ errorCode: ErrorCodes.AUTH.PASSWORD_REQUIRED });
        }

        try {
            const user = db.prepare('SELECT password_hash FROM users WHERE id = ?').get(request.user.id);
            const validPassword = await bcrypt.compare(password, user.password_hash);

            if (!validPassword) {
                return reply.status(401).send({ errorCode: ErrorCodes.AUTH.INVALID_PASSWORD });
            }

            db.prepare('UPDATE users SET two_fa_enabled = 0, two_fa_secret = NULL WHERE id = ?').run(request.user.id);

            return reply.send({ message: '2FA disabled successfully' });
        } catch (error) {
            fastify.log.error(error);
            return reply.status(500).send({ errorCode: ErrorCodes.AUTH['2FA_DISABLE_FAILED'] });
        }
    });
}

module.exports = routes;
