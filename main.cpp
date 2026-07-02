#include<iostream>
#include <memory>

#include "src/storage/RedisStorage.h"

#include "src/rule_engine/RuleLoader.h"

#include "src/manager/RateLimiterManager.h"

#include "src/rule_engine/RuleEngine.h"

#include "src/synchronization/RuleSynchronizer.h"

#include "src/monitoring/MetricsCollector.h"
#include "src/config/ConfigLoader.h"
#include "src/server/RequestHandler.h"
#include "src/monitoring/MetricsReporter.h"
#include "src/server/HttpServer.h"

#include "src/server/ServerConfig.h"
#include "src/logging/Logger.h"
int main(int argc,char* argv[])
{
    try
    {
        ConfigLoader configLoader;
MetricsCollector metricsCollector;
        ServerConfig serverConfig =configLoader.loadServerConfig("config/server.json");

        RedisConfig redisConfig =configLoader.loadRedisConfig("config/redis.json");

        LoggingConfig loggingConfig =configLoader.loadLoggingConfig("config/logging.json");
        
        auto storage =std::make_shared<RedisStorage>(redisConfig.host,redisConfig.port,&metricsCollector);
        RuleLoader loader;
        std::vector<Rule>rules=loader.loadRules("rules.json");
        RateLimiterManager manager(storage);
        RuleEngine ruleEng(rules,manager);
        MetricsReporter reporter(metricsCollector);
        reporter.start();
        RuleSynchronizer sync(ruleEng);
        sync.start();
        RequestHandler req(ruleEng,metricsCollector);
        ServerConfig config=serverConfig;
        HttpServer server(config,req,metricsCollector,sync);
        
        Logger::getInstance().info("Starting Distributed Rate Limiter...");
        int port=config.port;
        if(argc>1)
        {
             port = std::stoi(argv[1]);
        }
        std::cout << "argc = " << argc << std::endl;

for(int i = 0; i < argc; i++)
{
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
}

std::cout << "Final Port = " << port << std::endl;
        Logger::getInstance().info(
    "Starting Server on Port " +
    std::to_string(port)
);
        server.start(port);
    }
    catch(const std::exception& ex)
    {
        std::cerr<<"Fatal Error: "<<ex.what()<<std::endl;
    }
    return 0;
}