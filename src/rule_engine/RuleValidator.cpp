#include "RuleValidator.h"

bool RuleValidator::validate(const Rule& rule) const
{
    if(!validateCommon(rule))
    {
        return false;
    }
    switch(rule.getConfig().algorithm)
    {
        case AlgorithmType::TOKEN_BUCKET:
            return validateTokenBucket(rule);
        case AlgorithmType::FIXED_WINDOW:
            return validateFixedWindow(rule);
        case AlgorithmType::LEAKY_BUCKET:
            return validateLeakyBucket(rule);
        case AlgorithmType::SLIDING_WINDOW_LOG:
            return validateSlidingWindowLog(rule);
        case AlgorithmType::SLIDING_WINDOW_COUNTER:
            return validateSlidingWindowCounter(rule);
        default:    
            return false;
    }
}
bool RuleValidator::validateCommon(const Rule& rule) const
{
    if(rule.getId() <= 0)
        return false;

    if(rule.getPriority() <= 0)
        return false;

    return true;
}

bool RuleValidator::validateTokenBucket(const Rule& rule) const
{
    const auto & config=rule.getConfig();
    if(config.capacity<0)
    {
        return false;
    }
    if(config.refillRate<0)
    {
        return false;
    }
    return true;
}
bool RuleValidator::validateFixedWindow(const Rule& rule) const
{
    const auto& config=rule.getConfig();
    if(config.windowSize<0)
    {
        return false;
    }
    if(config.limit<0)
    {
        return false;
    }
    return true;
}
bool RuleValidator::validateSlidingWindowCounter(const Rule& rule)const
{
    const auto& config=rule.getConfig();
    return config.limit > 0 && config.windowSize > 0;
}
bool RuleValidator::validateSlidingWindowLog(const Rule&rule) const
{
    const auto& config=rule.getConfig();
    return config.limit>0 && config.windowSize>0;
}
bool RuleValidator::validateLeakyBucket(const Rule& rule) const
{
    const auto& config = rule.getConfig();

    return config.capacity > 0 && config.leakRate > 0;
}