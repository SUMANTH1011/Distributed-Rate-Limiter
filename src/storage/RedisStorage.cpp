#include "RedisStorage.h"

RedisStorage::RedisStorage(
    const std::string& host,
    int port,
    MetricsCollector* metricsCollector)
    : redisClient(host, port),
      metricsCollector(metricsCollector)
{
}

std::optional<std::string> RedisStorage::get(const std::string& key)
{
    try
    {
        if(metricsCollector)
            metricsCollector->recordRedisCall();

        return redisClient.get(key);
    }
    catch(...)
    {
        if(metricsCollector)
            metricsCollector->recordRedisFailure();
        throw;
    }
}

void RedisStorage::set(
    const std::string& key,
    const std::string& value)
{
    try
    {
        if(metricsCollector)
            metricsCollector->recordRedisCall();

        redisClient.set(key, value);
    }
    catch(...)
    {
        if(metricsCollector)
            metricsCollector->recordRedisFailure();
        throw;
    }
}

bool RedisStorage::exists(const std::string& key)
{
    try
    {
        if(metricsCollector)
            metricsCollector->recordRedisCall();

        return redisClient.exists(key);
    }
    catch(...)
    {
        if(metricsCollector)
            metricsCollector->recordRedisFailure();
        throw;
    }
}

void RedisStorage::remove(const std::string& key)
{
    try
    {
        if(metricsCollector)
            metricsCollector->recordRedisCall();

        redisClient.del(key);
    }
    catch(...)
    {
        if(metricsCollector)
            metricsCollector->recordRedisFailure();
        throw;
    }
}

long long RedisStorage::increment(const std::string& key)
{
    try
    {
        if(metricsCollector)
            metricsCollector->recordRedisCall();

        return redisClient.incr(key);
    }
    catch(...)
    {
        if(metricsCollector)
            metricsCollector->recordRedisFailure();
        throw;
    }
}

void RedisStorage::expire(
    const std::string& key,
    int seconds)
{
    try
    {
        if(metricsCollector)
            metricsCollector->recordRedisCall();

        redisClient.expire(key, seconds);
    }
    catch(...)
    {
        if(metricsCollector)
            metricsCollector->recordRedisFailure();
        throw;
    }
}

long long RedisStorage::eval(
    const std::string& script,
    const std::vector<std::string>& keys,
    const std::vector<std::string>& args)
{
    try
    {
        if(metricsCollector)
            metricsCollector->recordRedisCall();

        return redisClient.eval(script, keys, args);
    }
    catch(...)
    {
        if(metricsCollector)
            metricsCollector->recordRedisFailure();
        throw;
    }
}