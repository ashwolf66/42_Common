const fs = require('fs');
const path = require('path');
const Database = require('better-sqlite3');

const DB_PATH = process.env.DATABASE_PATH || path.join(__dirname, 'ft_transcendence.db');
const SCHEMA_PATH = path.join(__dirname, 'schema.sql');

console.log('Starting database migration...');

// Create database directory if it doesn't exist
const dbDir = path.dirname(DB_PATH);
if (!fs.existsSync(dbDir)) {
    fs.mkdirSync(dbDir, { recursive: true });
    console.log(`Created directory: ${dbDir}`);
}

// Open database connection
const db = new Database(DB_PATH);
console.log(`Database connected: ${DB_PATH}`);

// Enable foreign keys
db.pragma('foreign_keys = ON');

// Read and execute schema
const schema = fs.readFileSync(SCHEMA_PATH, 'utf8');

// Split by semicolon but handle triggers specially
const statements = [];
let currentStatement = '';
let inTrigger = false;

schema.split('\n').forEach(line => {
    // Skip empty lines and comments at the start of a new statement
    if (!currentStatement && (line.trim().length === 0 || line.trim().startsWith('--'))) {
        return;
    }
    
    currentStatement += line + '\n';
    
    // Check if we're entering a trigger
    if (line.trim().toUpperCase().includes('CREATE TRIGGER')) {
        inTrigger = true;
    }
    
    // Check if we're exiting a trigger (END followed by semicolon)
    if (inTrigger && line.trim() === 'END;') {
        statements.push(currentStatement.trim());
        currentStatement = '';
        inTrigger = false;
    }
    // Normal statement end
    else if (!inTrigger && line.includes(';')) {
        statements.push(currentStatement.trim());
        currentStatement = '';
    }
});

// Add any remaining statement
if (currentStatement.trim()) {
    statements.push(currentStatement.trim());
}

// Filter out empty and comment-only statements
const validStatements = statements.filter(stmt => {
    const trimmed = stmt.trim();
    return trimmed.length > 0 && !trimmed.startsWith('--');
});

console.log(`Executing ${validStatements.length} SQL statements...`);

let successCount = 0;
let failureCount = 0;

validStatements.forEach((statement, index) => {
    try {
        db.exec(statement);
        successCount++;
        // Only log first 100 chars for cleaner output
        const preview = statement.substring(0, 100).replace(/\s+/g, ' ');
        console.log(`[OK] Statement ${index + 1}/${validStatements.length}: ${preview}...`);
    } catch (error) {
        failureCount++;
        console.error(`[FAIL] Statement ${index + 1} failed:`, error.message);
        console.error(statement.substring(0, 150) + '...');
    }
});

console.log(`\nResults: ${successCount} succeeded, ${failureCount} failed`);

// Verify tables
const tables = db.prepare("SELECT name FROM sqlite_master WHERE type='table'").all();
console.log('\nCreated tables:');
tables.forEach(table => {
    console.log(`  - ${table.name}`);
});

// Add avatar_url column to existing databases
console.log('\nChecking for additional migrations...');
try {
    const columns = db.prepare("PRAGMA table_info(users)").all();
    const hasAvatarUrl = columns.some(col => col.name === 'avatar_url');
    
    if (!hasAvatarUrl) {
        console.log('Adding avatar_url column to users table...');
        db.exec('ALTER TABLE users ADD COLUMN avatar_url TEXT');
        console.log('✓ avatar_url column added');
    } else {
        console.log('✓ avatar_url column already exists');
    }
} catch (error) {
    console.error('Migration check failed:', error.message);
}

db.close();
console.log('\nDatabase migration completed successfully!');
