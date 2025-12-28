// Tournament participants model helpers

function tournamentParticipantsModel(db) {
    return {
        markEliminated: (tournamentId, userId) => {
            return db.prepare(`
                UPDATE tournament_participants
                SET eliminated = 1
                WHERE tournament_id = ? AND user_id = ?
            `).run(tournamentId, userId);
        },
        countByTournamentId: (tournamentId) => {
            return db.prepare(`
                SELECT COUNT(*) as count FROM tournament_participants WHERE tournament_id = ?
            `).get(tournamentId);
        }
    };
}

module.exports = { tournamentParticipantsModel };
