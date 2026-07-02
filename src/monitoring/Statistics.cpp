#include "Statistics.h"

double Statistics::successRate(const Metrics& metrics)
{
    long long total = metrics.totalRequests.load();

    if (total == 0)
        return 0.0;

    return (metrics.allowedRequests.load() * 100.0) / total;
}

double Statistics::rejectionRate(const Metrics& metrics)
{
    long long total = metrics.totalRequests.load();

    if (total == 0)
        return 0.0;

    return (metrics.rejectedRequests.load() * 100.0) / total;
}

double Statistics::redisFailureRate(const Metrics& metrics)
{
    long long calls = metrics.redisCalls.load();

    if (calls == 0)
        return 0.0;

    return (metrics.redisFailures.load() * 100.0) / calls;
}

long long Statistics::totalProcessed(const Metrics& metrics)
{
    return metrics.totalRequests.load();
}