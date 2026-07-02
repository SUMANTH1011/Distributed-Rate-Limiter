#ifndef RULE_ENGINE_H
#define RULE_ENGINE_H

#include<vector>
#include <shared_mutex>

#include "Rule.h"
#include "../manager/RateLimiterManager.h"
#include "RuleMatcher.h"
#include "../request/RequestContext.h"
#include "../models/RateLimitResult.h"
class RuleEngine
{
private:
    std::vector<Rule>rules;
    RuleMatcher matcher;
    mutable std::shared_mutex rulesMutex;
    RateLimiterManager& manager;
    std::string getRateLimitKey(const RequestContext& request,const Rule&rule) const;
public:
    RuleEngine(const std::vector<Rule>&rules,RateLimiterManager& manager);
    void updateRules(const std::vector<Rule> rules);
    RateLimitResult requestProccess(const RequestContext& request);
};

#endif