#ifndef STATISTICS_H
#define STATISTICS_H

#include "Metrics.h"

class Statistics
{
public:

    static double successRate(const Metrics& metrics);

    static double rejectionRate(const Metrics& metrics);

    static double redisFailureRate(const Metrics& metrics);

    static long long totalProcessed(const Metrics& metrics);
};

#endif