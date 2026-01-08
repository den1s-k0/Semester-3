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

const isValidStatus = (status) => {
  return ["todo", "in_progress", "done"].includes(status);
};

app.get("/", (req, res) => {
  res.send("API работает!");
});

app.get("/tasks", (req, res) => {
  const tasks = db.prepare("SELECT * FROM tasks ORDER BY id").all();
  res.json(tasks);
});

app.get("/tasks/:id", (req, res) => {
  const { id } = req.params;
  
  if (isNaN(id) || id <= 0) {
    return res.status(400).json({ error: "Некорректный ID" });
  }
  
  const task = db.prepare("SELECT * FROM tasks WHERE id = ?").get(id);
  
  if (!task) {
    return res.status(404).json({ error: "Задача не найдена" });
  }
  
  res.json(task);
});

app.post("/tasks", (req, res) => {
  const { title, description, status = "todo" } = req.body;

  if (!title || title.trim() === "") {
    return res.status(400).json({ error: "Title обязателен" });
  }

  if (status && !isValidStatus(status)) {
    return res.status(400).json({ error: "Статус должен быть: todo, in_progress или done" });
  }

  const stmt = db.prepare("INSERT INTO tasks (title, description, status) VALUES (?, ?, ?)");
  const info = stmt.run(title.trim(), description || null, status);
  
  const newTask = {
    id: info.lastInsertRowid,
    title: title.trim(),
    description: description || null,
    status
  };
  
  res.status(201).json(newTask);
});

app.put("/tasks/:id", (req, res) => {
  const { id } = req.params;
  const { title, description, status } = req.body;

  if (isNaN(id) || id <= 0) {
    return res.status(400).json({ error: "Некорректный ID" });
  }

  const existingTask = db.prepare("SELECT * FROM tasks WHERE id = ?").get(id);
  if (!existingTask) {
    return res.status(404).json({ error: "Задача не найдена" });
  }

  if (!title || title.trim() === "") {
    return res.status(400).json({ error: "Title обязателен для полного обновления" });
  }
  
  if (!status || !isValidStatus(status)) {
    return res.status(400).json({ error: "Статус обязателен и должен быть: todo, in_progress или done" });
  }

  const stmt = db.prepare("UPDATE tasks SET title = ?, description = ?, status = ? WHERE id = ?");
  const info = stmt.run(title.trim(), description || null, status, id);

  const updatedTask = {
    id: parseInt(id),
    title: title.trim(),
    description: description || null,
    status
  };
  
  res.json(updatedTask);
});

app.patch("/tasks/:id", (req, res) => {
  const { id } = req.params;
  const { title, description, status } = req.body;

  if (isNaN(id) || id <= 0) {
    return res.status(400).json({ error: "Некорректный ID" });
  }

  const existingTask = db.prepare("SELECT * FROM tasks WHERE id = ?").get(id);
  if (!existingTask) {
    return res.status(404).json({ error: "Задача не найдена" });
  }

  if (title === undefined && description === undefined && status === undefined) {
    return res.status(400).json({ error: "Не указаны поля для обновления" });
  }

  if (status !== undefined && !isValidStatus(status)) {
    return res.status(400).json({ error: "Статус должен быть: todo, in_progress или done" });
  }

  const newTitle = title !== undefined ? title.trim() : existingTask.title;
  const newDescription = description !== undefined ? description : existingTask.description;
  const newStatus = status !== undefined ? status : existingTask.status;

  if (title !== undefined && newTitle === "") {
    return res.status(400).json({ error: "Title не может быть пустым" });
  }

  const stmt = db.prepare("UPDATE tasks SET title = ?, description = ?, status = ? WHERE id = ?");
  stmt.run(newTitle, newDescription, newStatus, id);

  const updatedTask = {
    id: parseInt(id),
    title: newTitle,
    description: newDescription,
    status: newStatus
  };
  
  res.json(updatedTask);
});

app.delete("/tasks/:id", (req, res) => {
  const { id } = req.params;

  if (isNaN(id) || id <= 0) {
    return res.status(400).json({ error: "Некорректный ID" });
  }

  const stmt = db.prepare("DELETE FROM tasks WHERE id = ?");
  const info = stmt.run(id);

  if (info.changes === 0) {
    return res.status(404).json({ error: "Задача не найдена" });
  }

  res.json({ message: "Задача удалена" });
});

app.listen(3000, () => console.log("Сервер запущен на http://localhost:3000"));