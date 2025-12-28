// Game Invitation functionality

const WSS_OPEN = 1; // WebSocket.OPEN

function createInvitationHandler(ctx, safeBlockExists) {
  const handler = {
    async sendInvite(fromClient, toName, invite) {
      const from = fromClient.username;
      const to = typeof toName === 'string' ? toName.trim() : '';

      if (!to) {
        fromClient.safeSend({ type: 'error', reason: 'invalid_invite_target' });
        return;
      }
      if (to === from) {
        fromClient.safeSend({ type: 'error', reason: 'themselfves' });
        return;
      }

      const toClients = ctx.getUserSockets(to);
      if (!toClients || toClients.length === 0) {
        fromClient.safeSend({ type: 'error', reason: 'user_is_not_online', to });
        return;
      }

      const { blockListModel } = require('../../models/block_list');
      const blockRepo = blockListModel(ctx.app.db);
      const blockStatus = await this.resolveBlockStatus(blockRepo, from, to, safeBlockExists);
      if (blockStatus) {
        fromClient.safeSend({ type: 'error', reason: blockStatus, to });
        return;
      }

      // Generate unique room name based on sender's username
      let roomName = from;
      let counter = 1;

      // Import gameRooms from game.js module
      const gameModule = require('../game');
      const gameRooms = gameModule.getGameRooms ? gameModule.getGameRooms() : new Map();

      // Check for duplicate room names and add counter if needed
      const existingRoomNames = Array.from(gameRooms.values()).map(room => room.roomName);
      while (existingRoomNames.includes(roomName)) {
        counter++;
        roomName = `${from}${counter}`;
      }

      const gameMode = invite?.gameMode || 'classic';

      // Note: The actual GameRoom will be created when the first player (sender or recipient)
      // joins via the game WebSocket. We just ensure the room name is unique.

      const roomUrl = `/game/remote?room=${encodeURIComponent(roomName)}&inviter=${encodeURIComponent(from)}`;

      const payload = {
        type: 'invite',
        from,
        to,
        url: roomUrl,
        roomName: roomName,
        gameMode: gameMode,
        ts: Date.now(),
      };
      const fromClients = ctx.getUserSockets(from);
      if (fromClients && fromClients.length > 0) {
        for (const client of fromClients) {
          if (client.readyState !== WSS_OPEN) continue;
          client.safeSend(payload);
        }
      } else {
        fromClient.safeSend(payload);
      }
      for (const client of toClients) {
        if (client.readyState !== WSS_OPEN) continue;
        client.safeSend(payload);
      }
    },

    async resolveBlockStatus(blockRepo, sender, receiver, safeBlockExists) {
      if (!sender || !receiver) return null;
      const senderBlockedReceiver = await safeBlockExists(blockRepo, {
        blocker_username: sender,
        blocked_username: receiver,
      });
      if (senderBlockedReceiver) return 'you_blocked_user';

      const receiverBlockedSender = await safeBlockExists(blockRepo, {
        blocker_username: receiver,
        blocked_username: sender,
      });
      if (receiverBlockedSender) return 'blocked_by_user';

      return null;
    },
  };

  return handler;
}

module.exports = { createInvitationHandler };
