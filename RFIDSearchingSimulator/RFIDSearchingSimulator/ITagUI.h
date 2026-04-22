#pragma once

#include <string>
#include <vector>

#include "ITagSearcher.h"
#include "RFIDTag.h"

class ITagUI
{
public:
    virtual ~ITagUI() = default;

    virtual int ReadMenu() = 0;
    virtual int ReadTagCount(const std::string& message, int minValue, int maxValue) = 0;
    virtual std::string ReadTag(const std::string& message) = 0;

    virtual void ShowTags(const std::vector<RFIDTag>& tags) = 0;
    virtual void ShowSearchResult(const std::string& methodName, const SearchResult& result) = 0;
    virtual void ShowComparison(const std::string& firstMethodName, const SearchResult& firstResult, const std::string& secondMethodName, const SearchResult& secondResult) = 0;

    virtual void ShowMessage(const std::string& message) = 0;
    virtual void ShowError(const std::string& message) = 0;
};
