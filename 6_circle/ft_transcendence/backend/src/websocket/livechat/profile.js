// Profile Access through Chat functionality

const WSS_OPEN = 1; // WebSocket.OPEN

function createProfileHandler(ctx) {
  const handler = {
    async sendPresenceSnapshot(client) {
      if (!client) return;
      // Get unique usernames from all connected clients
      const usernames = new Set(
        Array.from(ctx.clients)
          .filter(c => c.username)
          .map(c => c.username)
      );
      const users = Array.from(usernames)
        .sort((a, b) => a.localeCompare(b))
        .map((username) => ({ username }));
      client.safeSend({ type: 'presence_snapshot', users });
    },

    broadcastPresenceUpdate(username, status, skipClient) {
      if (!username) return;
      const payload = { type: 'presence_update', username, status };
      for (const client of ctx.clients) {
        if (client.readyState !== WSS_OPEN) continue;
        if (skipClient && client === skipClient) continue;
        client.safeSend(payload);
      }
    },

    async handleJoin(client, username) {
      const cleanName = username?.trim?.();
      if (!cleanName) {
        client.safeSend({ type: 'error', reason: 'invalid_username' });
        return;
      }

      // Check if this is the first connection for this user
      const existingConnections = Array.from(ctx.clients).filter(
        c => c.username === cleanName && c !== client
      );
      const isFirstConnection = existingConnections.length === 0;

      // Set username if not already set
      if (!client.username) {
        client.username = cleanName;
      }

      console.log('[LiveChat] User joined:', {
        username: cleanName,
        totalConnectionsForUser: existingConnections.length + 1,
        totalClients: ctx.clients.size
      });

      await this.sendPresenceSnapshot(client);
      if (ctx.tournament) {
        ctx.tournament.sendSnapshot(client);
      }

      if (isFirstConnection) {
        this.broadcastPresenceUpdate(cleanName, 'online', client);
        await this.sendAll({ type: 'enter', from: cleanName, action: 'joined' });
      }
    },

    async handleLeave(username, client) {
      const cleanName = username?.trim?.();
      if (!cleanName) return;

      // Check if there are other connections for this user
      const remainingConnections = Array.from(ctx.clients).filter(
        c => c.username === cleanName && c !== client
      );

      console.log('[LiveChat] User leave:', {
        username: cleanName,
        remainingConnectionsForUser: remainingConnections.length
      });

      // Only broadcast offline if this was the last connection
      if (remainingConnections.length === 0) {
        this.broadcastPresenceUpdate(cleanName, 'offline');
        await this.sendAll({ type: 'enter', from: cleanName, action: 'left' });
      }
    },
  };

  return handler;
}

module.exports = { createProfileHandler };
