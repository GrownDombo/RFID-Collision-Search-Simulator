#pragma once

#include "ITagUI.h"
#include <array>

// ConsoleTagUI는 콘솔 기반으로 사용자와 상호작용하는 구현체이다.
//
// 이 클래스는 단순히 입력만 받는 것이 아니라,
// TAG 입력과 관련된 출력까지 함께 담당한다.
// 따라서 이름도 Reader보다는 UI가 더 자연스럽다.
class TagUIConsole : public ITagUI
{
public:
    // 사용자가 TAG 입력 방식을 선택하도록 메뉴를 보여주고 값을 읽는다.
    int ReadMenu() override;
    // TAG 개수를 입력받는다.
    int ReadTagCount(const std::string& message, int minValue, int maxValue) override;
    // 유효한 4bit TAG가 들어올 때까지 반복 입력받는다.
    std::string ReadTag(const std::string& message) override;
    // 생성된 TAG 목록을 화면에 출력한다.
    void ShowTags(const std::vector<RFIDTag>& tags) override;
    // 탐색 결과를 화면에 출력한다.
    void ShowSearchResult(const std::string& methodName, const SearchResult& result) override;
    // 두 탐색 결과를 비교 출력한다.
    void ShowComparison(const std::string& firstMethodName, const SearchResult& firstResult, const std::string& secondMethodName, const SearchResult& secondResult) override;
    // 일반 메시지를 출력한다.
    void ShowMessage(const std::string& message) override;
    // 오류 메시지를 출력한다.
    void ShowError(const std::string& message) override;

private:
    // 가장 기본적인 문자열 한 줄 입력 함수이다.
    std::string ReadLine(const std::string& message);
    // minValue ~ maxValue 범위의 정수를 입력받는 내부 공통 함수이다.
    int ReadIntInRange(const std::string& message, int minValue, int maxValue);
    // 전달받은 문자열이 4bit 이진수인지 검사한다.
    bool IsValid4BitTag(const std::string& tag) const;
};