#pragma once

#include "ITagProvider.h"

class ITagUI;

// ManualTagProvider는 사용자가 직접 TAG를 입력해서 목록을 만드는 구현체이다.
//
// 역할 분리
// - TAG 형식 검증(4bit 여부) : UI가 담당
// - 중복 검사(목록 규칙)     : Provider가 담당
class TagProviderManual : public ITagProvider
{
public:
    explicit TagProviderManual(ITagUI& tagUI);
    std::vector<RFIDTag> GetTags() override;

private:
    ITagUI& m_tagUI;
};