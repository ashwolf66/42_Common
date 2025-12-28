// Block and Unblock functionality

const { blockListModel } = require('../../models/block_list');

const WSS_OPEN = 1; // WebSocket.OPEN
const BLOCK_COMMAND = /^\+(\S+)$/;
const UNBLOCK_COMMAND = /^-(\S+)$/;

function createBlockHandler(ctx) {
  const handler = {
    BLOCK_COMMAND,
    UNBLOCK_COMMAND,

    async blockUser(client, targetName) {
      const me = client.username;
      const target = typeof targetName === 'string' ? targetName.trim() : '';
      if (!target) {
        client.safeSend({ type: 'error', reason: 'invalid_block_target' });
        return;
      }
      if (target === me) {
        client.safeSend({ type: 'error', reason: 'themselfves' });
        return;
      }
      const blockRepo = blockListModel(ctx.app.db);
      const exists = await blockRepo.exists({ blocker_username: me, blocked_username: target });
      if (exists) {
        client.safeSend({ type: 'block_update', action: 'already_blocked', username: target });
        return;
      }
      await blockRepo.add({ blocker_username: me, blocked_username: target });
      client.safeSend({ type: 'block_update', action: 'blocked', username: target });
      const targetClients = ctx.getUserSockets(target);
      for (const targetClient of targetClients) {
        if (targetClient.readyState === WSS_OPEN) {
          targetClient.safeSend({ type: 'block_notice', from: me });
        }
      }
    },

    async unblockUser(client, targetName) {
      const me = client.username;
      const target = typeof targetName === 'string' ? targetName.trim() : '';
      if (!target) {
        client.safeSend({ type: 'error', reason: 'invalid_block_target' });
        return;
      }
      if (target === me) {
        client.safeSend({ type: 'error', reason: 'themselfves' });
        return;
      }
      const blockRepo = blockListModel(ctx.app.db);
      const exists = await blockRepo.exists({ blocker_username: me, blocked_username: target });
      if (!exists) {
        client.safeSend({ type: 'block_update', action: 'not_blocked', username: target });
        return;
      }
      await blockRepo.remove({ blocker_username: me, blocked_username: target });
      client.safeSend({ type: 'block_update', action: 'unblocked', username: target });
      const targetClients = ctx.getUserSockets(target);
      for (const targetClient of targetClients) {
        if (targetClient.readyState === WSS_OPEN) {
          targetClient.safeSend({ type: 'unblock_notice', from: me });
        }
      }
    },
  };

  return handler;
}

module.exports = { createBlockHandler, BLOCK_COMMAND, UNBLOCK_COMMAND };
