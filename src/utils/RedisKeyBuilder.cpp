#include "RedisKeyBuilder.h"

// Token Bucket
std::string RedisKeyBuilder::tokenBucket(const std::string& key)
{
    return "ratelimit:token:" + key;
}

std::string RedisKeyBuilder::tokenBucketLastRefill(const std::string& key)
{
    return "ratelimit:token:last:" + key;
}

// Fixed Window
std::string RedisKeyBuilder::fixedWindow(const std::string& key)
{
    return "ratelimit:fixed:" + key;
}

// Leaky Bucket
std::string RedisKeyBuilder::leakyBucket(const std::string& key)
{
    return "ratelimit:leaky:" + key;
}

std::string RedisKeyBuilder::leakyBucketLastLeak(const std::string& key)
{
    return "ratelimit:leaky:last:" + key;
}

// Sliding Window Log
std::string RedisKeyBuilder::slidingWindowLog(const std::string& key)
{
    return "ratelimit:slidinglog:" + key;
}

// Sliding Window Counter
std::string RedisKeyBuilder::slidingCounterCurrent(const std::string& key)
{
    return "ratelimit:slidingcounter:current:" + key;
}

std::string RedisKeyBuilder::slidingCounterPrevious(const std::string& key)
{
    return "ratelimit:slidingcounter:previous:" + key;
}

std::string RedisKeyBuilder::slidingCounterWindowStart(const std::string& key)
{
    return "ratelimit:slidingcounter:start:" + key;
}