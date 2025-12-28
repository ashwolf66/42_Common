-- ft_transcendence Database Schema
-- SQLite Database

-- Users table
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    email TEXT UNIQUE NOT NULL,
    password_hash TEXT NOT NULL,
    display_name TEXT,
    avatar_url TEXT,
    two_fa_secret TEXT,
    two_fa_enabled INTEGER DEFAULT 0,
    is_online INTEGER DEFAULT 0,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

-- Friendships table
CREATE TABLE IF NOT EXISTS friendships (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    friend_id INTEGER NOT NULL,
    status TEXT DEFAULT 'pending' CHECK(status IN ('pending', 'accepted', 'blocked')),
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (friend_id) REFERENCES users(id) ON DELETE CASCADE,
    UNIQUE(user_id, friend_id)
);

-- Games table
CREATE TABLE IF NOT EXISTS games (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    player1_id INTEGER,
    player2_id INTEGER,
    player1_score INTEGER DEFAULT 0,
    player2_score INTEGER DEFAULT 0,
    winner_id INTEGER,
    game_mode TEXT DEFAULT 'local' CHECK(game_mode IN ('local', 'remote', 'ai')),
    difficulty TEXT CHECK(difficulty IN ('easy', 'medium', 'hard')),
    duration_seconds INTEGER DEFAULT 0,
    tournament_id INTEGER,
    started_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    finished_at DATETIME,
    FOREIGN KEY (player1_id) REFERENCES users(id) ON DELETE SET NULL,
    FOREIGN KEY (player2_id) REFERENCES users(id) ON DELETE SET NULL,
    FOREIGN KEY (winner_id) REFERENCES users(id) ON DELETE SET NULL,
    FOREIGN KEY (tournament_id) REFERENCES tournaments(id) ON DELETE CASCADE
);

-- Tournaments table
CREATE TABLE IF NOT EXISTS tournaments (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    max_players INTEGER NOT NULL,
    current_round INTEGER DEFAULT 0,
    total_rounds INTEGER,
    status TEXT DEFAULT 'pending' CHECK(status IN ('pending', 'active', 'finished')),
    winner_id INTEGER,
    created_by INTEGER,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    started_at DATETIME,
    finished_at DATETIME,
    FOREIGN KEY (winner_id) REFERENCES users(id) ON DELETE SET NULL,
    FOREIGN KEY (created_by) REFERENCES users(id) ON DELETE SET NULL
);

-- Tournament participants table
CREATE TABLE IF NOT EXISTS tournament_participants (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    tournament_id INTEGER NOT NULL,
    user_id INTEGER,
    alias TEXT,
    seed INTEGER,
    eliminated INTEGER DEFAULT 0,
    joined_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (tournament_id) REFERENCES tournaments(id) ON DELETE CASCADE,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE SET NULL
);

-- User statistics table (denormalized for performance)
CREATE TABLE IF NOT EXISTS user_stats (
    user_id INTEGER PRIMARY KEY,
    total_games INTEGER DEFAULT 0,
    total_wins INTEGER DEFAULT 0,
    total_losses INTEGER DEFAULT 0,
    win_rate REAL DEFAULT 0.0,
    highest_score INTEGER DEFAULT 0,
    total_playtime_seconds INTEGER DEFAULT 0,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

-- Messages table
CREATE TABLE IF NOT EXISTS messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    sender_username TEXT NOT NULL,
    receiver_username TEXT,
    content TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (sender_username) REFERENCES users(username),
    FOREIGN KEY (receiver_username) REFERENCES users(username)
);

-- Block list table
CREATE TABLE IF NOT EXISTS block_list (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    blocker_username TEXT NOT NULL,
    blocked_username TEXT NOT NULL,
    created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
    UNIQUE(blocker_username, blocked_username),
    FOREIGN KEY (blocker_username) REFERENCES users(username),
    FOREIGN KEY (blocked_username) REFERENCES users(username)
);

