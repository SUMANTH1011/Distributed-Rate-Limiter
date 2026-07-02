#include "FixedWindow.h"
#include <chrono>

using namespace std;

FixedWindow::FixedWindow(int limit,int size,std::shared_ptr<IStorageProvider>storage)
{
    this->limit=limit;
    windowSize=size;
    this->storage=storage;
}
bool FixedWindow::allowRequest(const string &key)
{
    auto now = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();

    return storage->eval(
        RedisLuaScripts::FIXED_WINDOW,
        {
            RedisKeyBuilder::fixedWindow(key)
        },
        {
            std::to_string(limit),
            std::to_string(windowSize),
            std::to_string(now)
        }
    )==1;
}