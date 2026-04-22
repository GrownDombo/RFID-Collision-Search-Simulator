#pragma once

#include <string>

struct RFIDTag
{
    int id = 0;
    std::string bits;

    std::string ToString() const
    {
        return bits + "<TAG " + std::to_string(id) + ">";
    }
};