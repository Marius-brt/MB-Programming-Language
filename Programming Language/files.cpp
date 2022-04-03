#include "main.h"

vector<string> readFile(string fileName)
{
    ifstream file(fileName);
    if (file.is_open()) {
        string ln;
        vector<string> lines;
        while (std::getline(file, ln))
            lines.push_back(ln);
        return lines;
    }
    else 
    {
        cout << "Failed to read " + fileName << endl;
        exit(EXIT_FAILURE);
    }
}