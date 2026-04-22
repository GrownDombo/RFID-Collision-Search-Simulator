#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "RFIDTag.h"

enum class QueryState
{
    Empty,
    Success,
    Collision
};

struct PrefixEvaluation
{
    QueryState state = QueryState::Empty;
    std::vector<RFIDTag> matchedTags;
};

struct QueryLog
{
    int cycle = 0;
    std::string prefix;
    int depth = 0;
    QueryState state = QueryState::Empty;
    std::vector<RFIDTag> matchedTags;
};

struct SearchResult
{
    std::vector<RFIDTag> foundTags;
    std::vector<QueryLog> logs;
    int queryCount = 0;
    int collisionCount = 0;
    long long elapsedNanoseconds = 0;
};

class ITagSearcher
{
public:
    virtual ~ITagSearcher() = default;

    virtual std::string GetName() const = 0;
    virtual SearchResult Search(const std::vector<RFIDTag>& tags) const = 0;

protected:
    PrefixEvaluation EvaluatePrefix(const std::vector<RFIDTag>& tags, const std::string& prefix) const
    {
        PrefixEvaluation evaluation;

        for (const RFIDTag& tag : tags)
        {
            if (tag.bits.rfind(prefix, 0) == 0)
                evaluation.matchedTags.push_back(tag);
        }

        if (evaluation.matchedTags.empty())
            evaluation.state = QueryState::Empty;
        else if (evaluation.matchedTags.size() == 1)
            evaluation.state = QueryState::Success;
        else
            evaluation.state = QueryState::Collision;

        return evaluation;
    }

    std::size_t GetTagBitLength(const std::vector<RFIDTag>& tags) const
    {
        return tags.empty() ? 0 : tags.front().bits.size();
    }

    void RecordStep(
        SearchResult& result,
        const std::string& prefix,
        int depth,
        const PrefixEvaluation& evaluation) const
    {
        ++result.queryCount;

        if (evaluation.state == QueryState::Collision)
            ++result.collisionCount;

        QueryLog log;
        log.cycle = result.queryCount;
        log.prefix = prefix;
        log.depth = depth;
        log.state = evaluation.state;
        log.matchedTags = evaluation.matchedTags;
        result.logs.push_back(log);

        if (evaluation.state == QueryState::Success && !evaluation.matchedTags.empty())
            result.foundTags.push_back(evaluation.matchedTags.front());
    }

    template<typename Func>
    SearchResult RunMeasuredSearch(const std::vector<RFIDTag>& tags, const Func& func) const
    {
        SearchResult result;

        if (tags.empty())
            return result;

        const auto start = std::chrono::high_resolution_clock::now();
        func(result);
        const auto end = std::chrono::high_resolution_clock::now();

        result.elapsedNanoseconds =
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        return result;
    }
};
