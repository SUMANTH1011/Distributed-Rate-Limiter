#include "RateLimiterManager.h"
#include "../logging/Logger.h"
#include <iostream>

RateLimiterManager::RateLimiterManager(
    std::shared_ptr<IStorageProvider> storage)
    : rateLimiterFactory(std::move(storage))
{
}

IRateLimiter* RateLimiterManager::getRateLimiter(const Rule& rule)
{
    std::lock_guard<std::mutex> lock(managerMutex);

    int id = rule.getId();

    auto it = limiters.find(id);

    if (it != limiters.end())
    {
        Logger::getInstance().debug(
    "Using Cached Limiter | RuleID=" +
    std::to_string(rule.getId())
);

        return it->second.get();
    }
    Logger::getInstance().info("Creating Limiter | RuleID=" +std::to_string(id));

    auto limiter = rateLimiterFactory.createRateLimiter(rule.getConfig());

    IRateLimiter* ptr = limiter.get();

    limiters.emplace(id, std::move(limiter));

    return ptr;
}