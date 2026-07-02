#include "RequestContext.h"

RequestContext::RequestContext(
    const std::string& userId,
    const std::string& ipAddress,
    const std::string& apiKey,
    const std::string& path,
    const std::string& method,
    const std::string& userType,
    const std::string& service,
    const std::string& region,
    const std::string& tenant)
    : userId(userId),
      ipAddress(ipAddress),
      apiKey(apiKey),
      path(path),
      method(method),
      userType(userType),
      service(service),
      region(region),
      tenant(tenant)
{
}

// Getters

const std::string& RequestContext::getUserId() const
{
    return userId;
}

const std::string& RequestContext::getIpAddress() const
{
    return ipAddress;
}

const std::string& RequestContext::getApiKey() const
{
    return apiKey;
}

const std::string& RequestContext::getPath() const
{
    return path;
}

const std::string& RequestContext::getMethod() const
{
    return method;
}

const std::string& RequestContext::getUserType() const
{
    return userType;
}

const std::string& RequestContext::getService() const
{
    return service;
}

const std::string& RequestContext::getRegion() const
{
    return region;
}

const std::string& RequestContext::getTenant() const
{
    return tenant;
}

// Setters

void RequestContext::setUserId(const std::string& userId)
{
    this->userId = userId;
}

void RequestContext::setIpAddress(const std::string& ipAddress)
{
    this->ipAddress = ipAddress;
}

void RequestContext::setApiKey(const std::string& apiKey)
{
    this->apiKey = apiKey;
}

void RequestContext::setPath(const std::string& path)
{
    this->path = path;
}

void RequestContext::setMethod(const std::string& method)
{
    this->method = method;
}

void RequestContext::setUserType(const std::string& userType)
{
    this->userType = userType;
}

void RequestContext::setService(const std::string& service)
{
    this->service = service;
}

void RequestContext::setRegion(const std::string& region)
{
    this->region = region;
}

void RequestContext::setTenant(const std::string& tenant)
{
    this->tenant = tenant;
}

// Header utilities

void RequestContext::setHeaders(
    const std::unordered_map<std::string, std::string>& headers)
{
    this->headers = headers;
}

void RequestContext::setQueryParams(
    const std::unordered_map<std::string, std::string>& queryParams)
{
    this->queryParams = queryParams;
}

void RequestContext::addHeader(
    const std::string& key,
    const std::string& value)
{
    headers[key] = value;
}

void RequestContext::addQueryParam(
    const std::string& key,
    const std::string& value)
{
    queryParams[key] = value;
}

const std::unordered_map<std::string, std::string>&
RequestContext::getHeaders() const
{
    return headers;
}

const std::unordered_map<std::string, std::string>&
RequestContext::getQueryParams() const
{
    return queryParams;
}

std::string RequestContext::getHeader(
    const std::string& key) const
{
    auto it = headers.find(key);

    if (it == headers.end())
    {
        return "";
    }

    return it->second;
}

std::string RequestContext::getQueryParam(
    const std::string& key) const
{
    auto it = queryParams.find(key);

    if (it == queryParams.end())
    {
        return "";
    }

    return it->second;
}