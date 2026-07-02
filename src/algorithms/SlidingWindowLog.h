#ifndef SLIDINGWINDOWLOG_H
#define SLIDINGWINDOWLOG_H

#include "IRateLimiter.h"

#include<memory>
#include <atomic>
#include<chrono>
#include "../storage/IStorageProvider.h"
#include "../storage/RedisLuaScripts.h"
#include "../utils/RedisKeyBuilder.h"

class SlidingWindowLog : public IRateLimiter
{
private:
    int limit;
    int size;
    std::shared_ptr<IStorageProvider>storage;
    static std::atomic<uint64_t> requestCounter;
public:
    SlidingWindowLog(int limit,int size,std::shared_ptr<IStorageProvider>storage);

    bool allowRequest(const std::string& key) override;
};
#endif