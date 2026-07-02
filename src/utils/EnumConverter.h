#ifndef ENUM_CONVERTER_H
#define ENUM_CONVERTER_H

#include<string>

#include "../models/AlgorithmType.h"
#include "../models/KeyType.h"

class EnumConverter
{
public:
    static AlgorithmType toAlgorithmType(const std::string& value);
    static KeyType toKeyType(const std::string& value);
    static std::string toString(AlgorithmType type);
    static std::string toString(KeyType type);
};
#endif