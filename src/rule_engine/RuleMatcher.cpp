#include "RuleMatcher.h"
#include <iostream>

bool RuleMatcher::matches(const RequestContext& request,const Rule&rule)const
{
    if(!rule.getPath().empty() && request.getPath()!=rule.getPath())
    {
        return false;
    }
    if(!rule.getApiKey().empty() && request.getApiKey()!=rule.getApiKey())
    {
        return false;
    }
    if(!rule.getMethod().empty() && request.getMethod()!=rule.getMethod())
    {
        return false;
    }
    if(!rule.getUserType().empty() && request.getUserType()!=rule.getUserType())
    {
        return false;
    }
    if(!rule.getIp().empty() && request.getIpAddress()!=rule.getIp())
    {
        return false;
    }
    return true;
}

std::optional<Rule>RuleMatcher::matchRule(const RequestContext& request,
    const std::vector<Rule>&rules) const
{
    const Rule* baseRule=nullptr;
    for(const Rule&r : rules)
    {
        if(matches(request,r))
        {
            std::cout << "Matched Rule ID: "
                      << r.getId()
                      << " Priority: "
                      << r.getPriority()
                      << std::endl;
            if(baseRule==nullptr || r.getPriority()<baseRule->getPriority())
            {
                baseRule=&r;
            }
        }
    }
    if(baseRule)
    {
        std::cout << "Selected Rule ID: "
              << baseRule->getId()
              << " Priority: "
              << baseRule->getPriority()
              << std::endl;
        return *baseRule;
    }
    std::cout << "No matching rule found." << std::endl;
    return std::nullopt;
}