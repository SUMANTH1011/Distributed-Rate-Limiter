#ifndef REQUEST_CONTEXT_BUILDER_H
#define REQUEST_CONTEXT_BUILDER_H

#include <crow.h>

#include "../request/RequestContext.h"

class RequestContextBuilder
{
public:
    static RequestContext build(const crow::request& request);
};

#endif