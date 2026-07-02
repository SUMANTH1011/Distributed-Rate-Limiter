#include "Rule.h"

Rule::Rule(int id,int priority,const std::string& path,const std::string& method,const std::string& userType
    ,const std::string& apiKey, const std::string& ip, const
    RateLimiterConfig& config):id(id),priority(priority),path(path),method(method),userType(userType),
    apiKey(apiKey),ip(ip),config(config){}

int Rule::getId() const
{
    return id;
}

int Rule::getPriority() const
{
    return priority;
}

const std::string& Rule::getPath() const
{
    return path;
}

const std::string& Rule::getMethod() const
{
    return method;
}

const std::string& Rule::getUserType() const
{
    return userType;
}

const std::string& Rule::getApiKey() const
{
    return apiKey;
}

const std::string& Rule::getIp() const
{
    return ip;
}

const RateLimiterConfig& Rule::getConfig() const
{
    return config;
}