#include "main.h"

bool checkQuotes(string s)
{
	s = trim(s);
	if (s.length() < 2)
		return false;
	if (s[0] != s[s.length() - 1])
		return false;
	if (s[0] == '\'')
	{
		if (s.length() > 4)
			return false;
		if (s[1] == '\\' && s.length() == 3)
			return false;
		if (s.length() == 4 && s[1] != '\\')
			return false;
		return true;
	}
	if (s.length() > 2)
	{
		int i = 1;
		while (i < s.length() - 1)
		{
			if (s[i] == '"' && (i - 1 == 0 || s[i - 1] != '\\'))
				return false;
			i++;
		}
	}
	return true;
}

bool isInt(string s)
{
	if (s.length() == 0)
		return false;
	int i = -1;
	while (s[++i])
		if (s[i] < '0' || s[i] > '9')
			return false;
	return true;
}

bool isFloat(string s)
{
	if (s.length() == 0 || s[s.length() - 1] == '.')
		return false;
	int i = -1;
	while (s[++i])
		if ((s[i] < '0' || s[i] > '9') && s[i] != '.')
			return false;
	return true;
}

bool isString(string s)
{
	return s.length() > 1 && startsWith(s, "\"") && checkQuotes(s);
}

bool isChar(string s)
{
	return s.length() > 2 && startsWith(s, "'") && checkQuotes(s);
}

bool isValidVarName(string s)
{
	if (s.length() == 0)
		return false;
	if (s[0] >= '0' && s[0] <= '9')
		return false;
	int i = -1;
	while (s[++i])
		if ((s[i] < 'a' || s[i] > 'z') && (s[i] < 'A' || s[i] > 'Z') && s[i] != '_' && (s[0] < '0' && s[0] > '9'))
			return false;
	return true;
}