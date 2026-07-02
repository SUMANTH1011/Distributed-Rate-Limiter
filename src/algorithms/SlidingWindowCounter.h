#ifndef SLIDINGWINDOWCOUNTER_H
#define SLIDINGWINDOWCOUNTER_H

#include "IRateLimiter.h"
#include "../storage/IStorageProvider.h"
#include <memory>
#include "../storage/RedisLuaScripts.h"
#include "../utils/RedisKeyBuilder.h"
#include<chrono>

class SlidingWindowCounter : public IRateLimiter
{
private:
    int limit;
    int windowSize;
    std::shared_ptr<IStorageProvider>storage;
public:
    SlidingWindowCounter(int limit,int WindowSize,std::shared_ptr<IStorageProvider>storage);
    bool allowRequest(const std::string &key) override;
};
#endif