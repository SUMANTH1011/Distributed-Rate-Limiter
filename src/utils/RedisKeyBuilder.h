#ifndef REDIS_KEY_BUILDER_H
#define REDIS_KEY_BUILDER_H

#include<string>
class RedisKeyBuilder
{
public:
    static std::string tokenBucket(const std::string& key);
    static std::string tokenBucketLastRefill(const std::string& key);

    static std::string fixedWindow(const std::string& key);

    static std::string leakyBucket(const std::string& key);
    static std::string leakyBucketLastLeak(const std::string& key);

    static std::string slidingWindowLog(const std::string& key);

    static std::string slidingCounterCurrent(const std::string& key);
    static std::string slidingCounterPrevious(const std::string& key);
    static std::string slidingCounterWindowStart(const std::string& key);
};
#endif