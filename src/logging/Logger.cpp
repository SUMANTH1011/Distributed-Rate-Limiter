#include "Logger.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
Logger& Logger::getInstance()
{
    static Logger logger;
    return logger;
}

std::string Logger::levelToString(LogLevel level) const
{
    switch(level)
    {
         case LogLevel::Debug:
            return "DEBUG";

        case LogLevel::Info:
            return "INFO";

        case LogLevel::Warning:
            return "WARNING";

        case LogLevel::Error:
            return "ERROR";
    }
     return "UNKNOWN";
}
std::string Logger::currentTime() const
{
    auto now =
        std::chrono::system_clock::now();

    std::time_t time =
        std::chrono::system_clock::to_time_t(now);

    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif

    std::ostringstream out;

    out << std::put_time(
        &tm,
        "%Y-%m-%d %H:%M:%S"
    );

    return out.str();
}
void Logger::log(
    LogLevel level,
    const std::string& message)
{
    std::lock_guard<std::mutex> lock(logMutex);

    std::cout
        << "["
        << currentTime()
        << "] "
        << "["
        << levelToString(level)
        << "] "
        << "[Thread "
        << std::this_thread::get_id()
        << "] "
        << message
        << std::endl;
}
void Logger::info(
    const std::string& message)
{
    log(
        LogLevel::Info,
        message
    );
}

void Logger::debug(
    const std::string& message)
{
    log(
        LogLevel::Debug,
        message
    );
}

void Logger::warning(
    const std::string& message)
{
    log(
        LogLevel::Warning,
        message
    );
}

void Logger::error(
    const std::string& message)
{
    log(
        LogLevel::Error,
        message
    );
}