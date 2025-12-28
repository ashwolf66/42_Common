// Tournament Notifications functionality

function createTournamentHandler(ctx) {
  const handler = {
    sendSnapshot(client) {
      if (!ctx.tournament) return;
      ctx.tournament.sendSnapshot(client);
    },

    broadcastTournament(payload) {
      const tournamentPayload = { type: 'tournament', ...payload };
      console.log('Broadcasting tournament payload:', tournamentPayload);
      return this.sendAll(tournamentPayload);
    },
  };

  return handler;
}

module.exports = { createTournamentHandler };
