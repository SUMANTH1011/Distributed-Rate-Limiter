#ifndef REDIS_CONFIG_H
#define REDIS_CONFIG_H

#include <string>

struct RedisConfig
{
    std::string host = "127.0.0.1";

    int port = 6379;
};

#endif