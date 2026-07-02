#ifndef LEAKYBUCKET_H
#define LEAKYBUCKET_H

#include "IRateLimiter.h"
#include <memory>
#include<chrono>
#include "../storage/IStorageProvider.h"
#include "../storage/RedisLuaScripts.h"
#include "../utils/RedisKeyBuilder.h"

class LeakyBucket : public IRateLimiter
{
private:
    int cap;
    double leakRate;
    std::shared_ptr<IStorageProvider>storage;
public:
    LeakyBucket(int cap,double leakRate,std::shared_ptr<IStorageProvider>storage);
    bool allowRequest(const std::string &key) override;
};
#endif