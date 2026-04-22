#pragma once

#include <string>
#include <vector>

#include "ITagSearcher.h"

class TagSearcherIterative : public ITagSearcher
{
public:
    std::string GetName() const override;
    SearchResult Search(const std::vector<RFIDTag>& tags) const override;
};