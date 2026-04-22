#include "TagSearcherIterative.h"
#include <stack>

std::string TagSearcherIterative::GetName() const
{
    return "반복 방식";
}

SearchResult TagSearcherIterative::Search(const std::vector<RFIDTag>& tags) const
{
    struct StackNode
    {
        std::string prefix;
        int depth;
    };

    return RunMeasuredSearch(tags, [&](SearchResult& result)
    {
        const size_t tagBitLength = GetTagBitLength(tags);
        std::stack<StackNode> nodes;
        nodes.push({ "", 0 });

        while (!nodes.empty())
        {
            const StackNode current = nodes.top();
            nodes.pop();

            const PrefixEvaluation evaluation = EvaluatePrefix(tags, current.prefix);
            RecordStep(result, current.prefix, current.depth, evaluation);

            if (evaluation.state == QueryState::Collision && current.prefix.size() < tagBitLength)
            {
                nodes.push({ current.prefix + "1", current.depth + 1 });
                nodes.push({ current.prefix + "0", current.depth + 1 });
            }
        }
    });
}
