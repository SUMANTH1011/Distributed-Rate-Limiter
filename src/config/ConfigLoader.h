#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include "RedisConfig.h"
#include "../server/ServerConfig.h"
#include "LoggingConfig.h"

class ConfigLoader
{
public:

    ServerConfig loadServerConfig(
        const std::string& fileName
    ) const;

    RedisConfig loadRedisConfig(
        const std::string& fileName
    ) const;

    LoggingConfig loadLoggingConfig(
        const std::string& fileName
    ) const;
};

#endif