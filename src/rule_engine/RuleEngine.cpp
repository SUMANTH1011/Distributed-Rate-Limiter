#include "RuleEngine.h"
#include "../logging/Logger.h"
#include<iostream>
RuleEngine::RuleEngine(const std::vector<Rule>&rules, RateLimiterManager& manager):rules(rules),manager(manager){}

RateLimitResult RuleEngine::requestProccess(const RequestContext& request)
{
    RateLimitResult result;
    std::shared_lock<std::shared_mutex> lock(rulesMutex);
    auto matchedRule=matcher.matchRule(request,rules);
    if(!matchedRule)
    {
        result.allowed=true;
        result.ruleId=-1;
        return result;
    }
   Logger::getInstance().info(
    "Matched Rule | RuleID=" +
    std::to_string(matchedRule->getId()) +
    " | Priority=" +
    std::to_string(matchedRule->getPriority())
);
    IRateLimiter* rateLimiter=manager.getRateLimiter(*matchedRule);
    if(rateLimiter==nullptr)
    {
        result.allowed = false;
        result.ruleId = matchedRule->getId();
        result.algorithm = matchedRule->getConfig().algorithm;

        return result;
    }
    std::string key =
        getRateLimitKey(request, *matchedRule);

    Logger::getInstance().debug(
    "Rate Limit Key | " + key
);

    result.ruleId =
        matchedRule->getId();

    result.algorithm =
        matchedRule->getConfig().algorithm;

    result.allowed =
        rateLimiter->allowRequest(key);

    return result;
}
void RuleEngine::updateRules(const std::vector<Rule> rules)
{
    std::unique_lock<std::shared_mutex> lock(rulesMutex);
    this->rules = std::move(rules);
}
std::string RuleEngine::getRateLimitKey(
        const RequestContext& request,
        const Rule& rule) const
{
    switch(rule.getConfig().keyType)
    {
        case KeyType::USER_ID:
            return request.getUserId();

        case KeyType::IP_ADDRESS:
            return request.getIpAddress();

        case KeyType::API_KEY:
            return request.getApiKey();

        case KeyType::TENANT:
            return request.getTenant();

        case KeyType::USER_TYPE:
            return request.getUserType();

        case KeyType::SERVICE:
            return request.getService();

        case KeyType::REGION:
            return request.getRegion();

        default:
            return request.getUserId();
    }
}