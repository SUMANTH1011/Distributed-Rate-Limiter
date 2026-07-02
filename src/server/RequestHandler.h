#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "../rule_engine/RuleEngine.h"
#include "../models/HttpResponse.h"

#include "../monitoring/MetricsCollector.h"
class RequestHandler
{
private:
    RuleEngine& engine;
    MetricsCollector& metricsCollector;
public:
    explicit RequestHandler(RuleEngine& engine,MetricsCollector& metricsCollector);
    HttpResponse handleRequest(const RequestContext& request);
};
#endif