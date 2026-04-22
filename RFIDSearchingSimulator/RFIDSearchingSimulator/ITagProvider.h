#pragma once

#include <string>
#include <vector>
#include "RFIDTag.h"

class ITagProvider
{
public:
    virtual ~ITagProvider() = default;
    virtual std::vector<RFIDTag> GetTags() = 0;
};