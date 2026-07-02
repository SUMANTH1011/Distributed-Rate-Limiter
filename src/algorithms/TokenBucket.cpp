#include "TokenBucket.h"
using namespace std;

TokenBucket::TokenBucket(int cap,int refill,std::shared_ptr<IStorageProvider>storage)
{
    capacity=cap;
    refillRate=refill;
    this->storage=storage;
}

bool TokenBucket::allowRequest(const string &key)
{
    long long currentTime=std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count();

    long long result=storage->eval(
        RedisLuaScripts::TOKEN_BUCKET,
        {
            RedisKeyBuilder::tokenBucket(key),
            RedisKeyBuilder::tokenBucketLastRefill(key)
        },
        {
            std::to_string(capacity),
            std::to_string(refillRate),
            std::to_string(currentTime)
        }
    );
    return  result==1;
}