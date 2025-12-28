// Live chat handler - aggregates all chat-related functionalities

const { messagesModel } = require('../../models/messages');
const { blockListModel } = require('../../models/block_list');
const { createDMHandler } = require('./dm');
const { createBlockHandler, BLOCK_COMMAND, UNBLOCK_COMMAND } = require('./block');
const { createInvitationHandler } = require('./invitation');
const { createTournamentHandler } = require('./tournament');
const { createProfileHandler } = require('./profile');

const WSS_OPEN = 1; // WebSocket.OPEN
const DM_COMMAND = /^@(\S+)\s+([\s\S]+)/;

function createLiveChatHandler(app) {
  // Store all client connections
  const clients = new Set();

  // Add safeSend method to WebSocket prototype
  const safeSend = function(payload) {
    if (this.readyState === WSS_OPEN) {
      try {
        this.send(typeof payload === 'string' ? payload : JSON.stringify(payload));
      } catch (error) {
        console.error('[LiveChat] Failed to send message:', error);
      }
    }
  };

  const handleBlockListError = (error) => {
    const message = error?.message || String(error);
    console.error('[LiveChat] block_list error:', message);
  };

  const safeBlockExists = async (repo, params) => {
    try {
      return await repo.exists(params);
    } catch (error) {
      handleBlockListError(error);
      return false;
    }
  };

  // Helper function to get all sockets for a username
  const getUserSockets = (username) => {
    if (!username) return [];
    return Array.from(clients).filter(c => c.username === username);
  };

  const ctx = {
    app,
    clients,
    getUserSockets,
    nextSocketId: 1,
    tournament: null // Can be extended for tournament features
  };

  // Create module handlers
  const dmHandler = createDMHandler(ctx, safeBlockExists);
  const blockHandler = createBlockHandler(ctx);
  const invitationHandler = createInvitationHandler(ctx, safeBlockExists);
  const tournamentHandler = createTournamentHandler(ctx);
  const profileHandler = createProfileHandler(ctx);

  const handler = {
    async handleMessage(type, payload, client) {
      console.log('[LiveChat] Incoming message:', {
        type,
        from: client?.username,
        payload
      });
      switch (type) {
        case 'join': {
          // Username is already set from token authentication
          if (!client.username) {
            client.safeSend({ type: 'error', reason: 'not_authenticated' });
            return true;
          }
          await profileHandler.handleJoin(client, client.username);
          return true;
        }
        case 'leave': {
          return true;
        }
        case 'sys': {
          const text = payload.text ?? '';
          await this.sendAll({ type: 'sys', text });
          return true;
        }
        case 'chat': {
          const text = payload.text?.trim?.();

          if (!text) {
            return true; // Ignore empty messages
          }

          if (!client.username) {
            client.safeSend({ type: 'error', reason: 'not_authenticated' });
            return true;
          }

          await this.handleChat(client, client.username, text);

          // Only save non-command messages
          const isCommand = DM_COMMAND.test(text) || BLOCK_COMMAND.test(text) || UNBLOCK_COMMAND.test(text);
          if (!isCommand) {
            await this.saveChatMessage(client.username, text);
          }
          return true;
        }
        case 'online_user':
          await profileHandler.sendPresenceSnapshot(client);
          return true;
        case 'dm_send': {
          const to = payload.to?.trim?.();
          const text = payload.text?.trim?.();
          if (!to || !text) {
            client.safeSend({ type: 'error', reason: 'invalid_dm_target' });
            return true;
          }
          await dmHandler.sendDirectMessage(client, to, text);
          return true;
        }
        case 'invite': {
          const to = payload.to?.trim?.();
          if (!to) {
            client.safeSend({ type: 'error', reason: 'invalid_invite_target' });
            return true;
          }
          await invitationHandler.sendInvite(client, to, {
            roomName: payload.roomName || null,
            gameMode: payload.gameMode || null
          });
          return true;
        }
        case 'block_user': {
          const target = payload.to?.trim?.();
          if (!target) {
            client.safeSend({ type: 'error', reason: 'invalid_block_target' });
            return true;
          }
          await blockHandler.blockUser(client, target);
          return true;
        }
        case 'unblock_user': {
          const target = payload.to?.trim?.();
          if (!target) {
            client.safeSend({ type: 'error', reason: 'invalid_block_target' });
            return true;
          }
          await blockHandler.unblockUser(client, target);
          return true;
        }
        default:
          return false;
      }
    },

    async handleChat(client, username, rawText) {
      const text = (rawText ?? '').toString();
      const trimmed = text.trim();
      if (!trimmed) return;

      const blockMatch = BLOCK_COMMAND.exec(trimmed);
      if (blockMatch) {
        await blockHandler.blockUser(client, blockMatch[1]);
        return;
      }
      const unblockMatch = UNBLOCK_COMMAND.exec(trimmed);
      if (unblockMatch) {
        await blockHandler.unblockUser(client, unblockMatch[1]);
        return;
      }
      const dmMatch = DM_COMMAND.exec(text);
      if (dmMatch) {
        await dmHandler.sendDirectMessage(client, dmMatch[1], dmMatch[2]);
        return;
      }
      await this.sendAll({ type: 'chat', from: username, text });
    },

    async saveChatMessage(username, text) {
      if (username && text?.trim()) {
        await messagesModel(ctx.app.db).create({
          sender_username: username,
          receiver_username: null,
          content: text,
        });
      }
    },

    async sendAll(payload) {
      console.log('[LiveChat] sendAll called with payload:', {
        type: payload.type,
        action: payload.action,
        from: payload.from,
        hasI18nKey: !!payload.i18nKey
      });
      const blockRepo = blockListModel(ctx.app.db);
      const from = payload.from?.trim?.();
      let delivered = 0;
      let skippedBlocked = 0;
      let skippedClosed = 0;

      for (const client of ctx.clients) {
        if (client.readyState !== WSS_OPEN) {
          skippedClosed += 1;
          continue;
        }
        if (!from || !client.username || client.username === from) {
          console.log('[LiveChat] Sending to client:', {
            username: client.username || 'anonymous',
            socketId: client._livechatId,
            reason: !from ? 'no_from_field' : (!client.username ? 'no_client_username' : 'sender_is_recipient')
          });
          client.safeSend(payload);
          delivered += 1;
          continue;
        }
        const blockedByReceiver = await safeBlockExists(blockRepo, {
          blocker_username: client.username,
          blocked_username: from,
        });
        if (blockedByReceiver) {
          skippedBlocked += 1;
          continue;
        }
        const blockedBySender = await safeBlockExists(blockRepo, {
          blocker_username: from,
          blocked_username: client.username,
        });
        if (blockedBySender) {
          skippedBlocked += 1;
          continue;
        }
        client.safeSend(payload);
        delivered += 1;
      }
      console.log('[LiveChat] sendAll summary:', {
        type: payload.type,
        from,
        delivered,
        skippedBlocked,
        skippedClosed,
        liveChatTotalClients: ctx.clients.size
      });
    },
  };

  // Add sendAll method to profile handler for join/leave notifications
  profileHandler.sendAll = handler.sendAll.bind(handler);

  return {
    handler,
    ctx,
    safeSend
  };
}

