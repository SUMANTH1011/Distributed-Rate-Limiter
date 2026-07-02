#include "RuleLoader.h"
#include "RuleValidator.h"

#include "../utils/EnumConverter.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json=nlohmann::json;

std::vector<Rule> RuleLoader::loadRules(const std::string& fileName)
{
   std::vector<Rule> validRules;

RuleValidator validator;

std::ifstream input(fileName);

if (!input.is_open())
{
     throw std::runtime_error(
        "Unable to open rules file: " + fileName
    );
}

json root;
input >> root;

for (const auto& item : root)
{
    RateLimiterConfig config;

    config.algorithm =
        EnumConverter::toAlgorithmType(item["config"]["algorithm"]);

    config.keyType =
        EnumConverter::toKeyType(item["config"]["keyType"]);

    config.capacity =
        item["config"]["capacity"];

    config.refillRate =
        item["config"]["refillRate"];

    config.limit =
        item["config"]["limit"];

    config.windowSize =
        item["config"]["windowSize"];

    config.leakRate =
        item["config"]["leakRate"];

    Rule rule(
    item["id"].get<int>(),
    item["priority"].get<int>(),
    item["path"].get<std::string>(),
    item["method"].get<std::string>(),
    item["userType"].get<std::string>(),
    item["apiKey"].get<std::string>(),
    item["ip"].get<std::string>(),
    config
);
    if (validator.validate(rule))
    {
         std::cout<<"Loaded Rule ID: "<<rule.getId()<<" Priority: "<<rule.getPriority()<<std::endl;
        validRules.push_back(rule);
    }
}

return validRules;
}