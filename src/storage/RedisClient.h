#ifndef REDIS_CLIENT_H
#define REDIS_CLIENT_H

#include <memory>

#if __has_include(<optional>)
#include <optional>
#elif __has_include(<experimental/optional>)
#include <experimental/optional>
namespace std { using experimental::optional; }
#else
#error "<optional> or <experimental/optional> is required"
#endif

#include <string>

#include<sw/redis++/redis++.h>

class RedisClient
{
private:
    std::shared_ptr<sw::redis::Redis> redis;
public:
    RedisClient(const std::string &host,int port);
    std::optional<std::string> get(const std::string& key);
    void set(const std::string& key,const std::string& value);
    bool exists(const std::string& key);
    void del(const std::string& key);
    long long incr(const std::string& key);
    void expire(const std::string& key,int seconds);
    long long eval(const std::string& script,const std::vector<std::string>& keys,
    const std::vector<std::string>& args);
};
#endif