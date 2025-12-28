// Game model helpers

function gamesModel(db) {
    return {
        countFinishedByTournamentId: (tournamentId) => {
            return db.prepare(`
                SELECT COUNT(*) as count
                FROM games
                WHERE tournament_id = ? AND finished_at IS NOT NULL
            `).get(tournamentId);
        },
        countByTournamentId: (tournamentId) => {
            return db.prepare(`
                SELECT COUNT(*) as count
                FROM games
                WHERE tournament_id = ?
            `).get(tournamentId);
        },
        updateMatchResult: ({ matchId, player1Score, player2Score, winnerId, durationSeconds }) => {
            return db.prepare(`
                UPDATE games
                SET player1_score = ?, player2_score = ?, winner_id = ?,
                    duration_seconds = ?, finished_at = datetime('now')
                WHERE id = ?
            `).run(player1Score, player2Score, winnerId, durationSeconds, matchId);
        },
        insertGameResult: ({
            player1Id,
            player2Id,
            player1Score,
            player2Score,
            winnerId,
            durationSeconds,
            tournamentId
        }) => {
            return db.prepare(`
                INSERT INTO games (
                    player1_id, player2_id, player1_score, player2_score,
                    winner_id, game_mode, duration_seconds, tournament_id, finished_at
                )
                VALUES (?, ?, ?, ?, ?, 'remote', ?, ?, datetime('now'))
            `).run(
                player1Id,
                player2Id,
                player1Score,
                player2Score,
                winnerId,
                durationSeconds,
                tournamentId
            );
        },
        findByTournamentId: (tournamentId) => {
            return db.prepare(`
                SELECT * FROM games WHERE tournament_id = ? ORDER BY id ASC
            `).all(tournamentId);
        },
        insertTournamentMatch: ({ player1Id, player2Id, tournamentId }) => {
            return db.prepare(`
                INSERT INTO games (player1_id, player2_id, game_mode, tournament_id, started_at)
                VALUES (?, ?, 'remote', ?, datetime('now'))
            `).run(player1Id, player2Id, tournamentId);
        }
    };
}

module.exports = { gamesModel };
