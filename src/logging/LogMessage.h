#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include<string>
#include<chrono>
#include "LogLevel.h"

struct LogMessage
{
    LogLevel level;
    std::string message;
    std::chrono::system_clock::time_point timeStamp;
    std::string threadId;
    
};
#endif