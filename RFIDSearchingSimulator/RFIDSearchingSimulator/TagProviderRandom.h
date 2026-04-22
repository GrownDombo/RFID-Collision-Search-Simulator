#pragma once

#include "ITagProvider.h"

class ITagUI;

// RandomTagProvider는 랜덤한 4bit TAG 목록을 생성하는 구현체이다.
// 현재는 중복 없는 TAG 집합을 만든다.
class TagProviderRandom : public ITagProvider
{
public:
    explicit TagProviderRandom(ITagUI& tagUI);
    std::vector<RFIDTag> GetTags() override;

private:
    ITagUI& m_tagUI;
};