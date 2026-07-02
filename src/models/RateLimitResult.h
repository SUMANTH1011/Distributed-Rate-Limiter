#ifndef RATE_LIMIT_RESULT_H
#define RATE_LIMIT_RESULT_H

#include "AlgorithmType.h"

struct RateLimitResult
{
    bool allowed=false;
    int ruleId=-1;
    AlgorithmType algorithm=AlgorithmType::TOKEN_BUCKET;
};
#endif