#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Error! Usage: ./grade <file-name>" << endl;
        return 0;
    }

    if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0))
    {
        cout << "Usage: ./grade <file-name>" << endl;
        return 0;
    }

    char ch;

    fstream fin(argv[1], fstream::in);

    int cc = 0;

    while (fin >> noskipws >> ch)
    {
        if (ch == (int)',' || ch == (int)';')
        {
            cc++;
        }
    }

    if (cc <= 65)
    {
        cout << "The count of , and ; is " << cc << " out of 65" << endl;
    }
    else
    {
        cout << "The count of , and ; is " << cc << " out of 65" << endl;
        cout << "That is " << 65 - cc << " too many" << endl;
    }

    return 0;
}