
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdio.h>

#include "defns.h"

using namespace std;

int main(int argc, char** argv)
{
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

    char c = getc(stdin);
    while (c != EOF)
    {
       int i = c;
       if (i >= 0 && i < NSYMBOLS)
       {
           Symbols[i].freq++;
       }
       c = getc(stdin);
    }
    Symbols[(int)'\n'].freq++;

    for (int i = 0; i < NSYMBOLS; i++)
    {
        if (Symbols[i].freq > 0)
        {
            cout << i << "\t" << Symbols[i].freq << "\n";
        }
    }

    return 0;
}
