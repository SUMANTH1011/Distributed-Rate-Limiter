#include "Metrics.h"

#include <chrono>

Metrics::Metrics()
{
    startTime =
        std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();
}