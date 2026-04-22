#include "TagUIConsole.h"
#include "StringUtil.h"
#include "RFIDTag.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

namespace
{
    string FormatMicrosecondsFromNanoseconds(long long nanoseconds)
    {
        ostringstream oss;
        oss << fixed << setprecision(3) << static_cast<double>(nanoseconds) / 1000.0 << " us";
        return oss.str();
    }

    bool SameTagSet(vector<RFIDTag> left, vector<RFIDTag> right)
    {
        auto comparer = [](const RFIDTag& a, const RFIDTag& b)
            {
                if (a.bits != b.bits)
                    return a.bits < b.bits;
                return a.id < b.id;
            };

        sort(left.begin(), left.end(), comparer);
        sort(right.begin(), right.end(), comparer);

        if (left.size() != right.size())
            return false;

        for (size_t i = 0; i < left.size(); ++i)
        {
            if (left[i].id != right[i].id || left[i].bits != right[i].bits)
                return false;
        }

        return true;
    }

    string FormatQueryState(QueryState state)
    {
        switch (state)
        {
        case QueryState::Empty:
            return "Empty";
        case QueryState::Success:
            return "Success";
        case QueryState::Collision:
            return "Collision";
        default:
            return "Unknown";
        }
    }
}

int TagUIConsole::ReadMenu()
{
    return ReadIntInRange(
        StringUtil::JoinLines(
            "=== RFID TAG 입력 방식 선택 ===",
            "1. 정해진 데이터",
            "2. 사용자 직접 입력",
            "3. 랜덤 TAG 생성"),
        1,
        3);
}

int TagUIConsole::ReadTagCount(const std::string& message, int minValue, int maxValue)
{
    return ReadIntInRange(message, minValue, maxValue);
}

string TagUIConsole::ReadLine(const string& message)
{
    cout << message << endl;
    string line;
    getline(cin, line);
    cout << endl;
    return line;
}

int TagUIConsole::ReadIntInRange(const string& message, int minValue, int maxValue)
{
    while (true)
    {
        const string line = ReadLine(message);

        size_t pos = 0;
        const int value = stoi(line, &pos);
        if (pos == line.size() && value >= minValue && value <= maxValue)
            return value;

        cout << "잘못된 입력입니다. " << minValue << " ~ " << maxValue << " 사이 값을 입력하세요." << endl;
    }
}

bool TagUIConsole::IsValid4BitTag(const string& tag) const
{
    if (tag.size() != 4)
        return false;

    for (const char ch : tag)
    {
        if (ch != '0' && ch != '1')
            return false;
    }

    return true;
}

string TagUIConsole::ReadTag(const string& message)
{
    while (true)
    {
        const string tag = ReadLine(message);
        if (IsValid4BitTag(tag))
            return tag;

        ShowError("잘못된 TAG입니다. 예: 1010 처럼 0/1로만 이루어진 4자리여야 합니다.");
    }
}

void TagUIConsole::ShowTags(const vector<RFIDTag>& tags)
{
    cout << "========================================" << endl;
    cout << "[입력된 TAG 목록]" << endl;
    cout << "========================================" << endl;

    if (tags.empty())
    {
        cout << "(TAG 없음)" << endl << endl;
        return;
    }

    for (size_t i = 0; i < tags.size(); ++i)
        cout << i + 1 << ". " << tags[i].ToString() << endl;

    cout << endl;
}

void TagUIConsole::ShowSearchResult(const std::string& methodName, const SearchResult& result)
{
    cout << "========================================" << endl;
    cout << "[" << methodName << "]" << endl;
    cout << "========================================" << endl;

    if (result.logs.empty())
    {
        cout << "탐색할 TAG가 없습니다." << endl << endl;
        return;
    }

    for (const QueryLog& log : result.logs)
    {
        cout << "==== Cycle: " << log.cycle << "====" << endl;
        cout << "Query: " << (log.prefix.empty() ? "ROOT" : log.prefix) << endl << endl;

        if (log.matchedTags.empty())
            cout << "No matching tags";
        else
        {

            for (size_t i = 0; i < log.matchedTags.size(); ++i)
                cout << "Response:" << log.matchedTags[i].ToString() << endl;;
        }

        cout << endl;

        cout << "Result: " << FormatQueryState(log.state) << endl;
        cout << endl;
    }

    cout << "[탐색 요약]" << endl;
    cout << "질의 횟수 : " << result.queryCount << endl;
    cout << "충돌 횟수 : " << result.collisionCount << endl;
    cout << "실행 시간 : " << FormatMicrosecondsFromNanoseconds(result.elapsedNanoseconds) << endl;
    cout << endl;

    cout << "[발견된 TAG]" << endl;
    if (result.foundTags.empty())
    {
        cout << "(없음)" << endl;
    }
    else
    {
        for (size_t i = 0; i < result.foundTags.size(); ++i)
            cout << i + 1 << ". " << result.foundTags[i].ToString() << endl;
    }

    cout << endl;
}

void TagUIConsole::ShowComparison(
    const std::string& firstMethodName,
    const SearchResult& firstResult,
    const std::string& secondMethodName,
    const SearchResult& secondResult)
{
    cout << "========================================" << endl;
    cout << "[비교 결과]" << endl;
    cout << "========================================" << endl;

    cout << "발견 Tag 동일 여부 : "
        << (SameTagSet(firstResult.foundTags, secondResult.foundTags) ? "동일" : "다름")
        << endl;

    cout << firstMethodName << " 질의 횟수 : " << firstResult.queryCount << endl;
    cout << secondMethodName << " 질의 횟수 : " << secondResult.queryCount << endl;
    cout << firstMethodName << " 충돌 횟수 : " << firstResult.collisionCount << endl;
    cout << secondMethodName << " 충돌 횟수 : " << secondResult.collisionCount << endl;
    cout << firstMethodName << " 실행 시간 : " << FormatMicrosecondsFromNanoseconds(firstResult.elapsedNanoseconds) << endl;
    cout << secondMethodName << " 실행 시간 : " << FormatMicrosecondsFromNanoseconds(secondResult.elapsedNanoseconds) << endl;
    cout << endl;
}

void TagUIConsole::ShowMessage(const string& message)
{
    cout << message << endl << endl;
}

void TagUIConsole::ShowError(const string& message)
{
    cout << "오류: " << message << endl;
}
