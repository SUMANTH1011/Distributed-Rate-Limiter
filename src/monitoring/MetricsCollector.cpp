#include "MetricsCollector.h"

void MetricsCollector::recordRequest()
{
    metrics.totalRequests++;
}

void MetricsCollector::recordAllowed()
{
    metrics.allowedRequests++;
}

void MetricsCollector::recordRejected()
{
    metrics.rejectedRequests++;
}

void MetricsCollector::recordRedisCall()
{
    metrics.redisCalls++;
}

void MetricsCollector::recordRedisFailure()
{
    metrics.redisFailures++;
}

void MetricsCollector::recordRuleReload()
{
    metrics.ruleReloads++;
}

void MetricsCollector::recordAlgorithm(AlgorithmType algorithm)
{
    switch (algorithm)
    {
        case AlgorithmType::TOKEN_BUCKET:
            metrics.tokenBucketRequests++;
            break;

        case AlgorithmType::FIXED_WINDOW:
            metrics.fixedWindowRequests++;
            break;

        case AlgorithmType::LEAKY_BUCKET:
            metrics.leakyBucketRequests++;
            break;

        case AlgorithmType::SLIDING_WINDOW_LOG:
            metrics.slidingWindowLogRequests++;
            break;

        case AlgorithmType::SLIDING_WINDOW_COUNTER:
            metrics.slidingWindowCounterRequests++;
            break;
    }
}

const Metrics& MetricsCollector::getMetrics() const
{
    return metrics;
}