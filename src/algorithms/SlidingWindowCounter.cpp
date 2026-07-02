#include "SlidingWindowCounter.h"

using namespace std;

SlidingWindowCounter::SlidingWindowCounter(int limit,int size,std::shared_ptr<IStorageProvider>storage)
{
    this->limit=limit;
    windowSize=size;
    this->storage=storage;
}
bool SlidingWindowCounter::allowRequest(const string &key)
{
    long long currentTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

        long long result = storage->eval(
        RedisLuaScripts::SLIDING_WINDOW_COUNTER,
        {
            RedisKeyBuilder::slidingCounterCurrent(key),
            RedisKeyBuilder::slidingCounterPrevious(key),
            RedisKeyBuilder::slidingCounterWindowStart(key)
        },
        {
            std::to_string(limit),
            std::to_string(windowSize),
            std::to_string(currentTime)
        }
    );

    return result == 1;
}