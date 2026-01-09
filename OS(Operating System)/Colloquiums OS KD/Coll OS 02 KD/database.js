const Database = require("better-sqlite3");
const bcrypt = require("bcryptjs");

const db = new Database("tasks.db");

const initDatabase = async () => {
  db.prepare(`
    CREATE TABLE IF NOT EXISTS tasks (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      title TEXT NOT NULL,
      description TEXT,
      status TEXT CHECK(status IN ('todo','in_progress','done')) DEFAULT 'todo',
      user_id INTEGER,
      created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
      updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
    )
  `).run();

  db.prepare(`
    CREATE TABLE IF NOT EXISTS users (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      username TEXT UNIQUE NOT NULL,
      password TEXT NOT NULL,
      created_at DATETIME DEFAULT CURRENT_TIMESTAMP
    )
  `).run();

  try {
    const userCount = db.prepare("SELECT COUNT(*) as count FROM users").get();
    if (userCount.count === 0) {
      const hashedPassword = await bcrypt.hash("admin123", 10);
      db.prepare("INSERT INTO users (username, password) VALUES (?, ?)")
        .run("admin", hashedPassword);
      console.log("Создан тестовый пользователь: admin / admin123");
    }
  } catch (error) {
    console.error("Ошибка при создании тестового пользователя:", error);
  }

  console.log("База данных инициализирована");
};

module.exports = { db, initDatabase };