#include "ConfigLoader.h"

#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

ServerConfig ConfigLoader::loadServerConfig(
    const std::string& fileName) const
{
    std::ifstream input(fileName);

    if(!input.is_open())
    {
        throw std::runtime_error(
            "Unable to open " + fileName
        );
    }

    json root;

    input >> root;

    ServerConfig config;

    config.host =
        root.value("host", "0.0.0.0");

    config.port =
        root.value("port", 8080);

    config.threads =
        root.value("threads", 8);

    config.enableMetrics =
        root.value("enableMetrics", true);

    config.enableRuleReload =
        root.value("enableRuleReload", true);

    return config;
}

RedisConfig ConfigLoader::loadRedisConfig(const std::string& fileName) const
{
std::ifstream input(fileName);

    if(!input.is_open())
    {
        throw std::runtime_error(
            "Unable to open " + fileName
        );
    }

    json root;

    input >> root;

    RedisConfig config;

    config.host =
        root.value("host", "127.0.0.1");

    config.port =
        root.value("port", 6379);

    return config;
}
LoggingConfig ConfigLoader::loadLoggingConfig(
    const std::string& fileName) const
{
    std::ifstream input(fileName);

    if(!input.is_open())
    {
        throw std::runtime_error(
            "Unable to open " + fileName
        );
    }

    json root;

    input >> root;

    LoggingConfig config;

    config.level =
        root.value("level", "INFO");

    config.console =
        root.value("console", true);

    config.file =
        root.value("file", false);

    config.path =
        root.value("path", "logs/server.log");

    return config;
}