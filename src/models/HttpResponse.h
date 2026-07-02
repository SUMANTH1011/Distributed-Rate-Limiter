#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>

struct HttpResponse
{
    int statusCode;
    std::string body;

    HttpResponse(int status,
                 const std::string& body)
        : statusCode(status),
          body(body)
    {
    }
};

#endif