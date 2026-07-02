#ifndef FIXEDWINDOW_H
#define FFIXEDWINDOW_H
#include "IRateLimiter.h"

#include "../storage/IStorageProvider.h"
#include <memory>
#include "../storage/RedisLuaScripts.h"
#include "../utils/RedisKeyBuilder.h"

class FixedWindow : public IRateLimiter
{
private:
    int limit;
    int windowSize;
    std::shared_ptr<IStorageProvider> storage;
public:
    FixedWindow(int limit,int windowSize,std::shared_ptr<IStorageProvider>storage);
    bool allowRequest(const std::string &key) override;
};
#endif