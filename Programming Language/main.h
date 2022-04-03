#ifndef  MAIN_H
#define MAIN_H

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdarg>
#include <map>

using namespace std;

// Parser

struct parserResult
{
	vector<string> cpp;
	vector<string> header;
};
parserResult Parse(vector<string> code);

// Files

vector<string> readFile(string fileName);

// Variables

bool isValidVarName(string s);
bool isChar(string s);
bool isString(string s);
bool isFloat(string s);
bool isInt(string s);
bool checkQuotes(string s);

// Utils

string ltrim(const string& s);
string trim(const string& s);
bool startsWith(string str, string prefix);
bool startsWith(string str, string prefixes[]);
bool endsWith(const string& mainStr, const string& toMatch);
vector<string> Split(string str, string seperator);
vector<string> Split(string str, char seperator);
vector<string> SplitOnce(string str, char seperator);
string JoinAt(vector<string> str, int index, string join = "");
bool Contains(string element, vector<string> list);

#endif 
