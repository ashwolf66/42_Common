const fs = require('fs');
const path = require('path');
const Fastify = require('fastify');
const cors = require('@fastify/cors');
const multipart = require('@fastify/multipart');
const staticFiles = require('@fastify/static');
const websocket = require('@fastify/websocket');
require('dotenv').config({ path: path.join(__dirname, '../../.env') });

const db = require('./config/database');
const authRoutes = require('./routes/auth');
const userRoutes = require('./routes/users');
const gameRoutes = require('./routes/games');
const tournamentRoutes = require('./routes/tournaments');
const friendRoutes = require('./routes/friends');
const { authenticateToken } = require('./middleware/auth');
const gameWebSocket = require('./websocket/game');
const liveChatWebSocket = require('./websocket/livechat/livechat');
const initBlockchain = require('./utils/initBlockchain');

// Initialize Blockchain (attempt auto-deploy on boot to ensure readiness)
initBlockchain(db, { autoDeploy: true }).then(address => {
    if (address) {
        console.log(`[Server] Blockchain initialized. Contract: ${address}`);
        // Pre-connect the service
        const blockchainService = require('./services/BlockchainService');
        blockchainService.connect(true);
    } else {
        console.warn('[Server] Blockchain initialization failed. Check logs for details.');
    }
});

const fastify = Fastify({
    logger: true,
    https: {
        key: fs.readFileSync(process.env.SSL_KEY_PATH || path.join(__dirname, '../../ssl/key.pem')),
        cert: fs.readFileSync(process.env.SSL_CERT_PATH || path.join(__dirname, '../../ssl/cert.pem'))
    }
});

// Add database to fastify instance
fastify.decorate('db', db);

// Add auth middleware to fastify instance
fastify.decorate('authenticateToken', authenticateToken);

// Register CORS first
const isDev = process.env.NODE_ENV !== 'production';
fastify.register(cors, {
    origin: isDev
        ? true // reflect request origin and allow credentials in development
        : (origin, cb) => {
            const allowedOrigins = ['https://localhost:3000', 'http://localhost:3000', 'https://127.0.0.1:3000', 'http://127.0.0.1:3000'];
            if (!origin || allowedOrigins.includes(origin)) {
                cb(null, true);
                return;
            }
            cb(new Error('Not allowed by CORS'));
        },
    credentials: true,
    methods: ['GET', 'POST', 'PUT', 'DELETE', 'OPTIONS', 'PATCH'],
    allowedHeaders: ['Content-Type', 'Authorization', 'Accept'],
    exposedHeaders: ['Content-Type', 'Authorization']
});

// Register other plugins
fastify.register(multipart, {
    limits: {
        fileSize: 5 * 1024 * 1024 // 5MB
    }
});

fastify.register(staticFiles, {
    root: path.join(__dirname, '../uploads'),
    prefix: '/uploads/'
});

fastify.register(websocket);

// Add security headers
fastify.addHook('onRequest', async (request, reply) => {
    // Prevent XSS attacks
    reply.header('X-Content-Type-Options', 'nosniff');
    reply.header('X-Frame-Options', 'DENY');
    reply.header('X-XSS-Protection', '1; mode=block');
    reply.header('Content-Security-Policy', "default-src 'self'; script-src 'self' 'unsafe-inline'; style-src 'self' 'unsafe-inline'; img-src 'self' data: https:;");
    reply.header('Referrer-Policy', 'strict-origin-when-cross-origin');
});

// Health check
fastify.get('/health', async (request, reply) => {
    return { status: 'ok', timestamp: new Date().toISOString() };
});

// Register routes
fastify.register(authRoutes, { prefix: '/api/auth' });
fastify.register(userRoutes, { prefix: '/api/users' });
fastify.register(gameRoutes, { prefix: '/api/games' });
fastify.register(tournamentRoutes, { prefix: '/api/tournaments' });
fastify.register(friendRoutes, { prefix: '/api/friends' });

fastify.register(liveChatWebSocket, { prefix: '/ws/livechat' });
fastify.register(gameWebSocket, { prefix: '/ws/game' });

// Error handler
fastify.setErrorHandler((error, request, reply) => {
    fastify.log.error(error);
    reply.status(error.statusCode || 500).send({
        error: error.message || 'Internal Server Error',
        statusCode: error.statusCode || 500
    });
});

// Start server
const start = async () => {
    try {
        // Initialize all plugins before listening
        await fastify.ready();
        console.log('[Server] All plugins initialized');

        const PORT = process.env.BACKEND_PORT || 4000;
        await fastify.listen({ port: PORT, host: '0.0.0.0' });
        console.log(`Server running on https://localhost:${PORT}`);
        console.log('[Server] fastify.livechat available:', !!fastify.livechat);

        // Verify livechat handler is available
        const livechat = require('./websocket/livechat/livechat');
        console.log('[Server] livechat handler available:', !!livechat.getHandler());
    } catch (err) {
        fastify.log.error(err);
        process.exit(1);
    }
};

start();

// Export fastify instance for access in other modules
module.exports.fastifyInstance = fastify;
