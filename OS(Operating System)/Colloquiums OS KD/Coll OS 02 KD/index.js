const express = require("express");
const cors = require("cors");

const { initDatabase } = require("./database");
const { cacheMiddleware } = require("./cache");
const { rateLimitMiddleware } = require("./rateLimiter");
const { authMiddleware } = require("./auth");
const authRoutes = require("./routes/auth");
const taskRoutes = require("./routes/tasks");

const app = express();
const PORT = process.env.PORT || 3000;

app.use(cors());
app.use(express.json());
app.use(rateLimitMiddleware);
app.use(cacheMiddleware);

app.get("/", (req, res) => {
  res.json({
    message: "To-Do List API работает.",
    version: "1.0.0",
    endpoints: {
      auth: {
        register: "POST /auth/register",
        login: "POST /auth/login",
        me: "GET /auth/me (требует токен)"
      },
      tasks: {
        getAll: "GET /tasks (требует токен)",
        getOne: "GET /tasks/:id (требует токен)",
        create: "POST /tasks (требует токен)",
        update: "PUT /tasks/:id (требует токен)",
        patch: "PATCH /tasks/:id (требует токен)",
        delete: "DELETE /tasks/:id (требует токен)"
      }
    },
  });
});

app.use("/auth", authRoutes);

app.use("/tasks", authMiddleware, taskRoutes);

app.use((req, res) => {
  res.status(404).json({
    error: "Маршрут не найден",
    message: `Запрошенный путь ${req.path} не существует`
  });
});

app.use((err, req, res, next) => {
  console.error("Ошибка сервера:", err);
  res.status(500).json({
    error: "Внутренняя ошибка сервера",
    message: process.env.NODE_ENV === 'development' ? err.message : 'Что-то пошло не так'
  });
});

const startServer = async () => {
  try {
    await initDatabase();
    
    app.listen(PORT, () => {
      console.log(`Сервер запущен на порту ${PORT}`);
      console.log(`API доступен по адресу: http://localhost:${PORT}`);
      console.log(`Тестовый пользователь: admin / admin123`);
      console.log("Используйте токен для доступа к /tasks");
    });
  } catch (error) {
    console.error("Ошибка запуска сервера:", error);
    process.exit(1);
  }
};

startServer();

module.exports = app;