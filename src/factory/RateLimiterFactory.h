#ifndef RATE_LIMITER_FACTORY_H
#define RATE_LIMITER_FACTORY_H

#include<memory>

#include "../models/RateLimiterConfig.h"
#include "../algorithms/IRateLimiter.h"
#include "../storage/IStorageProvider.h"
class RateLimiterFactory
{
private:
    std::shared_ptr<IStorageProvider> storage;
public:
    explicit RateLimiterFactory(std::shared_ptr<IStorageProvider> storage);
    std::unique_ptr<IRateLimiter>createRateLimiter(const RateLimiterConfig&config);
};
#endif