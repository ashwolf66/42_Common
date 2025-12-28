// Tournament model helpers

function tournamentsModel(db) {
    return {
        findById: (id) => {
            return db.prepare('SELECT * FROM tournaments WHERE id = ?').get(id);
        },
        updateFinished: (id, winnerId) => {
            return db.prepare(`
                UPDATE tournaments
                SET status = 'finished', winner_id = ?, finished_at = datetime('now')
                WHERE id = ?
            `).run(winnerId, id);
        },
        updateCurrentRound: (id, currentRound) => {
            return db.prepare(`
                UPDATE tournaments SET current_round = ? WHERE id = ?
            `).run(currentRound, id);
        }
    };
}

module.exports = { tournamentsModel };
