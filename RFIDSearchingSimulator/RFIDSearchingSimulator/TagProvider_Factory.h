#pragma once

#include <memory>

class ITagProvider;
class ITagUI;

// 사용자 메뉴 입력값과 실제 TAG 준비 방식을 연결한다.
enum class TagInputType
{
    Preset = 1,
    Manual = 2,
    Random = 3
};

// TagProviderFactory는 메뉴 번호에 따라 적절한 Provider 객체를 생성한다.
//
// 이 클래스를 사용하면 main 함수는 구체 구현체를 직접 알 필요가 없다.
class TagProvider_Factory
{
public:
    explicit TagProvider_Factory(ITagUI& tagUI);

    std::unique_ptr<ITagProvider> Create(int menuNumber) const;

private:
    ITagUI& m_tagUI;
};