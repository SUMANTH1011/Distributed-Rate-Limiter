#ifndef TOKENBUCKET_H
#define TOKENBUCKET_H

#include "IRateLimiter.h"
#include <memory>
#include<chrono>
#include "../storage/IStorageProvider.h"
#include "../storage/RedisLuaScripts.h"
#include "../utils/RedisKeyBuilder.h"

class TokenBucket : public IRateLimiter
{
private:
    int capacity;
    int refillRate;
    std::shared_ptr<IStorageProvider> storage;
public:
    TokenBucket(int capacity,int refillRate,std::shared_ptr<IStorageProvider>storage);
    bool allowRequest(const std::string &key) override;
};

#endif