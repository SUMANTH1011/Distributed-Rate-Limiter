#include "RequestContextBuilder.h"

RequestContext RequestContextBuilder::build(
    const crow::request& request)
{
    RequestContext context;

context.setPath(request.url);
std::cout << "Request URL: " << request.url << std::endl;
context.setMethod(std::string(crow::method_name(request.method)));
context.setIpAddress(request.remote_ip_address);

context.setApiKey(
    request.get_header_value("X-API-Key"));

context.setUserId(
    request.get_header_value("X-User-ID"));

context.setTenant(
    request.get_header_value("X-Tenant-ID"));

context.setUserType(
    request.get_header_value("X-User-Type"));

context.addHeader(
    "Authorization",
    request.get_header_value("Authorization"));

context.addHeader(
    "Content-Type",
    request.get_header_value("Content-Type"));

context.addHeader(
    "User-Agent",
    request.get_header_value("User-Agent"));
    
    return context;
}