#include "TagProviderPreset.h"
#include "ITagUI.h"
#include <string>
#include <unordered_set>
#include <vector>

TagProviderPreset::TagProviderPreset(ITagUI& tagUI) : m_tagUI(tagUI)
{
}

std::vector<RFIDTag> TagProviderPreset::GetTags()
{
    m_tagUI.ShowMessage("사전에 정해진 Tag Data 가져옵니다.");

    const std::vector<std::string> rawTags = { "0010", "1101", "0011", "0101", "1010" };

    std::vector<RFIDTag> tags;
    tags.reserve(rawTags.size());

    for (size_t i = 0; i < rawTags.size(); ++i)
        tags.push_back({ static_cast<int>(i) + 1, rawTags[i] });

    return tags;
}