#include "InMemoryStorage.h"
#include<stdexcept>

std::optional<std::string> InMemoryStorage::get(const std::string& key)
{
    std::lock_guard<std::mutex>lock(mutex);
    auto it=storage.find(key);
    if(it==storage.end())
    {
        return std::nullopt;
    }
    return it->second;
}

void InMemoryStorage::set(const std::string& key,const std::string& value)
{
    std::lock_guard<std::mutex>lock(mutex);
    storage[key]=value;
}
bool InMemoryStorage::exists(const std::string& key)
{
    std::lock_guard<std::mutex>lock(mutex);
    return storage.find(key)!=storage.end();
}
void InMemoryStorage::remove(const std::string& key)
{
    std::lock_guard<std::mutex> lock(mutex);
    storage.erase(key);
}
long long InMemoryStorage::increment(const std::string&key)
{
    std::lock_guard<std::mutex> lock(mutex);
    long long val=0;
    auto it=storage.find(key);
    if(it!=storage.end())
    {
        val=std::stoll(it->second);
    }
    val++;
    storage[key]=std::to_string(val);
    return val;
}
void InMemoryStorage::expire(const std::string& key,int seconds)
{
    // No-op for in-memory storage.
}
long long InMemoryStorage::eval(const std::string&,const std::vector<std::string>&,
    const std::vector<std::string>&)
{
    throw std::logic_error(
        "Lua scripts are not supported by InMemoryStorage."
    );
}