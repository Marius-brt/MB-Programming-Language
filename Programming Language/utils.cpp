#include "main.h"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s) {
    return rtrim(ltrim(s));
}

bool startsWith(string str, string prefix)
{
    if (str.length() < prefix.length())
        return false;
    int i = -1;
    while (prefix[++i])
        if (prefix[i] != str[i])
            return false;
    return true;
}

bool startsWith(string str, string prefixes[])
{
    for (int i = 0; i < sizeof(prefixes); i++)
        if (str.rfind(prefixes[i], 0) == 0)
            return true;
    return false;
}

bool endsWith(const string& mainStr, const string& toMatch)
{
    return (mainStr.size() >= toMatch.size() &&
        mainStr.compare(mainStr.size() - toMatch.size(), toMatch.size(), toMatch) == 0);
}

vector<string> Split(string str, string seperator)
{
    vector<string> splts;
    if (str.length() == 0)
        return splts;
    size_t pos = 0;
    while ((pos = str.find(seperator)) != string::npos) {
        splts.push_back(str.substr(0, pos));
        str.erase(0, pos + seperator.length());
    }
    return splts;
}

vector<string> Split(string str, char seperator)
{
    vector<string> splts;
    if (str.length() == 0)
        return splts;
    int i = 0, startIndex = 0, endIndex = 0;
    bool inQuote = false;
    char quoteType;
    while (i <= str.length())
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            if (inQuote && str[i] == quoteType)
                inQuote = false;
            else if (!inQuote)
            {
                inQuote = true;
                quoteType = str[i];
            }
        }
        else if (!inQuote && (str[i] == seperator || i == str.length()))
        {
            endIndex = i;
            string subStr = "";
            subStr.append(str, startIndex, endIndex - startIndex);
            splts.push_back(subStr);
            startIndex = endIndex + 1;
        }
        i++;
    }
    return splts;
}

vector<string> SplitOnce(string str, char seperator)
{
    vector<string> splts;
    if (str.length() == 0)
        return splts;
    int i = 0, startIndex = 0, endIndex = 0;
    bool ended = false, inQuote = false;
    char quoteType;
    while (!ended && i <= str.length())
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            if (inQuote && str[i] == quoteType)
                inQuote = false;
            else if (!inQuote)
            {
                inQuote = true;
                quoteType = str[i];
            }
        }
        else if (str[i] == seperator && !inQuote)
        {
            endIndex = i;
            string before = "";
            before.append(str, startIndex, endIndex - startIndex);
            splts.push_back(before);
            startIndex = endIndex + 1;
            if (i + 1 < str.length()) {
                string after = "";
                after.append(str, startIndex, str.length() - startIndex);
                splts.push_back(after);
            }
            ended = true;
        }
        i++;
    }
    if (splts.size() == 0)
        splts.push_back(str);
    return splts;
}

string JoinAt(vector<string> str, int index, string join)
{
    if (index + 1 > str.size())
        throw invalid_argument("Index out of range");
    string res = "";
    while (index < str.size())
    {
        res += str[index];
        if(index + 1 < str.size())
            res += join;
        index++;
    }
    return res;
}

bool Contains(string element, vector<string> list)
{
    for (string el : list)
        if (el == element)
            return true;
    return false;
}