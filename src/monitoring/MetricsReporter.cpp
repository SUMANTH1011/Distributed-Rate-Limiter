#include "MetricsReporter.h"

#include <iostream>
#include <chrono>

MetricsReporter::MetricsReporter(
    MetricsCollector& collector)
    : metricsCollector(collector),
      running(false)
{
}

MetricsReporter::~MetricsReporter()
{
    stop();
}

void MetricsReporter::start()
{
    if(running)
        return;

    running = true;

    reporterThread =
        std::thread(
            &MetricsReporter::reportLoop,
            this
        );
}

void MetricsReporter::stop()
{
    running = false;

    if(reporterThread.joinable())
        reporterThread.join();
}
void MetricsReporter::reportLoop()
{
    while(running)
    {
        std::this_thread::sleep_for(
            std::chrono::seconds(30)
        );

        const Metrics& m =
            metricsCollector.getMetrics();

        std::cout << "\n================ Metrics ================\n";

        std::cout << "Total Requests      : "
                  << m.totalRequests.load() << '\n';

        std::cout << "Allowed Requests    : "
                  << m.allowedRequests.load() << '\n';

        std::cout << "Rejected Requests   : "
                  << m.rejectedRequests.load() << '\n';

        std::cout << "Redis Calls         : "
                  << m.redisCalls.load() << '\n';

        std::cout << "Redis Failures      : "
                  << m.redisFailures.load() << '\n';

        std::cout << "Rule Reloads        : "
                  << m.ruleReloads.load() << '\n';

        std::cout << "\nAlgorithm Usage\n";

        std::cout << "Token Bucket        : "
                  << m.tokenBucketRequests.load() << '\n';

        std::cout << "Fixed Window        : "
                  << m.fixedWindowRequests.load() << '\n';

        std::cout << "Leaky Bucket        : "
                  << m.leakyBucketRequests.load() << '\n';

        std::cout << "Sliding Window Log  : "
                  << m.slidingWindowLogRequests.load() << '\n';

        std::cout << "Sliding Window Ctr  : "
                  << m.slidingWindowCounterRequests.load() << '\n';

        std::cout << "=========================================\n";
    }
}