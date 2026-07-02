#ifndef REQUEST_CONTEXT_H
#define REQUEST_CONTEXT_H

#include <string>
#include <unordered_map>

class RequestContext
{
private:

    std::string userId;
    std::string ipAddress;
    std::string apiKey;
    std::string path;
    std::string method;
    std::string userType;
    std::string service;
    std::string region;
    std::string tenant;

    std::unordered_map<std::string, std::string> headers;
    std::unordered_map<std::string, std::string> queryParams;

public:

    RequestContext() = default;

    RequestContext(
        const std::string& userId,
        const std::string& ipAddress,
        const std::string& apiKey,
        const std::string& path,
        const std::string& method,
        const std::string& userType,
        const std::string& service,
        const std::string& region,
        const std::string& tenant
    );

    // Setters
    void setUserId(const std::string& userId);
    void setIpAddress(const std::string& ipAddress);
    void setApiKey(const std::string& apiKey);
    void setPath(const std::string& path);
    void setMethod(const std::string& method);
    void setUserType(const std::string& userType);
    void setService(const std::string& service);
    void setRegion(const std::string& region);
    void setTenant(const std::string& tenant);

    // Getters
    const std::string& getUserId() const;
    const std::string& getIpAddress() const;
    const std::string& getApiKey() const;
    const std::string& getPath() const;
    const std::string& getMethod() const;
    const std::string& getUserType() const;
    const std::string& getService() const;
    const std::string& getRegion() const;
    const std::string& getTenant() const;

    // Headers
    void setHeaders(const std::unordered_map<std::string, std::string>& headers);
    void setQueryParams(const std::unordered_map<std::string, std::string>& queryParams);

    void addHeader(const std::string& key,const std::string& value);
    void addQueryParam(const std::string& key,const std::string& value);

    const std::unordered_map<std::string, std::string>& getHeaders() const;
    const std::unordered_map<std::string, std::string>& getQueryParams() const;

    std::string getHeader(const std::string& key) const;
    std::string getQueryParam(const std::string& key) const;
};

#endif