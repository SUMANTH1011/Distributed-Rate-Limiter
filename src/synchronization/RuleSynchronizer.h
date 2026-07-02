#ifndef RULE_SYNCHRONIZER_H
#define RULE_SYNCHRONIZER_H

#include "../rule_engine/RuleLoader.h"
#include "../rule_engine/RuleValidator.h"
#include "../rule_engine/RuleEngine.h"

#include "../logging/Logger.h"

#include "FileWatcher.h"

#include <thread>
#include <atomic>
#include <string>

class RuleSynchronizer
{
private:
    RuleEngine& engine;

    RuleLoader loader;
    RuleValidator validator;

    FileWatcher watcher;

    std::thread syncThread;

    std::atomic<bool> running;

    void watchLoop();

public:
    explicit RuleSynchronizer(
        RuleEngine& engine
    );

    ~RuleSynchronizer();

    void start();

    void stop();

    bool reloadRules(
        const std::string& fileName
    );
};

#endif