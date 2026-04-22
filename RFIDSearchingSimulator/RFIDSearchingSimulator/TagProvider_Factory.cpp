#include "TagProvider_Factory.h"
#include "ITagProvider.h"
#include "ITagUI.h"
#include "TagProviderManual.h"
#include "TagProviderRandom.h"
#include "TagProviderPreset.h"

TagProvider_Factory::TagProvider_Factory(ITagUI& tagUI)
    : m_tagUI(tagUI)
{
}

std::unique_ptr<ITagProvider> TagProvider_Factory::Create(int menuNumber) const
{
    // 사용자가 선택한 메뉴 번호를 기반으로
    // 적절한 TAG Provider 구현체를 생성한다.
    switch (static_cast<TagInputType>(menuNumber))
    {
    case TagInputType::Preset:
        return std::make_unique<TagProviderPreset>(m_tagUI);
    case TagInputType::Manual:
        return std::make_unique<TagProviderManual>(m_tagUI);
    case TagInputType::Random:
        return std::make_unique<TagProviderRandom>(m_tagUI);
    default:
        // 방어 코드: 정상적인 흐름이면 오지 않지만,
        // 잘못된 값이 들어온 경우 nullptr로 실패를 알린다.
        return nullptr;
    }
}