#include "RateLimiterFactory.h"
#include "../algorithms/TokenBucket.h"
#include "../algorithms/FixedWindow.h"
#include "../algorithms/LeakyBucket.h"
#include "../algorithms/SlidingWindowLog.h"
#include "../algorithms/SlidingWindowCounter.h"

RateLimiterFactory::RateLimiterFactory(std::shared_ptr<IStorageProvider> storage)
    : storage(std::move(storage))
{
}

std::unique_ptr<IRateLimiter> RateLimiterFactory::createRateLimiter(const RateLimiterConfig& config)
{
    switch(config.algorithm)
    {
        case AlgorithmType::FIXED_WINDOW:
            return std::make_unique<FixedWindow>(config.limit,config.windowSize,storage);
        case AlgorithmType::TOKEN_BUCKET:
            return std::make_unique<TokenBucket>(config.capacity,config.refillRate,storage);
        case AlgorithmType::LEAKY_BUCKET:
            return std::make_unique<LeakyBucket>(config.capacity,config.leakRate,storage);
        case AlgorithmType::SLIDING_WINDOW_LOG:
            return std::make_unique<SlidingWindowLog>(config.limit,config.windowSize,storage);
        case AlgorithmType::SLIDING_WINDOW_COUNTER:
            return std::make_unique<SlidingWindowCounter>(config.limit,config.windowSize,storage);
        default:
            return nullptr;
    }
}