#include "TagSearcherRecursive.h"

std::string TagSearcherRecursive::GetName() const 
{
	return "Àç±Í ¹æ½Ä";
}

SearchResult TagSearcherRecursive::Search(const std::vector<RFIDTag>& tags) const
{
    return RunMeasuredSearch(tags, [&](SearchResult& result)
        {
            const size_t tagBitLength = GetTagBitLength(tags);
            Explore(tags, "", 0, tagBitLength, result);
        });
}

void TagSearcherRecursive::Explore(const std::vector<RFIDTag>& tags, const std::string& prefix, int depth, size_t tagBitLength, SearchResult& result) const
{
    const PrefixEvaluation evaluation = EvaluatePrefix(tags, prefix);
    RecordStep(result, prefix, depth, evaluation);

    if (evaluation.state == QueryState::Collision && prefix.size() < tagBitLength)
    {
        Explore(tags, prefix + "0", depth + 1, tagBitLength, result);
        Explore(tags, prefix + "1", depth + 1, tagBitLength, result);
    }
}