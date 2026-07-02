#ifndef RATE_LIMITER_CONFIG_H
#define RATE_LIMITER_CONFIG_H

#include "AlgorithmType.h"
#include "KeyType.h"

struct  RateLimiterConfig
{
    AlgorithmType algorithm;
    KeyType keyType;
    int capacity=0;
    int refillRate=0;
    int limit=0;
    int windowSize=0;
    double leakRate=0.0;
};

#endif