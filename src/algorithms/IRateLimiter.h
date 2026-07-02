#ifndef IRATELIMITER_H
#define IRATELIMITER_H

#include<string>
using namespace std;

class IRateLimiter
{
public:
    virtual bool allowRequest(const string &key) = 0;
    virtual ~IRateLimiter(){}
};
#endif