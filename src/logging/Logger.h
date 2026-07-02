#ifndef LOGGER_H
#define LOGGER_H

#include<string>
#include <mutex>
#include "LogLevel.h"
class Logger
{
private:
    std::mutex logMutex;
    Logger() =default;
    std::string levelToString(LogLevel level) const;
    std::string currentTime() const;
public:
    Logger(const Logger&)=delete;
    Logger& operator=(const Logger&)=delete;
    static Logger& getInstance();
    void log(
        LogLevel level,
        const std::string& message
    );

    void info(
        const std::string& message
    );

    void debug(
        const std::string& message
    );

    void warning(
        const std::string& message
    );

    void error(
        const std::string& message
    );
};
#endif