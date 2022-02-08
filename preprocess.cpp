
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>

#include "defns.h"

using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
       return EXIT_FAILURE;
    }
    
    for (int i = 0; i < argc; ++i)
    {
        std::cout << argv[i] << std::endl;
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

    FILE* preFile;
    char c = 0;

    preFile = fopen(argv[1], "r");
    if (preFile == NULL)
    {
       return EXIT_FAILURE;
    }

    while (!feof(preFile))
    {
       c = getc(preFile);
       int i = c;
       if (i >= 0 && i < NSYMBOLS)
       {
           Symbols[i].freq++;
       }
    }
    fclose(preFile);

    for (int i = 0; i < NSYMBOLS; i++)
    {
        cout << i << "\t" << Symbols[i].freq << "\n";
    }

    return 0;
}
