#ifndef RULE_H
#define RULE_H

#include<string>

#include "../models/RateLimiterConfig.h"

class Rule
{
protected:
    int id;
    int priority;
    std::string path;
    std::string method;
    std::string userType;
    std::string apiKey;
    std::string ip;
    RateLimiterConfig config;
public:
    Rule()=default;

    Rule(int id,int priority,const std::string& path,const std::string& method,const std::string& userType
    ,const std::string& apiKey, const std::string& ip, const RateLimiterConfig& config);

    int getId() const;

    int getPriority() const;

    const std::string& getPath() const;
    
    const std::string& getMethod() const;
    
    const std::string& getUserType() const;

    const std::string& getApiKey() const;

    const std::string& getIp() const;

    const RateLimiterConfig& getConfig() const;
};
#endif