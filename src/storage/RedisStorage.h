#ifndef REDIS_STORAGE_H
#define REDIS_STORAGE_H

#include "IStorageProvider.h"
#include "RedisClient.h"
#include "../monitoring/MetricsCollector.h"
class RedisStorage: public IStorageProvider
{
private:
    RedisClient redisClient;
     MetricsCollector* metricsCollector;
public:
    RedisStorage(const std::string &host,int port, MetricsCollector* metricsCollector = nullptr);
    std::optional<std::string>get(const std::string& key) override;
    void set(const std::string& key,const std::string& value) override;
    bool exists(const std::string& key) override;
    void remove(const std::string& key) override;
    long long increment(const std::string& key) override;
    void expire(const std::string& key,int seconds) override;
    long long eval(const std::string& script,const std::vector<std::string>&keys,
    const std::vector<std::string>&args)override;
};
#endif