// Global handler instance to be accessed by other modules
let globalHandler = null;

async function routes(fastify, options) {
  const { handler, ctx, safeSend } = createLiveChatHandler(fastify);

  globalHandler = handler;
  const rootFastify = fastify.root || fastify;
  if (!rootFastify.hasDecorator('livechat')) {
    rootFastify.decorate('livechat', {
      broadcast: (payload) => handler.sendAll(payload),
      broadcastTournament: (payload) => {
        console.log('[LiveChat] broadcastTournament called with:', payload);
        return handler.sendAll({ type: 'tournament', ...payload });
      },
    });
    console.log('[LiveChat] livechat decorator registered on root fastify instance');
  }

  fastify.register(async function (fastify) {
    fastify.get('/', { websocket: true }, (connection, req) => {
      const socket = connection.socket;
      socket._livechatId = ctx.nextSocketId++;
      socket._livechatConnectedAt = Date.now();

      // Add safeSend method to socket
      socket.safeSend = safeSend.bind(socket);
      const refreshToken = req.query?.token;

      if (!refreshToken) {
        console.log('[LiveChat] Connection rejected: No token provided');
        socket.close(4001, 'Authentication required');
        return;
      }

      const { verifyToken } = require('../../middleware/auth');
      const user = verifyToken(refreshToken);

      if (!user) {
        console.log('[LiveChat] Connection rejected: Invalid token');
        socket.close(4002, 'Invalid or expired token');
        return;
      }

      socket.username = user.username;
      socket.refreshToken = refreshToken;
      console.log('[LiveChat] User authenticated via token:', user.username);

      // Add to clients set
      ctx.clients.add(socket);

      console.log('[LiveChat] WebSocket connection established', {
        socketId: socket._livechatId,
        username: socket.username || 'unauthenticated',
        remoteAddress: req.socket?.remoteAddress,
        origin: req.headers?.origin,
        userAgent: req.headers?.['user-agent']
      });

      socket.on('message', async (message) => {
        try {
          console.log('[LiveChat] Raw message received', {
            socketId: socket._livechatId,
            size: message?.length
          });
          const data = JSON.parse(message.toString());

          if (!data || typeof data !== 'object') {
            console.error('[LiveChat] Invalid message format - not an object');
            socket.safeSend({ type: 'error', reason: 'invalid_message_format' });
            return;
          }

          const { type, payload } = data;

          if (!type || typeof type !== 'string') {
            console.error('[LiveChat] Missing or invalid message type');
            socket.safeSend({ type: 'error', reason: 'missing_message_type' });
            return;
          }

          const handled = await handler.handleMessage(type, payload || {}, socket);

          if (!handled) {
            console.log('[LiveChat] Unknown message type:', type);
            socket.safeSend({ type: 'error', reason: 'unknown_message_type', messageType: type });
          }
        } catch (error) {
          console.error('[LiveChat] WebSocket message error:', error.message);
          socket.safeSend({ type: 'error', reason: 'server_error', message: error.message });
        }
      });

      socket.on('close', async (code, reason) => {
        const durationMs = Date.now() - (socket._livechatConnectedAt || Date.now());
        console.log('[LiveChat] WebSocket connection closed', {
          socketId: socket._livechatId,
          username: socket.username,
          code,
          reason: reason?.toString?.(),
          durationMs
        });

        // Remove from clients
        ctx.clients.delete(socket);

        // Handle user leave - use profile handler
        if (socket.username) {
          const profileHandler = createProfileHandler(ctx);
          profileHandler.sendAll = handler.sendAll.bind(handler);
          await profileHandler.handleLeave(socket.username, socket);
        }
      });

      socket.on('error', (error) => {
        console.error('[LiveChat] WebSocket error:', error);
      });
    });
  });
}

// Export both routes and a function to get the global handler
module.exports = routes;
module.exports.getHandler = () => globalHandler;
