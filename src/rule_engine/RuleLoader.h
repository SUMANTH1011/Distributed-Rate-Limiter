#ifndef RULE_LOADER_H
#define RULE_LOADER_H

#include <vector>
#include <string>

#include "Rule.h"
#include "../models/RateLimiterConfig.h"

class RuleLoader
{
public:

    std::vector<Rule> loadRules(const std::string& fileName);

};

#endif