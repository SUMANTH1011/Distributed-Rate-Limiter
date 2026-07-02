#include "SlidingWindowLog.h"

using namespace std;

SlidingWindowLog::SlidingWindowLog(int limit,int size,std::shared_ptr<IStorageProvider>storage)
{
    this->limit=limit;
    this->size=size;
    this->storage=storage;
}
std::atomic<uint64_t> SlidingWindowLog::requestCounter{0};
bool SlidingWindowLog::allowRequest(const string &key)
{
    long long currentTime =
    std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch())
        .count();

    std::string requestId = std::to_string(currentTime) + "_" + std::to_string(requestCounter.fetch_add(1));
    
    long long result = storage->eval(
    RedisLuaScripts::SLIDING_WINDOW_LOG,
    {
        RedisKeyBuilder::slidingWindowLog(key)
    },
    {
        std::to_string(limit),
        std::to_string(size),
        std::to_string(currentTime),
        requestId
    }
);

return result == 1;
}