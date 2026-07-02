#include "RedisLuaScripts.h"

const std::string RedisLuaScripts::TOKEN_BUCKET = R"(
local tokens = redis.call("GET", KEYS[1])

if not tokens then
    tokens = tonumber(ARGV[1])
else
    tokens = tonumber(tokens)
end

local last = redis.call("GET", KEYS[2])

if not last then
    last = tonumber(ARGV[3])
else
    last = tonumber(last)
end

local elapsed = (tonumber(ARGV[3]) - last) / 1000.0
redis.call("SET", "debug:elapsed", elapsed)
local refill = elapsed * tonumber(ARGV[2])

tokens = math.min(
    tonumber(ARGV[1]),
    tokens + refill
)

if tokens >= 1 then
    tokens = tokens - 1

    redis.call("SET", KEYS[1], tokens)
    redis.call("SET", KEYS[2], ARGV[3])

    return 1
end

return 0
)";

const std::string RedisLuaScripts::FIXED_WINDOW = R"(
local current = redis.call("INCR", KEYS[1])

if current == 1 then
    redis.call("EXPIRE", KEYS[1], tonumber(ARGV[2]))
end

if current <= tonumber(ARGV[1]) then
    return 1
end

return 0
)";

const std::string RedisLuaScripts::LEAKY_BUCKET = R"(
local water = redis.call("GET", KEYS[1])

if not water then
    water = 0
else
    water = tonumber(water)
end

local last = redis.call("GET", KEYS[2])

if not last then
    last = tonumber(ARGV[3])
else
    last = tonumber(last)
end

local elapsed = (tonumber(ARGV[3]) - last) / 1000.0

local leaked = elapsed * tonumber(ARGV[2])

water = math.max(0, water - leaked)

if water < tonumber(ARGV[1]) then

    water = water + 1

    redis.call("SET", KEYS[1], water)
    redis.call("SET", KEYS[2], ARGV[3])

    return 1
end

return 0
)";

const std::string RedisLuaScripts::SLIDING_WINDOW_LOG = R"(
local limit = tonumber(ARGV[1])
local window = tonumber(ARGV[2])
local now = tonumber(ARGV[3])

local minTime = now - (window * 1000)

redis.call(
    "ZREMRANGEBYSCORE",
    KEYS[1],
    0,
    minTime
)

local count = redis.call("ZCARD", KEYS[1])

if count < limit then

    redis.call(
        "ZADD",
        KEYS[1],
        now,
        ARGV[4]
    )

    redis.call(
        "EXPIRE",
        KEYS[1],
        window
    )

    return 1
end

return 0
)";

const std::string RedisLuaScripts::SLIDING_WINDOW_COUNTER = R"(
local now = tonumber(ARGV[3])
local limit = tonumber(ARGV[1])
local window = tonumber(ARGV[2])

local windowStart = redis.call("GET", KEYS[3])

if not windowStart then
    windowStart = now
    redis.call("SET", KEYS[3], windowStart)
end

windowStart = tonumber(windowStart)

-- Rotate window if expired
if now >= windowStart + (window * 1000) then

    local current = redis.call("GET", KEYS[1])

    if not current then
        current = 0
    end

    redis.call("SET", KEYS[2], current)
    redis.call("SET", KEYS[1], 0)
    redis.call("SET", KEYS[3], now)

    windowStart = now
end

local current = tonumber(redis.call("GET", KEYS[1]) or 0)
local previous = tonumber(redis.call("GET", KEYS[2]) or 0)

local elapsed = (now - windowStart) / 1000.0

local weight = 1.0 - (elapsed / window)

if weight < 0 then
    weight = 0
end

local estimated = current + (previous * weight)

if estimated >= limit then
    return 0
end

redis.call("INCR", KEYS[1])

return 1
)";