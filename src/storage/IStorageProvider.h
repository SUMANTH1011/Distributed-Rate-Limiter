#ifndef ISTORAGE_PROVIDER_H
#define ISTORAGE_PROVIDER_H

#if __has_include(<optional>)
#include <optional>
#elif __has_include(<experimental/optional>)
#include <experimental/optional>
namespace std { using experimental::optional; }
#else
#error "<optional> or <experimental/optional> is required"
#endif

#include <string>
#include <vector>

class IStorageProvider
{
public:

    virtual ~IStorageProvider() = default;

    virtual std::optional<std::string>
    get(const std::string& key) = 0;

    virtual void
    set(const std::string& key,
        const std::string& value) = 0;

    virtual bool
    exists(const std::string& key) = 0;

    virtual void
    remove(const std::string& key) = 0;

    virtual long long
    increment(const std::string& key) = 0;

    virtual void
    expire(const std::string& key,
           int seconds) = 0;

    virtual long long eval(
    const std::string& script,
    const std::vector<std::string>& keys,
    const std::vector<std::string>& args)=0;
};

#endif