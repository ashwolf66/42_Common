/**
 * Update user statistics after a game
 * Only updates stats for 'remote' and 'tournament' game modes
 * @param {Object} db - Database instance
 * @param {number} userId - User ID
 */
function updateUserStats(db, userId) {
    // Calculate stats from games where user participated
    // Only count 'remote' and games with tournament_id (tournament games)
    const stats = db.prepare(`
        SELECT 
            COUNT(*) as total_games,
            SUM(CASE WHEN winner_id = ? THEN 1 ELSE 0 END) as total_wins,
            SUM(CASE WHEN winner_id != ? THEN 1 ELSE 0 END) as total_losses,
            MAX(CASE WHEN player1_id = ? THEN player1_score ELSE player2_score END) as highest_score,
            SUM(duration_seconds) as total_playtime_seconds
        FROM games
        WHERE (player1_id = ? OR player2_id = ?)
        AND (game_mode = 'remote' OR tournament_id IS NOT NULL)
        AND finished_at IS NOT NULL
    `).get(userId, userId, userId, userId, userId);

    const totalGames = stats.total_games || 0;
    const totalWins = stats.total_wins || 0;
    const totalLosses = stats.total_losses || 0;
    const winRate = totalGames > 0 ? totalWins / totalGames : 0;
    const highestScore = stats.highest_score || 0;
    const totalPlaytime = stats.total_playtime_seconds || 0;

    // Insert or update user stats
    db.prepare(`
        INSERT INTO user_stats (user_id, total_games, total_wins, total_losses, win_rate, highest_score, total_playtime_seconds)
        VALUES (?, ?, ?, ?, ?, ?, ?)
        ON CONFLICT(user_id) DO UPDATE SET
            total_games = excluded.total_games,
            total_wins = excluded.total_wins,
            total_losses = excluded.total_losses,
            win_rate = excluded.win_rate,
            highest_score = excluded.highest_score,
            total_playtime_seconds = excluded.total_playtime_seconds
    `).run(userId, totalGames, totalWins, totalLosses, winRate, highestScore, totalPlaytime);
}

module.exports = { updateUserStats };
