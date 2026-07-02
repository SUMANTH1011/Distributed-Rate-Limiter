#ifndef LOGGING_CONFIG_H
#define LOGGING_CONFIG_H

#include <string>

struct LoggingConfig
{
    std::string level = "INFO";

    bool console = true;

    bool file = false;

    std::string path = "logs/server.log";
};

#endif