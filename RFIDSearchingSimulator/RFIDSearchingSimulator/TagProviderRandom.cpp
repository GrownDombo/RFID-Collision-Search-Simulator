#include "TagProviderRandom.h"
#include "ITagUI.h"
#include <bitset>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>



TagProviderRandom::TagProviderRandom(ITagUI& tagUI) : m_tagUI(tagUI)
{
}

std::vector<RFIDTag> TagProviderRandom::GetTags()
{
    m_tagUI.ShowMessage("Random으로 Tag Data 생성합니다.");
    const int count = m_tagUI.ReadTagCount("생성할 랜덤 TAG 개수 (1~16): ", 1, 16);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 15);

    std::unordered_set<int> usedValues;

    std::vector<RFIDTag> tags;
    tags.reserve(count);

    while (static_cast<int>(tags.size()) < count)
    {
        const int value = dist(gen);

        if (usedValues.insert(value).second)
        {
            tags.push_back({
                static_cast<int>(tags.size()) + 1,
                std::bitset<4>(value).to_string()
                });
        }
    }

    return tags;
}