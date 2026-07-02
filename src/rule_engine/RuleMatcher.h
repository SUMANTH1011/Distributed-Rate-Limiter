#ifndef RULE_MATCHER_H
#define RULE_MATCHER_H


#if __has_include(<optional>)
#include <optional>
#elif __has_include(<experimental/optional>)
#include <experimental/optional>
namespace std { using experimental::optional; }
#else
#error "<optional> or <experimental/optional> is required"
#endif

#include <vector>

#include "../request/RequestContext.h"
#include "Rule.h"

class RuleMatcher
{
public:
    std::optional<Rule>matchRule(const RequestContext& request,const std::vector<Rule>& rules)const;
private:
    bool matches(const RequestContext& request,const Rule& rule)const;
};
#endif