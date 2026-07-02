#ifndef METRICSREPORTER_H
#define METRICSREPORTER_H

#include <thread>
#include <atomic>

#include "MetricsCollector.h"

class MetricsReporter
{
private:
    MetricsCollector& metricsCollector;

    std::thread reporterThread;

    std::atomic<bool> running;

    void reportLoop();

public:
    explicit MetricsReporter(
        MetricsCollector& collector
    );

    ~MetricsReporter();

    void start();

    void stop();
};

#endif