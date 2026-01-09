const express = require("express");
const router = express.Router();
const { db } = require("../database");
const { 
  generateToken, 
  hashPassword, 
  comparePassword 
} = require("../auth");

router.post("/register", async (req, res) => {
  try {
    const { username, password } = req.body;
    
    if (!username || !password) {
      return res.status(400).json({
        error: "Неверные данные",
        message: "Имя пользователя и пароль обязательны"
      });
    }
    
    if (password.length < 6) {
      return res.status(400).json({
        error: "Слабый пароль",
        message: "Пароль должен содержать минимум 6 символов"
      });
    }
    
    const existingUser = db.prepare("SELECT id FROM users WHERE username = ?").get(username);
    if (existingUser) {
      return res.status(409).json({
        error: "Пользователь уже существует",
        message: "Пожалуйста, выберите другое имя пользователя"
      });
    }
    
    const hashedPassword = await hashPassword(password);
    
    const stmt = db.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    const result = stmt.run(username, hashedPassword);
    
    const token = generateToken(result.lastInsertRowid, username);
    
    res.status(201).json({
      message: "Пользователь успешно зарегистрирован",
      token,
      user: {
        id: result.lastInsertRowid,
        username
      }
    });
    
  } catch (error) {
    console.error("Ошибка регистрации:", error);
    res.status(500).json({
      error: "Ошибка сервера",
      message: "Не удалось зарегистрировать пользователя"
    });
  }
});

router.post("/login", async (req, res) => {
  try {
    const { username, password } = req.body;
    
    if (!username || !password) {
      return res.status(400).json({
        error: "Неверные данные",
        message: "Имя пользователя и пароль обязательны"
      });
    }
    
    const user = db.prepare("SELECT * FROM users WHERE username = ?").get(username);
    
    if (!user) {
      return res.status(401).json({
        error: "Ошибка авторизации",
        message: "Неверное имя пользователя или пароль"
      });
    }
    
    const isPasswordValid = await comparePassword(password, user.password);
    
    if (!isPasswordValid) {
      return res.status(401).json({
        error: "Ошибка авторизации",
        message: "Неверное имя пользователя или пароль"
      });
    }
    
    const token = generateToken(user.id, user.username);
    
    res.json({
      message: "Успешный вход",
      token,
      user: {
        id: user.id,
        username: user.username,
        createdAt: user.created_at
      }
    });
    
  } catch (error) {
    console.error("Ошибка входа:", error);
    res.status(500).json({
      error: "Ошибка сервера",
      message: "Не удалось выполнить вход"
    });
  }
});

router.get("/me", (req, res) => {
  if (!req.user) {
    return res.status(401).json({
      error: "Не авторизован",
      message: "Требуется авторизация"
    });
  }
  
  res.json({
    user: req.user
  });
});

module.exports = router;