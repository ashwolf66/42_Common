const Database = require('better-sqlite3');
const path = require('path');

const dbPath = process.env.DATABASE_PATH || path.join(__dirname, 'database', 'ft_transcendence.db');
const db = new Database(dbPath);

try {
    // Check if column exists
    const tableInfo = db.pragma('table_info(users)');
    const hasAvatarUrl = tableInfo.some(col => col.name === 'avatar_url');
    
    if (!hasAvatarUrl) {
        console.log('Adding avatar_url column to users table...');
        db.exec('ALTER TABLE users ADD COLUMN avatar_url TEXT;');
        console.log('Successfully added avatar_url column!');
    } else {
        console.log('avatar_url column already exists.');
    }
} catch (error) {
    console.error('Error:', error.message);
    process.exit(1);
} finally {
    db.close();
}
