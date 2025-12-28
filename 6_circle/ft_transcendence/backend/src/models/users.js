// User model helpers

function usersModel(db) {
    return {
        findById: (id) => {
            return db.prepare('SELECT * FROM users WHERE id = ?').get(id);
        },
        findUsernameById: (id) => {
            return db.prepare('SELECT username FROM users WHERE id = ?').get(id);
        },
        findProfileById: (id) => {
            return db.prepare(`
                SELECT u.id, u.username, u.email, u.display_name, u.avatar_url,
                       u.two_fa_enabled, u.is_online, u.created_at,
                       COALESCE(s.total_games, 0) as total_games,
                       COALESCE(s.total_wins, 0) as total_wins,
                       COALESCE(s.total_losses, 0) as total_losses,
                       COALESCE(s.win_rate, 0) as win_rate,
                       COALESCE(s.highest_score, 0) as highest_score
                FROM users u
                LEFT JOIN user_stats s ON u.id = s.user_id
                WHERE u.id = ?
            `).get(id);
        },
        findPublicProfileById: (id) => {
            return db.prepare(`
                SELECT u.id, u.username, u.display_name, u.avatar_url,
                       u.is_online, u.created_at,
                       COALESCE(s.total_games, 0) as total_games,
                       COALESCE(s.total_wins, 0) as total_wins,
                       COALESCE(s.total_losses, 0) as total_losses,
                       COALESCE(s.win_rate, 0) as win_rate,
                       COALESCE(s.highest_score, 0) as highest_score
                FROM users u
                LEFT JOIN user_stats s ON u.id = s.user_id
                WHERE u.id = ?
            `).get(id);
        }
    };
}

module.exports = { usersModel };