-- Indexes for performance
CREATE INDEX IF NOT EXISTS idx_friendships_user_id ON friendships(user_id);
CREATE INDEX IF NOT EXISTS idx_friendships_friend_id ON friendships(friend_id);
CREATE INDEX IF NOT EXISTS idx_friendships_status ON friendships(status);
CREATE INDEX IF NOT EXISTS idx_games_player1_id ON games(player1_id);
CREATE INDEX IF NOT EXISTS idx_games_player2_id ON games(player2_id);
CREATE INDEX IF NOT EXISTS idx_games_tournament_id ON games(tournament_id);
CREATE INDEX IF NOT EXISTS idx_games_finished_at ON games(finished_at);
CREATE INDEX IF NOT EXISTS idx_tournament_participants_tournament_id ON tournament_participants(tournament_id);
CREATE INDEX IF NOT EXISTS idx_users_username ON users(username);
CREATE INDEX IF NOT EXISTS idx_users_email ON users(email);
CREATE INDEX IF NOT EXISTS idx_users_wallet ON users(wallet_address);
CREATE INDEX IF NOT EXISTS idx_messages_sender ON messages(sender_username);
CREATE INDEX IF NOT EXISTS idx_messages_receiver ON messages(receiver_username);
CREATE INDEX IF NOT EXISTS idx_messages_created ON messages(created_at);
CREATE INDEX IF NOT EXISTS idx_block_blocker ON block_list(blocker_username);
CREATE INDEX IF NOT EXISTS idx_block_blocked ON block_list(blocked_username);

-- Trigger: Update user stats when a game finishes
CREATE TRIGGER IF NOT EXISTS update_user_stats_after_game
AFTER UPDATE ON games
WHEN NEW.finished_at IS NOT NULL AND OLD.finished_at IS NULL
BEGIN
    -- Update player1 stats
    INSERT INTO user_stats (user_id, total_games, total_wins, total_losses, highest_score, total_playtime_seconds)
    VALUES (NEW.player1_id, 1, 
            CASE WHEN NEW.winner_id = NEW.player1_id THEN 1 ELSE 0 END,
            CASE WHEN NEW.winner_id != NEW.player1_id THEN 1 ELSE 0 END,
            NEW.player1_score,
            NEW.duration_seconds)
    ON CONFLICT(user_id) DO UPDATE SET
        total_games = total_games + 1,
        total_wins = total_wins + CASE WHEN NEW.winner_id = NEW.player1_id THEN 1 ELSE 0 END,
        total_losses = total_losses + CASE WHEN NEW.winner_id != NEW.player1_id THEN 1 ELSE 0 END,
        highest_score = MAX(highest_score, NEW.player1_score),
        total_playtime_seconds = total_playtime_seconds + NEW.duration_seconds,
        win_rate = CAST(total_wins AS REAL) / CAST(total_games AS REAL);
    
    -- Update player2 stats (if not AI)
    INSERT INTO user_stats (user_id, total_games, total_wins, total_losses, highest_score, total_playtime_seconds)
    SELECT NEW.player2_id, 1,
            CASE WHEN NEW.winner_id = NEW.player2_id THEN 1 ELSE 0 END,
            CASE WHEN NEW.winner_id != NEW.player2_id THEN 1 ELSE 0 END,
            NEW.player2_score,
            NEW.duration_seconds
    WHERE NEW.player2_id IS NOT NULL
    ON CONFLICT(user_id) DO UPDATE SET
        total_games = total_games + 1,
        total_wins = total_wins + CASE WHEN NEW.winner_id = NEW.player2_id THEN 1 ELSE 0 END,
        total_losses = total_losses + CASE WHEN NEW.winner_id != NEW.player2_id THEN 1 ELSE 0 END,
        highest_score = MAX(highest_score, NEW.player2_score),
        total_playtime_seconds = total_playtime_seconds + NEW.duration_seconds,
        win_rate = CAST(total_wins AS REAL) / CAST(total_games AS REAL);
END;

-- Trigger: Update updated_at timestamp
CREATE TRIGGER IF NOT EXISTS update_users_timestamp
AFTER UPDATE ON users
BEGIN
    UPDATE users SET updated_at = CURRENT_TIMESTAMP WHERE id = NEW.id;
END;

-- Blockchain Configuration table
CREATE TABLE IF NOT EXISTS blockchain_config (
    key TEXT PRIMARY KEY,
    value TEXT NOT NULL,
    updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

