#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "ITagSearcher.h"

class TagSearcherRecursive : public ITagSearcher
{
public:
    std::string GetName() const override;
    SearchResult Search(const std::vector<RFIDTag>& tags) const override;

private:
    void Explore(const std::vector<RFIDTag>& tags, const std::string& prefix, int depth, std::size_t tagBitLength, SearchResult& result) const;
};