#pragma once
#include <fstream>

class ISerializer{
    public:
        virtual ~ISerializer() {};
        virtual void serialize(std::fstream& out) = 0;
        virtual void deserialize(std::fstream& in) = 0;
};