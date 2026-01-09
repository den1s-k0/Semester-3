class RateLimiter {
  constructor(windowMs = 60000, maxRequests = 100) {
    this.windowMs = windowMs;
    this.maxRequests = maxRequests;
    this.requests = new Map();
    
    setInterval(() => this.cleanup(), 300000);
  }

  check(ip) {
    const now = Date.now();
    const windowStart = now - this.windowMs;
    
    if (!this.requests.has(ip)) {
      this.requests.set(ip, []);
    }
    
    const timestamps = this.requests.get(ip);
    
    const validTimestamps = timestamps.filter(time => time > windowStart);
    
    if (validTimestamps.length >= this.maxRequests) {
      const oldestRequest = validTimestamps[0];
      const resetTime = Math.ceil((oldestRequest + this.windowMs - now) / 1000);
      return {
        allowed: false,
        remaining: 0,
        reset: resetTime
      };
    }
    
    validTimestamps.push(now);
    this.requests.set(ip, validTimestamps);
    
    return {
      allowed: true,
      remaining: this.maxRequests - validTimestamps.length,
      reset: Math.ceil(this.windowMs / 1000)
    };
  }

  cleanup() {
    const now = Date.now();
    const windowStart = now - this.windowMs;
    
    for (const [ip, timestamps] of this.requests.entries()) {
      const validTimestamps = timestamps.filter(time => time > windowStart);
      if (validTimestamps.length === 0) {
        this.requests.delete(ip);
      } else {
        this.requests.set(ip, validTimestamps);
      }
    }
  }

  getStats() {
    return {
      totalIPs: this.requests.size,
      windowMs: this.windowMs,
      maxRequests: this.maxRequests
    };
  }
}

const rateLimiter = new RateLimiter(60000, 100);

// Middleware для rate limiting
const rateLimitMiddleware = (req, res, next) => {
  const ip = req.ip || req.connection.remoteAddress;
  const result = rateLimiter.check(ip);
  
  if (!result.allowed) {
    res.setHeader('X-RateLimit-Limit', rateLimiter.maxRequests);
    res.setHeader('X-RateLimit-Remaining', result.remaining);
    res.setHeader('X-RateLimit-Reset', result.reset);
    
    return res.status(429).json({
      error: "Слишком много запросов",
      message: `Превышен лимит запросов. Попробуйте через ${result.reset} секунд.`,
      retryAfter: result.reset
    });
  }
  
  res.setHeader('X-RateLimit-Limit', rateLimiter.maxRequests);
  res.setHeader('X-RateLimit-Remaining', result.remaining);
  res.setHeader('X-RateLimit-Reset', result.reset);
  
  next();
};

module.exports = { rateLimiter, rateLimitMiddleware };