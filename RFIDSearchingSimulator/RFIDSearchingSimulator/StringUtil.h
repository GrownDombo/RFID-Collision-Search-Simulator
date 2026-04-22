#pragma once
#include <string>
#include <cctype>
#include <vector>

namespace StringUtil
{
    void LTrim(std::string& str);
    void RTrim(std::string& str);
    void Trim(std::string& str);

    std::string Join(const std::vector<std::string>& values, const std::string& delimiter);
    std::string JoinLines(const std::vector<std::string>& values);

    template<typename... Args>
    std::string JoinLines(const Args&... values)
    {
        return JoinLines(std::vector<std::string>{ std::string(values)... });
    }
}