#include "RedisClient.h"

RedisClient::RedisClient(const std::string& host,int port)
{
    sw::redis::ConnectionOptions options;
    options.host=host;
    options.port=port;
    redis=std::make_shared<sw::redis::Redis>(options);
}

std::optional<std::string>RedisClient::get(const std::string& key)
{
    auto value=redis->get(key);
    if(value)
        return *value;
    return std::nullopt;
}
void RedisClient::set(const std::string&key,const std::string& value)
{
    redis->set(key,value);
}
bool RedisClient::exists(const std::string&key)
{
    return redis->exists(key);
}
void RedisClient::del(const std::string&key)
{
    redis->del(key);
}
long long RedisClient::incr(const std::string&key)
{
    return redis->incr(key);
}
void RedisClient::expire(const std::string&key,int seconds)
{
    redis->expire(key,std::chrono::seconds(seconds));
}
long long RedisClient::eval(
    const std::string& scripts,
    const std::vector<std::string>& keys,
    const std::vector<std::string>& args)
{
    return redis->eval<long long>(
        scripts,
        keys.begin(),
        keys.end(),
        args.begin(),
        args.end()
    );
}