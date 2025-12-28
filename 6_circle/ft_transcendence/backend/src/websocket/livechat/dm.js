// Direct Message functionality

const { messagesModel } = require('../../models/messages');

const WSS_OPEN = 1; // WebSocket.OPEN

function createDMHandler(ctx, safeBlockExists) {
  const handler = {
    async sendDirectMessage(fromClient, toName, rawText) {
      const from = fromClient.username;
      const to = typeof toName === 'string' ? toName.trim() : '';
      const text = typeof rawText === 'string' ? rawText.trim() : '';

      if (!to || !text) {
        fromClient.safeSend({ type: 'error', reason: 'invalid_dm_target' });
        return;
      }
      if (to === from) {
        fromClient.safeSend({ type: 'error', reason: 'themselfves' });
        return;
      }

      // Find all sockets for the target user
      const toClients = Array.from(ctx.clients).filter(
        client => client.username === to && client.readyState === WSS_OPEN
      );
      if (toClients.length === 0) {
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

      const payload = {
        type: 'dm',
        from,
        to,
        text,
        ts: Date.now(),
      };

      // Send to all sender's connections
      const fromClients = Array.from(ctx.clients).filter(
        client => client.username === from && client.readyState === WSS_OPEN
      );
      for (const client of fromClients) {
        client.safeSend(payload);
      }

      // Send to all receiver's connections
      for (const client of toClients) {
        client.safeSend(payload);
      }
      await messagesModel(ctx.app.db).create({
        sender_username: from,
        receiver_username: to,
        content: text,
      });
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

module.exports = { createDMHandler };
