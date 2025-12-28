// Block list model for user blocking

function blockListModel(db) {
  return {
    exists: async ({ blocker_username, blocked_username }) => {
      const result = db.prepare(`
        SELECT COUNT(*) as count FROM block_list
        WHERE blocker_username = ? AND blocked_username = ?
      `).get(blocker_username, blocked_username);

      return result.count > 0;
    },

    add: async ({ blocker_username, blocked_username }) => {
      const result = db.prepare(`
        INSERT INTO block_list (blocker_username, blocked_username, created_at)
        VALUES (?, ?, datetime('now'))
      `).run(blocker_username, blocked_username);

      return result.lastInsertRowid;
    },

    remove: async ({ blocker_username, blocked_username }) => {
      const result = db.prepare(`
        DELETE FROM block_list
        WHERE blocker_username = ? AND blocked_username = ?
      `).run(blocker_username, blocked_username);

      return result.changes;
    },

    getBlockedUsers: async (blocker_username) => {
      return db.prepare(`
        SELECT blocked_username FROM block_list
        WHERE blocker_username = ?
      `).all(blocker_username);
    }
  };
}

module.exports = { blockListModel };
