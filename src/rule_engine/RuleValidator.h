#ifndef RULE_VALIDATOR_H
#define RULE_VALIDATOR_H

#include "Rule.h"

class RuleValidator
{
public:

    bool validate(const Rule& rule) const;

private:

    bool validateCommon(const Rule& rule) const;

    bool validateTokenBucket(const Rule& rule) const;

    bool validateFixedWindow(const Rule& rule) const;

    bool validateLeakyBucket(const Rule& rule) const;

    bool validateSlidingWindowLog(const Rule& rule) const;

    bool validateSlidingWindowCounter(const Rule& rule) const;

};

#endif