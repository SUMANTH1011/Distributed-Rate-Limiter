#include "EnumConverter.h"

#include<stdexcept>

AlgorithmType EnumConverter::toAlgorithmType(const std::string& value)
{
    if(value=="TOKEN_BUCKET")
    {
        return AlgorithmType::TOKEN_BUCKET;
    }
    if(value=="FIXED_WINDOW")
    {
        return AlgorithmType::FIXED_WINDOW;
    }
    if(value=="LEAKY_BUCKET")
    {
        return AlgorithmType::LEAKY_BUCKET;
    }
    if(value=="SLIDING_WINDOW_LOG")
    {
        return AlgorithmType::SLIDING_WINDOW_LOG;
    }
    if(value=="SLIDING_WINDOW_COUNTER")
    {
        return AlgorithmType::SLIDING_WINDOW_COUNTER;
    }
    throw std::runtime_error("Unknown AlgorithmType");
}

KeyType EnumConverter::toKeyType(const std::string& value)
{
    if(value=="USER_ID")
    {
        return KeyType::USER_ID;
    }
    if(value=="IP_ADDRESS")
    {
        return KeyType::IP_ADDRESS;
    }
    if(value=="API_KEY")
    {
        return KeyType::API_KEY;
    }
    if(value=="TENANT")
    {
        return KeyType::TENANT;
    }
    if(value=="USER_TYPE")
    {
        return KeyType::USER_TYPE;
    }
    if(value=="SERVICE")
    {
        return KeyType::SERVICE;
    }
    if(value=="REGION")
    {
        return KeyType::REGION;
    }
    throw std::runtime_error("Unknown KeyType");
}
std::string EnumConverter::toString(AlgorithmType type)
{
    switch(type)
    {
        case AlgorithmType::TOKEN_BUCKET:
            return "TOKEN_BUCKET";
        case AlgorithmType::FIXED_WINDOW:
            return "FIXED_WINDOW";
        case AlgorithmType::LEAKY_BUCKET:
            return "LEAKY_BUCKET";
        case AlgorithmType::SLIDING_WINDOW_LOG:
            return "SLIDING_WINDOW_LOG";
        case AlgorithmType::SLIDING_WINDOW_COUNTER:
            return "SLIDING_WINDOW_COUNTER";
        default:
            return "UNKNOWN";
    }
}
std::string EnumConverter::toString(KeyType type)
{
    switch(type)
    {
        case KeyType::USER_ID:
            return "USER_ID";
        case KeyType::USER_TYPE:
            return "USER_TYPE";
        case KeyType::API_KEY:
            return "API_KEY";
        case KeyType::IP_ADDRESS:
            return "IP_ADDRESS";
        case KeyType::REGION:
            return "REGION";
        case KeyType::SERVICE:
            return "SERVICE";
        case KeyType::TENANT:
            return "TENANT";
        default:
            return "UNKNOWN";
    }
}
