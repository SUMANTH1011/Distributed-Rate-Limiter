#ifndef INMEMORY_STORAGE_H
#define INMEMORY_STORAGE_H

#include "IStorageProvider.h"

#include <unordered_map>
#include <mutex>

class InMemoryStorage : public IStorageProvider
{
private:
    std::unordered_map<std::string, std::string> storage;
    std::mutex mutex;
public:
    std::optional<std::string> get(const std::string& key) override;
    void set(const std::string& key,const std::string& value) override;
    bool exists(const std::string& key) override;
    void remove(const std::string& key) override;
    long long increment(const std::string& key) override;
    void expire(const std::string& key,int seconds) override;
    long long eval(const std::string& script, const std::vector<std::string>& keys,
        const std::vector<std::string>& args) override;
};

#endif