#include "HttpServer.h"

#include <crow.h>
#include <iostream>
#include <chrono>
HttpServer::HttpServer(
    const ServerConfig& config,
    RequestHandler& handler,
    MetricsCollector& metricsCollector,
    RuleSynchronizer& synchronizer)
    : config(config),
      handler(handler),
      metricsCollector(metricsCollector),
      synchronizer(synchronizer)
{
}

void HttpServer::start(int port)
{
    crow::SimpleApp app;

    // Root
    CROW_ROUTE(app, "/")
    ([]()
    {
        crow::json::wvalue response;

        response["service"] = "Distributed Rate Limiter";
        response["version"] = "1.0";
        response["status"] = "UP";

        return response;
    });

    // Health
    CROW_ROUTE(app, "/health")
    ([]()
    {
        return crow::response(200, "Service is UP");
    });

    // Metrics
    CROW_ROUTE(app, "/metrics")
([this]()
{
    long long currentTime =
    std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
    const Metrics& m =
        metricsCollector.getMetrics();

long long uptime =
    currentTime - m.startTime;
    crow::json::wvalue response;

response["uptimeSeconds"] = uptime;

response["totalRequests"] =
    m.totalRequests.load();

response["allowedRequests"] =
    m.allowedRequests.load();
    double rps = 0.0;

if(uptime > 0)
{
    rps =
        static_cast<double>(
            m.totalRequests.load()
        ) / uptime;
}
    response["requestsPerSecond"] = rps;

response["rejectedRequests"] =
    m.rejectedRequests.load();

response["redisCalls"] =
    m.redisCalls.load();

response["redisFailures"] =
    m.redisFailures.load();

response["ruleReloads"] =
    m.ruleReloads.load();
    response["algorithms"]["TOKEN_BUCKET"] =
    m.tokenBucketRequests.load();

response["algorithms"]["FIXED_WINDOW"] =
    m.fixedWindowRequests.load();

response["algorithms"]["LEAKY_BUCKET"] =
    m.leakyBucketRequests.load();

response["algorithms"]["SLIDING_WINDOW_LOG"] =
    m.slidingWindowLogRequests.load();

response["algorithms"]["SLIDING_WINDOW_COUNTER"] =
    m.slidingWindowCounterRequests.load();
    return crow::response(response);
});

    // Rate Limited API
/// Rate Limited API
CROW_ROUTE(app, "/api/<string>")
.methods(crow::HTTPMethod::GET,crow::HTTPMethod::POST)
([this](const crow::request& req, const std::string& subPath)
{
    try
    {
        std::cout << "\n========== Incoming API Request ==========\n";
        std::cout << "URL       : " << req.url << std::endl;
        std::cout << "Sub Path  : " << subPath << std::endl;

        RequestContext context =
            RequestContextBuilder::build(req);

        std::cout << "Context Built Successfully" << std::endl;

        HttpResponse response =
            handler.handleRequest(context);

        std::cout
            << "Response Code : "
            << response.statusCode
            << std::endl;

        return crow::response(
            response.statusCode,
            response.body
        );
    }
    catch(const std::exception& ex)
    {
        std::cerr
            << "Exception : "
            << ex.what()
            << std::endl;

        return crow::response(
            500,
            ex.what()
        );
    }
    catch(...)
    {
        std::cerr
            << "Unknown Exception"
            << std::endl;

        return crow::response(
            500,
            "Unknown Error"
        );
    }
});
// CROW_ROUTE(app, "/api/<string>")
// ([](std::string subPath)
// {
//     return "API : " + subPath;
// });
//     CROW_ROUTE(app, "/hello/<string>")
// ([](std::string name)
// {
//     return "Hello " + name;
// });
    // Reload Rules
    CROW_ROUTE(app, "/reload")
    .methods(crow::HTTPMethod::POST)
    ([this]()
    {
        bool ok =
            synchronizer.reloadRules("rules.json");

        if (ok)
        {
            return crow::response(
                200,
                "Rules Reloaded"
            );
        }

        return crow::response(
            500,
            "Reload Failed"
        );
    });

    std::cout << "Server started on port "
              << port
              << std::endl;

    app.port(port)
       .multithreaded()
       .run();
}