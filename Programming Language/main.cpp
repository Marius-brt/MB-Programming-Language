#include "main.h"

int main()
{
    vector<string> lines = readFile("main.mb");
    vector<string> cpp = Parse(lines);
    /*for (string l : cpp)
        cout << l << endl;*/
    cout << "Ok!" << endl;
    return 0;
}