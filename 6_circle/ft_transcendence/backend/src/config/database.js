const path = require('path');
const Database = require('better-sqlite3');

const DB_PATH = process.env.DATABASE_PATH || path.join(__dirname, '../../database/ft_transcendence.db');

const db = new Database(DB_PATH);
db.pragma('foreign_keys = ON');
db.pragma('journal_mode = WAL');

// Migration: Add session_id column if not exists
try {
    const tableInfo = db.pragma('table_info(users)');
    const hasSessionId = tableInfo.some(col => col.name === 'session_id');
    
    if (!hasSessionId) {
        console.log('Migrating: Adding session_id column to users table...');
        db.exec('ALTER TABLE users ADD COLUMN session_id TEXT;');
        console.log('Migration successful: session_id column added.');
    }
} catch (error) {
    console.error('Migration error:', error);
}

console.log(`Database connected: ${DB_PATH}`);

module.exports = db;
