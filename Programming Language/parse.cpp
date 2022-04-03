#include "main.h"

string braceTokens[] = { "void", "class", "switch" };
string varTokens[] = { "string", "int", "float"};

struct varDeclaration
{
	string type, name;
};

struct voidDeclaration
{
	string name;
	map<string, string> parameters;
	vector<string> returnVars;
};

void Error(string msg)
{
	cout << "ERROR: " << msg << endl;
	exit(1);
}

bool checkQuotes(string s)
{
	s = trim(s);
	if (s.length() < 2)
		return false;
	if (s[0] != s[s.length() - 1])
		return false;
	if (s[0] == '\'' && s.length() > 4)
		return false;
	if (s[0] == '\'' && s.length() == 4 && s[1] != '\\')
		return false;
	if (s[0] == '\'')
		return true;
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

varDeclaration parseVarDeclaration(string ln, vector<string> splt, string line, bool checkSemicolon = true)
{
	if (splt.size() > 4)
		Error("Invalid variable declaration (line " + line + ")");
	if (checkSemicolon && !endsWith(ln, ";"))
		Error("Missing ; at the end of the line (line " + line + ")");
	if (splt.size() == 1 || splt[1] == ";")
		Error("Missing var name (line " + line + ")");
	vector<string> splt2 = SplitOnce(JoinAt(splt, 1), '=');
	if (Contains(splt2[0], braceTokens) || Contains(splt2[0], varTokens))
		Error("Variable cannot have '" + splt2[0] + "' has name (line " + line + ")");
	if (!isValidVarName(splt2[0]))
		Error("Invalid variable name at line " + line + ". Can only contains [a-z], [A-Z] and '_' characters.");
	varDeclaration data;
	data.name = splt2[0];
	data.type = splt[0];
	if (splt2.size() == 2)
	{
		string val = splt2[1];
		if(checkSemicolon)
			val.pop_back();
		val = trim(val);
		if (splt[0] == "int")
		{
			if (!isInt(val))
				Error("Invalid value (line " + line + ")");
		}
		else if (splt[0] == "float")
		{
			if (!isFloat(val))
				Error("Invalid value (line " + line + ")");
		}
		else if (splt[0] == "string")
		{
			if (!isString(val))
				Error("Invalid value (line " + line + ")");
		}
	}
	return data;
}

voidDeclaration ParseVoidDeclaration(string ln, string line)
{
	voidDeclaration data;
	if (endsWith(ln, ";"))
		Error("Function can't be ended with a ';' (line " + line + ")");
	vector<string> splt = SplitOnce(ln, '(');	
	if (splt.size() == 1)
		Error("Invalid function declaration (line " + line + ")");
	vector<string> splt1 = SplitOnce(splt[0], ' ');
	if (splt1.size() == 1)
		Error("Missing function name (line " + line + ")");
	splt1[0] = trim(splt1[0]);
	if (Contains(splt1[1], braceTokens) || Contains(splt1[1], varTokens))
		Error("Function cannot have '" + splt1[0] + "' has name (line " + line + ")");
	if (!isValidVarName(splt1[1]))
		Error("Invalid function name at line " + line + ". Can only contains [a-z], [A-Z] and '_' characters.");
	data.name = splt1[1];
	vector<string> splt2 = SplitOnce(splt[1], ')');
	splt2[0] = trim(splt2[0]);
	if (splt2[0] != "")
	{
		vector<string> parameters = Split(splt2[0], ',');
		for (string p : parameters)
		{
			p = trim(p);
			varDeclaration v = parseVarDeclaration(p, Split(p, ' '), line, false);
			data.parameters.insert(data.parameters.end(), make_pair(v.name, v.type));
		}
	}
	if (splt2.size() == 2)
	{
		splt2[1] = trim(splt2[1]);
		vector<string> splt3 = SplitOnce(splt2[1], ':');
		if (splt3.size() == 2)
		{
			vector<string> splt4 = Split(splt3[1], ',');
			for (string s : splt4)
			{
				s = trim(s);
				if (s == "")
					Error("Empty variable type (line " + line + ")");
				if (!Contains(s, varTokens))
					Error(s + " is not a valide variable type (line " + line + ")");
				data.returnVars.push_back(s);
			}
		}
		else if (splt2[1] != "" && splt2[1] != "{")
			Error("Invalid function declaration (line " + line + ")");
	}
	return data;
}

vector<string> ParseBetweenBraces(vector<string> lines, int start, int end, vector<varDeclaration> variables)
{
	vector<string> cpp;
	return cpp;
}

vector<string> Parse(vector<string> code)
{
	vector<string> cpp;
	vector<string> lines;
	vector<int> linesCount;
	for (int i = 0; i < code.size(); i++)
	{
		vector<string> splt = Split(code[i], ';');
		linesCount.push_back(0);
		for (int y = 0; y < splt.size(); y++)
		{
			splt[y] = trim(splt[y]);
			if (splt[y] != "")
			{
				if (y + 1 < splt.size())
					splt[y] += ';';
				if (splt[y] == "{")				
					lines.push_back("{");				
				else
				{
					if(startsWith(splt[y], "{"))
						lines.push_back("{");
					vector<string> splt1 = Split(splt[y], '{');
					for (int x = 0; x < splt1.size(); x++)
					{
						if (trim(splt1[x]) != "")
						{
							lines.push_back(splt1[x]);
							linesCount[i]++;
							if (x + 1 < splt1.size())
							{
								lines.push_back("{");
								linesCount[i]++;
							}
						}
					}
				}
			}
		}
		if (linesCount[i] == 0)
		{
			linesCount[i]++;
			lines.push_back("");
		}
	}
	map<string, string> variables;
	map<string, voidDeclaration> voids;
	bool waitForBrace = false;
	int openBraces = 0, rl = 0, lnI = 1;
	for (int i = 0; i < lines.size(); i++)
	{
		string lineNb = to_string(rl);
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
						Error("Missing opening brace (line " + lineNb + ")");
				}
				if (ln == "}")
				{
					openBraces--;
					if (openBraces < 0)
						Error("Extra '}' (line " + lineNb + ")");
				}				
				else if (Contains(splt[0], braceTokens))
				{
					voidDeclaration data = ParseVoidDeclaration(trim(ln), lineNb);
					if (voids.find(data.name) != voids.end())
						Error("Function '" + data.name + "' already declared (line " + lineNb + ")");
					if (variables.find(data.name) != variables.end())
						Error("A variable is already declared with the name '" + data.name + "' (line " + lineNb + ")");
					for (auto const& x : data.parameters)
						if (variables.find(x.first) != variables.end())
							Error("Variable '" + x.first + "' already declared (line " + lineNb + ")");
					if (i + 1 >= lines.size() || lines[i + 1] != "{")
						Error("Missing '{' (line " + lineNb + ")");
					openBraces++;
					i++;
					voids.insert(voids.end(), make_pair(data.name, data));
				} 
				else if (Contains(splt[0], varTokens))
				{
					varDeclaration data = parseVarDeclaration(ln, splt, lineNb);
					if (variables.find(data.name) != variables.end())
						Error("Variable '" + data.name + "' already declared (line " + lineNb + ")");
					if (voids.find(data.name) != voids.end())
						Error("A function is already declared with the name '" + data.name + "' (line " + lineNb + ")");
					variables.insert(variables.end(), make_pair(data.name, data.type));
					cpp.push_back(ln);
				}
				else if (ln == "{")
				{
					Error("Extra '{' (line " + lineNb + ")");
				}
			}
		}
		lnI++;
		if (rl < linesCount.size() && lnI >= linesCount[rl])
		{
			lnI = 1;
			rl++;
		}
	}
	if (waitForBrace) 
		Error("Missing opening brace at line " + to_string(code.size()));
	if(openBraces > 0)
		Error("Missing closing brace at line " + to_string(code.size()));
	return cpp;
}