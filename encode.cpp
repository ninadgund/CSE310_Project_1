
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>

#include "defns.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 3)
    {
       return EXIT_FAILURE;
    }

    ifstream preFile(argv[1]);
    if (!preFile.is_open())
    {
       return EXIT_FAILURE;
    }

    int mode = 0;
    if (strcmp(argv[2], "insertion") == 0)
    {
        mode = 1;
    }
    else if (strcmp(argv[2], "merge") == 0)
    {
        mode = 2;
    }
    if (mode == 0)
    {
       return EXIT_FAILURE;
    }
    
    symbol Symbols[NSYMBOLS];
    for (int i = 0; i < NSYMBOLS; i++)
    {
        Symbols[i].symbol = i;
        Symbols[i].freq = 0;
        Symbols[i].parent = NULL;
        Symbols[i].left = NULL;
        Symbols[i].right = NULL;
        memset(Symbols[i].encoding, 0, E_LEN);
    }

    string line;
    while (getline(preFile, line))
    {
        istringstream iss(line);
        string token;
        int symbol;
        if (std::getline(iss, token, '\t'))
        {
            symbol = stoi(token);
        }
        if (std::getline(iss, token, '\n'))
        {
            Symbols[symbol].freq = stoi(token);
        }
    }
    preFile.close();

    for (int i = 0; i < NSYMBOLS; i++)
    {
        cout << i << "\t" << Symbols[i].freq << "\n";
    }

    return 0;
}
