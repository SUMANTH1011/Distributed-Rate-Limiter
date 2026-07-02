#include "LeakyBucket.h"

using namespace std;

LeakyBucket::LeakyBucket(int cap,double rate,std::shared_ptr<IStorageProvider>storage)
{
    this->cap=cap;
    leakRate=rate;
    this->storage=storage;
}
bool LeakyBucket::allowRequest(const string &key)
{   
    long long currentTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
    return storage->eval(
        RedisLuaScripts::LEAKY_BUCKET,
        {
             RedisKeyBuilder::leakyBucket(key),
            RedisKeyBuilder::leakyBucketLastLeak(key)
        },
        {
            std::to_string(cap),
            std::to_string(leakRate),
            std::to_string(currentTime)
        }
    )==1;
}