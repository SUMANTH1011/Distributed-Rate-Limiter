
#include "RequestHandler.h"
#include "../logging/Logger.h"
#include<iostream>
RequestHandler::RequestHandler(
    RuleEngine& engine,MetricsCollector& metricsCollector)
    : engine(engine),metricsCollector(metricsCollector)
{
}

HttpResponse RequestHandler::handleRequest(
    const RequestContext& request)
{
    Logger::getInstance().info(
        "Incoming Request | IP=" +
        request.getIpAddress() +
        " | User=" +
        request.getUserId() +
        " | Method=" +
        request.getMethod() +
        " | Path=" +
        request.getPath()
    );
     metricsCollector.recordRequest();
    RateLimitResult result =
        engine.requestProccess(request);

    if(result.ruleId != -1)
    {
        metricsCollector.recordAlgorithm(
            result.algorithm
        );
    }

    if(result.allowed)
    {
        metricsCollector.recordAllowed();

        Logger::getInstance().info(
            "Decision | ALLOWED | RuleID=" +
            std::to_string(result.ruleId)
        );

        return
        {
            200,
            "Request Allowed"
        };
    }

    metricsCollector.recordRejected();

    Logger::getInstance().warning(
        "Decision | REJECTED | RuleID=" +
        std::to_string(result.ruleId)
    );

    return
    {
        429,
        "Too Many Requests"
    };
}