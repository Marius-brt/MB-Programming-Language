#include "main.h"

int main(int argc, char *argv[])
{
    vector<string> lines = readFile("main.mb");
    parserResult res = Parse(lines);
    cout << "CPP ---------" << endl;
    for (string l : res.cpp)
        cout << l << endl;
    cout << "-------------" << endl;
    cout << "Header ------" << endl;
    for (string l : res.header)
        cout << l << endl;
    cout << "-------------" << endl;
    cout << "Ok!" << endl;
    return 0;
}