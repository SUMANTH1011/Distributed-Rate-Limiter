#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "RequestHandler.h"
#include "ServerConfig.h"
#include "RequestContextBuilder.h"

#include "../monitoring/MetricsCollector.h"
#include "../synchronization/RuleSynchronizer.h"

class HttpServer
{
private:

    ServerConfig config;

    RequestHandler& handler;

    MetricsCollector& metricsCollector;

    RuleSynchronizer& synchronizer;

public:

    HttpServer(
        const ServerConfig& config,
        RequestHandler& handler,
        MetricsCollector& metricsCollector,
        RuleSynchronizer& synchronizer
    );

    void start(int port);
};

#endif