#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include <string>

struct ServerConfig
{
    int port = 8080;

    int threads = 4;

    bool enableMetrics = true;

    bool enableRuleReload = true;

    std::string host = "0.0.0.0";
};

#endif