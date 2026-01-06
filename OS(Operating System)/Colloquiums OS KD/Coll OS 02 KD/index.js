const express = require("express");
const Database = require("better-sqlite3");

const app = express();
app.use(express.json());

const db = new Database("tasks.db");

db.prepare(`
  CREATE TABLE IF NOT EXISTS tasks (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT NOT NULL,
    description TEXT,
    status TEXT CHECK(status IN ('todo','in_progress','done')) DEFAULT 'todo'
  )
`).run();

app.get("/", (req, res) => {
  res.send("API работает!");
});

app.get("/tasks", (req, res) => {
  const tasks = db.prepare("SELECT * FROM tasks").all();
  res.json(tasks);
});

app.post("/tasks", (req, res) => {
  const { title, description, status } = req.body;

  if (!title) {
    return res.status(400).json({ error: "Title обязателен" });
  }

  const stmt = db.prepare("INSERT INTO tasks (title, description, status) VALUES (?, ?, ?)");
  const info = stmt.run(title, description || null, status || "todo");

  res.status(201).json({ id: info.lastInsertRowid, title, description, status: status || "todo" });
});

app.put("/tasks/:id", (req, res) => {
  const { id } = req.params;
  const { title, description, status } = req.body;

  const stmt = db.prepare("UPDATE tasks SET title = ?, description = ?, status = ? WHERE id = ?");
  const info = stmt.run(title, description, status, id);

  if (info.changes === 0) {
    return res.status(404).json({ error: "Задача не найдена" });
  }

  res.json({ id, title, description, status });
});

app.delete("/tasks/:id", (req, res) => {
  const { id } = req.params;

  const stmt = db.prepare("DELETE FROM tasks WHERE id = ?");
  const info = stmt.run(id);

  if (info.changes === 0) {
    return res.status(404).json({ error: "Задача не найдена" });
  }

  res.json({ message: "Задача удалена" });
});

app.listen(3000, () => console.log("Сервер запущен на http://localhost:3000"));
