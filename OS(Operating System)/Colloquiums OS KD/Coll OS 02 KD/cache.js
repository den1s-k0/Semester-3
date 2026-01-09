class Cache {
  constructor() {
    this.data = new Map();
    this.startCleanupInterval();
  }

  get(key) {
    const item = this.data.get(key);
    if (!item) return null;
    
    if (item.expires < Date.now()) {
      this.data.delete(key);
      return null;
    }
    
    return item.value;
  }

  set(key, value, ttl = 30000) {
    this.data.set(key, {
      value,
      expires: Date.now() + ttl
    });
  }

  delete(key) {
    this.data.delete(key);
  }

  clear() {
    this.data.clear();
  }

  clearPattern(pattern) {
    for (const key of this.data.keys()) {
      if (key.includes(pattern)) {
        this.data.delete(key);
      }
    }
  }

  startCleanupInterval(interval = 60000) {
    setInterval(() => {
      const now = Date.now();
      for (const [key, item] of this.data.entries()) {
        if (item.expires < now) {
          this.data.delete(key);
        }
      }
    }, interval);
  }

  getStats() {
    return {
      size: this.data.size,
      keys: Array.from(this.data.keys())
    };
  }
}

const cache = new Cache();

const cacheMiddleware = (req, res, next) => {
  if (req.method !== "GET") {
    return next();
  }
  
  const cacheKey = req.originalUrl;
  const cachedData = cache.get(cacheKey);
  
  if (cachedData) {
    console.log(`[Cache] HIT: ${cacheKey}`);
    return res.json(cachedData);
  }
  
  console.log(`[Cache] MISS: ${cacheKey}`);
  
  const originalJson = res.json;
  res.json = function(data) {
    if (res.statusCode === 200) {
      cache.set(cacheKey, data, 15000);
    }
    originalJson.call(this, data);
  };
  
  next();
};

module.exports = { cache, cacheMiddleware };