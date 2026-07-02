#ifndef METRICS_H
#define METRICS_H

#include <atomic>
#include <string>

struct Metrics
{
     Metrics();
    std::atomic<long long> totalRequests{0};
    std::atomic<long long> allowedRequests{0};
    std::atomic<long long> rejectedRequests{0};

    std::atomic<long long> redisCalls{0};
    std::atomic<long long> redisFailures{0};

    std::atomic<long long> tokenBucketRequests{0};
    std::atomic<long long> fixedWindowRequests{0};
    std::atomic<long long> leakyBucketRequests{0};
    std::atomic<long long> slidingWindowLogRequests{0};
    std::atomic<long long> slidingWindowCounterRequests{0};

    std::atomic<long long> ruleReloads{0};

    long long startTime;
};

#endif