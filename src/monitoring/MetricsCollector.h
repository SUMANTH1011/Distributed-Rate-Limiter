#ifndef METRICS_COLLECTOR_H
#define METRICS_COLLECTOR_H

#include "Metrics.h"
#include "../models/AlgorithmType.h"
class MetricsCollector
{
private:
    Metrics metrics;

public:
    void recordRequest();
    void recordAllowed();
    void recordRejected();

    void recordRedisCall();
    void recordRedisFailure();

    void recordRuleReload();

    void recordAlgorithm(AlgorithmType algorithm);

    const Metrics& getMetrics() const;
};

#endif