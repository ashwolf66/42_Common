// Message model for chat messages

function messagesModel(db) {
  return {
    create: async ({ sender_username, receiver_username, content }) => {
      const result = db.prepare(`
        INSERT INTO messages (sender_username, receiver_username, content, created_at)
        VALUES (?, ?, ?, datetime('now'))
      `).run(sender_username, receiver_username, content);

      return result.lastInsertRowid;
    },

    findByUsers: async (user1, user2, limit = 50) => {
      return db.prepare(`
        SELECT * FROM messages
        WHERE (sender_username = ? AND receiver_username = ?)
           OR (sender_username = ? AND receiver_username = ?)
        ORDER BY created_at DESC
        LIMIT ?
      `).all(user1, user2, user2, user1, limit);
    },

    findGlobalMessages: async (limit = 100) => {
      return db.prepare(`
        SELECT * FROM messages
        WHERE receiver_username IS NULL
        ORDER BY created_at DESC
        LIMIT ?
      `).all(limit);
    }
  };
}

module.exports = { messagesModel };
