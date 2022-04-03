#include "main.h"

string braceTokens[] = { "function", "class", "switch" };
string varTokens[] = { "string", "int", "float"};

void Error(string msg)
{
	cout << msg << endl;
	exit(1);
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
	return s.length() > 1 && startsWith(s, "\"") && endsWith(s, "\"");
}

bool isValidVarName(string s)
{
	if (s.length() == 0)
		return false;
	int i = -1;
	while (s[++i])
		if ((s[i] < 'a' || s[i] > 'z') && (s[i] < 'A' || s[i] > 'Z') && s[i] != '_')
			return false;
	return true;
}

vector<string> Parse(vector<string> lines)
{
	vector<string> cpp;
	bool waitForBrace = false;
	int openBraces = 0;
	for (int i = 0; i < lines.size(); i++)
	{
		string ln = trim(lines[i]);
		if (ln != "") {
			vector<string> splt = Split(ln, ' ');
			if (splt.size() > 0)
			{
				if (waitForBrace) {
					if (startsWith(ln, "{"))
					{
						openBraces++;
						waitForBrace = false;
					}
					else 					
						Error("Missing opening brace at line " + to_string(i + 1));
				}
				if (Contains(splt[0], braceTokens))
				{
					if (!endsWith(ln, "{"))
						waitForBrace = true;
					else
						openBraces++;
				} 
				else if (Contains(splt[0], varTokens))
				{
					if (splt.size() > 4)
						Error("Invalid variable declaration at line " + to_string(i + 1));
					if (!endsWith(ln, ";"))
						Error("Missing ; at the end of the line " + to_string(i + 1));
					if (splt.size() == 1 || splt[1] == ";")
						Error("Missing var name at line " + to_string(i + 1));
					vector<string> splt2 = SplitOnce(JoinAt(splt, 1), '=');
					if (Contains(splt2[0], braceTokens) || Contains(splt2[0], varTokens))
						Error("Variable cannot have '" + splt2[0] + "' has name (line " + to_string(i + 1) + ")");
					if (!isValidVarName(splt2[0]))
						Error("Invalid variable name at line " + to_string(i + 1) + ". Can only contains [a-z], [A-Z] and '_' characters.");
					if (splt2.size() == 2)
					{
						string val = splt2[1];
						val.pop_back();
						val = trim(val);						
						if (splt[0] == "int")
						{
							if (!isInt(val))
								Error("Invalid value at line " + to_string(i + 1));
						}
						else if (splt[0] == "float")
						{
							if (!isFloat(val))
								Error("Invalid value at line " + to_string(i + 1));
						}
						else if (splt[0] == "string")
						{
							if (!isString(val))
								Error("Invalid value at line " + to_string(i + 1));
						}
					}
					cpp.push_back(ln);
				}
			}
		}
	}
	if (waitForBrace) 
		Error("Missing opening brace at line " + to_string(lines.size()));
	if(openBraces > 0)
		Error("Missing closing brace at line " + to_string(lines.size()));
	return cpp;
}