const express = require("express");
const router = express.Router();
const { db } = require("../database");
const { cache } = require("../cache");

const isValidStatus = (status) => {
  return ["todo", "in_progress", "done"].includes(status);
};

router.get("/", (req, res) => {
  try {
    const tasks = db.prepare(`
      SELECT * FROM tasks 
      WHERE user_id = ? 
      ORDER BY created_at DESC
    `).all(req.user.id);
    
    res.json(tasks);
  } catch (error) {
    console.error("Ошибка получения задач:", error);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

router.get("/:id", (req, res) => {
  try {
    const { id } = req.params;
    
    if (isNaN(id) || id <= 0) {
      return res.status(400).json({ error: "Некорректный ID" });
    }
    
    const task = db.prepare(`
      SELECT * FROM tasks 
      WHERE id = ? AND user_id = ?
    `).get(id, req.user.id);
    
    if (!task) {
      return res.status(404).json({ error: "Задача не найдена" });
    }
    
    res.json(task);
  } catch (error) {
    console.error("Ошибка получения задачи:", error);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

router.post("/", (req, res) => {
  try {
    const { title, description, status = "todo" } = req.body;
    
    if (!title || title.trim() === "") {
      return res.status(400).json({ error: "Название задачи обязательно" });
    }
    
    if (status && !isValidStatus(status)) {
      return res.status(400).json({ 
        error: "Неверный статус", 
        message: "Статус должен быть: todo, in_progress или done" 
      });
    }
    
    const stmt = db.prepare(`
      INSERT INTO tasks (title, description, status, user_id) 
      VALUES (?, ?, ?, ?)
    `);
    
    const result = stmt.run(
      title.trim(),
      description || null,
      status,
      req.user.id
    );
    
    cache.clearPattern("/tasks");
    
    const createdTask = db.prepare(`
      SELECT * FROM tasks WHERE id = ?
    `).get(result.lastInsertRowid);
    
    res.status(201).json(createdTask);
    
  } catch (error) {
    console.error("Ошибка создания задачи:", error);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

router.put("/:id", (req, res) => {
  try {
    const { id } = req.params;
    const { title, description, status } = req.body;
    
    if (isNaN(id) || id <= 0) {
      return res.status(400).json({ error: "Некорректный ID" });
    }
    
    const existingTask = db.prepare(`
      SELECT id FROM tasks WHERE id = ? AND user_id = ?
    `).get(id, req.user.id);
    
    if (!existingTask) {
      return res.status(404).json({ error: "Задача не найдена" });
    }
    
    if (!title || title.trim() === "") {
      return res.status(400).json({ error: "Название задачи обязательно" });
    }
    
    if (!status || !isValidStatus(status)) {
      return res.status(400).json({ 
        error: "Статус обязателен", 
        message: "Статус должен быть: todo, in_progress или done" 
      });
    }
    
    const stmt = db.prepare(`
      UPDATE tasks 
      SET title = ?, description = ?, status = ?, updated_at = CURRENT_TIMESTAMP
      WHERE id = ? AND user_id = ?
    `);
    
    stmt.run(
      title.trim(),
      description || null,
      status,
      id,
      req.user.id
    );
    
    cache.clearPattern("/tasks");
    
    const updatedTask = db.prepare(`
      SELECT * FROM tasks WHERE id = ?
    `).get(id);
    
    res.json(updatedTask);
    
  } catch (error) {
    console.error("Ошибка обновления задачи:", error);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

// Частичное обновление задачи (PATCH)
router.patch("/:id", (req, res) => {
  try {
    const { id } = req.params;
    
    // Валидация ID
    if (isNaN(id) || id <= 0) {
      return res.status(400).json({ error: "Некорректный ID" });
    }
    
    // Получаем текущую задачу
    const currentTask = db.prepare(`
      SELECT * FROM tasks WHERE id = ? AND user_id = ?
    `).get(id, req.user.id);
    
    if (!currentTask) {
      return res.status(404).json({ error: "Задача не найдена" });
    }
    
    // Проверяем, есть ли поля для обновления
    const { title, description, status } = req.body;
    if (title === undefined && description === undefined && status === undefined) {
      return res.status(400).json({ 
        error: "Нет данных для обновления",
        message: "Укажите title, description или status" 
      });
    }
    
    // Валидация статуса если передан
    if (status !== undefined && !isValidStatus(status)) {
      return res.status(400).json({ 
        error: "Неверный статус", 
        message: "Статус должен быть: todo, in_progress или done" 
      });
    }
    
    // Подготавливаем обновленные данные
    const updatedTitle = title !== undefined ? title.trim() : currentTask.title;
    const updatedDescription = description !== undefined ? description : currentTask.description;
    const updatedStatus = status !== undefined ? status : currentTask.status;
    
    // Проверяем title если он был обновлен
    if (title !== undefined && updatedTitle === "") {
      return res.status(400).json({ error: "Название задачи не может быть пустым" });
    }
    
    // Обновляем задачу
    const stmt = db.prepare(`
      UPDATE tasks 
      SET title = ?, description = ?, status = ?, updated_at = CURRENT_TIMESTAMP
      WHERE id = ? AND user_id = ?
    `);
    
    stmt.run(
      updatedTitle,
      updatedDescription,
      updatedStatus,
      id,
      req.user.id
    );
    
    // Очищаем кеш
    cache.clearPattern("/tasks");
    
    // Получаем обновленную задачу
    const updatedTask = db.prepare(`
      SELECT * FROM tasks WHERE id = ?
    `).get(id);
    
    res.json(updatedTask);
    
  } catch (error) {
    console.error("Ошибка частичного обновления:", error);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

// Удалить задачу
router.delete("/:id", (req, res) => {
  try {
    const { id } = req.params;
    
    // Валидация ID
    if (isNaN(id) || id <= 0) {
      return res.status(400).json({ error: "Некорректный ID" });
    }
    
    // Удаляем задачу
    const stmt = db.prepare(`
      DELETE FROM tasks 
      WHERE id = ? AND user_id = ?
    `);
    
    const result = stmt.run(id, req.user.id);
    
    if (result.changes === 0) {
      return res.status(404).json({ error: "Задача не найдена" });
    }
    
    // Очищаем кеш
    cache.clearPattern("/tasks");
    
    res.json({ 
      message: "Задача успешно удалена",
      deletedId: id 
    });
    
  } catch (error) {
    console.error("Ошибка удаления задачи:", error);
    res.status(500).json({ error: "Ошибка сервера" });
  }
});

module.exports = router;