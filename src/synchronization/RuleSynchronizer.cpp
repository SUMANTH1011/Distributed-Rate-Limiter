#include "RuleSynchronizer.h"

#include <chrono>

RuleSynchronizer::RuleSynchronizer(
    RuleEngine& engine)
    : engine(engine),
      watcher("rules.json"),
      running(false)
{
}

RuleSynchronizer::~RuleSynchronizer()
{
    stop();
}

void RuleSynchronizer::start()
{
    if(running)
        return;

    running = true;

    syncThread = std::thread(
        &RuleSynchronizer::watchLoop,
        this
    );
}

void RuleSynchronizer::stop()
{
    running = false;

    if(syncThread.joinable())
    {
        syncThread.join();
    }
}

void RuleSynchronizer::watchLoop()
{
    while(running)
    {
        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );

        if(watcher.hasChanged())
        {
            Logger::getInstance().info(
                "rules.json modified. Reloading rules..."
            );

            if(reloadRules("rules.json"))
            {
                Logger::getInstance().info(
                    "Rules reloaded successfully."
                );
            }
            else
            {
                Logger::getInstance().error(
                    "Failed to reload rules."
                );
            }
        }
    }
}

bool RuleSynchronizer::reloadRules(
    const std::string& fileName)
{
    auto rules =
        loader.loadRules(fileName);

    for(const auto& rule : rules)
    {
        if(!validator.validate(rule))
        {
            Logger::getInstance().error(
                "Rule validation failed."
            );

            return false;
        }
    }

    engine.updateRules(rules);

    Logger::getInstance().info(
        "Loaded " +
        std::to_string(rules.size()) +
        " rules."
    );

    return true;
}