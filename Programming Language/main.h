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

vector<string> Parse(vector<string> lines);

// Files

vector<string> readFile(string fileName);

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
template<class T>
bool Contains(T element, T list[])
{
    for (int i = 0; i < sizeof(list); i++)
        if (list[i] == element)
            return true;
    return false;
}

#endif 
