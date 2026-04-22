#include "TagProviderManual.h"
#include "ITagUI.h"
#include <string>
#include <unordered_set>
#include <vector>

TagProviderManual::TagProviderManual(ITagUI& tagUI) : m_tagUI(tagUI)
{
}

std::vector<RFIDTag> TagProviderManual::GetTags()
{
    m_tagUI.ShowMessage("사용자가 직접 입력하여 Tag Data 생성합니다.");
    const int count = m_tagUI.ReadTagCount("입력할 TAG 개수 (1~16): ", 1, 16);

    std::vector<RFIDTag> tags;
    tags.reserve(count);

    std::unordered_set<std::string> usedTags;

    for (int i = 0; i < count; ++i)
    {
        while (true)
        {
            const std::string message = std::to_string(i + 1) + "번째 4bit TAG 입력: ";
            const std::string tag = m_tagUI.ReadTag(message);

            if (usedTags.find(tag) != usedTags.end())
            {
                m_tagUI.ShowError("중복된 TAG입니다. 다른 TAG를 입력하세요.");
                continue;
            }

            usedTags.insert(tag);
            tags.push_back({ i + 1, tag });
            break;
        }
    }

    return tags;
}