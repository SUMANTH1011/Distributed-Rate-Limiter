#ifndef RATE_LIMITER_MANAGER_H
#define RATE_LIMITER_MANAGER_H

#include <memory>
#include <unordered_map>
#include <mutex>
#include "../algorithms/IRateLimiter.h"
#include "../factory/RateLimiterFactory.h"
#include "../rule_engine/Rule.h"
#include "../storage/IStorageProvider.h"

class RateLimiterManager
{
private:

    std::unordered_map<
        int,
        std::unique_ptr<IRateLimiter>
    > limiters;
    RateLimiterFactory rateLimiterFactory;
    std::mutex managerMutex;

public:
    explicit RateLimiterManager(std::shared_ptr<IStorageProvider> storage);
    IRateLimiter* getRateLimiter(
        const Rule& rule
    );

};

#endif