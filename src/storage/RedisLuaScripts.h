#ifndef REDIS_LUA_SCRIPTS_H
#define REDIS_LUA_SCRIPTS_H

#include <string>

class RedisLuaScripts
{
public:

    static const std::string TOKEN_BUCKET;

    static const std::string FIXED_WINDOW;

    static const std::string LEAKY_BUCKET;

    static const std::string SLIDING_WINDOW_LOG;

    static const std::string SLIDING_WINDOW_COUNTER;
};

#endif