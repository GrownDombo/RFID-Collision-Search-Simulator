#include "StringUtil.h"

namespace StringUtil
{
    void LTrim(std::string& str)
    {
        size_t start = 0;
        while (start < str.size() && isspace(static_cast<unsigned char>(str[start])))
            ++start;
        str.erase(0, start);
    }
    void RTrim(std::string& str)
    {
        size_t end = str.size();
        while (end > 0 && isspace(static_cast<unsigned char>(str[end - 1])))
            --end;
        str.erase(end);
    }
    void Trim(std::string& str)
    {
        RTrim(str);
        LTrim(str);
    }
    std::string Join(const std::vector<std::string>& values, const std::string& delimiter)
    {
        if (values.empty())
            return "";

        std::string result;
        for (size_t i = 0; i < values.size(); ++i)
        {
            if (i > 0)
                result += delimiter;
            result += values[i];
        }
        return result;
    }
    std::string JoinLines(const std::vector<std::string>& values)
    {
        return Join(values, "\n");
    }
}