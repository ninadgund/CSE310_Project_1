
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <ctype.h>

#include "defns.h"

using namespace std;

typedef tree **TreeArray;

enum class SortAlgo
{
    DEFAULT_NONE,
    INSERTION_SORT,
    MERGE_SORT,
};

int symbolComp(const tree * s1, const tree * s2)
{
    if (s1->freq > s2->freq)
    {
        return 1;
    }
    else if(s1->freq < s2->freq)
    {
        return -1;
    }
    else
    {
        if (s1->symbol > s2->symbol)
        {
            return 1;
        }
        else if (s1->symbol < s2->symbol)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

bool insertionSort(TreeArray Symbols, int num)
{
    int i, j;
    tree * key;
    for (i = 1; i < num; i++)
    {
        key = Symbols[i];
        j = i - 1;
        while (j >= 0 && (symbolComp(Symbols[j], key) > 0))
        {
            Symbols[j + 1] = Symbols[j];
            j = j - 1;
        }
        Symbols[j + 1] = key;
    }
    return true;
}

bool mergeSort(TreeArray Symbols, int num)
{
    return false;
}

bool symbolSort(TreeArray Symbols, int num, SortAlgo mode)
{
    if (mode == SortAlgo::INSERTION_SORT)
    {
        return insertionSort(Symbols, num);
    }
    else if (mode == SortAlgo::MERGE_SORT)
    {
        return mergeSort(Symbols, num);
    }
    return false;
}

bool constructBTree(TreeArray Symbols, int num)
{
    while (num > 1)
    {
        symbol *currSym = new symbol;

        currSym->parent = NULL;
        currSym->left = Symbols[0]->root;
        Symbols[0]->root->parent = currSym;
        currSym->right = Symbols[1]->root;
        Symbols[1]->root->parent = currSym;
        
        currSym->freq = Symbols[0]->freq + Symbols[1]->freq;

        tree *currTree = new tree;
        currTree->freq = currSym->freq;
        currTree->root = currSym;
        
        delete Symbols[0];
        delete Symbols[1];
        int step = 2;
        for (int i = 2; i < num; i++)
        {
            if (step == 2 && Symbols[i]->freq > currTree->freq)
            {
                Symbols[i - step] = currTree;
                step = 1;
            }
            Symbols[i - step] = Symbols[i];
        }
        num--;
//        cout << currTree->freq << endl;
    }
    return true;
}

int main(int argc, char** argv)
{
    // Arguements read and verify
    if (argc < 3)
    {
       return EXIT_FAILURE;
    }
    // Preprocessed file name
    ifstream preFile(argv[1]);
    if (!preFile.is_open())
    {
       return EXIT_FAILURE;
    }
    // Sort method
    SortAlgo mode = SortAlgo::DEFAULT_NONE;
    if (strcmp(argv[2], "insertion") == 0)
    {
        mode = SortAlgo::INSERTION_SORT;
    }
    else if (strcmp(argv[2], "merge") == 0)
    {
        mode = SortAlgo::MERGE_SORT;
    }
    if (mode == SortAlgo::DEFAULT_NONE)
    {
       return EXIT_FAILURE;
    }
    
    // Initialize preprocess data
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
    // Read preprocessed data
    string line;
    int alphaCount = 0;
    int nonAlphaCount = 0;
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
            if (Symbols[symbol].freq > 0)
            {
                if (isalpha(symbol))
                {
                    alphaCount++;
                }
                else
                {
                    nonAlphaCount++;
                }
            }
        }
    }
    preFile.close();

    /*
        // Out preprocessed data (TODO remove later)
        for (int i = 0; i < NSYMBOLS; i++)
        {
            cout << i << "\t" << Symbols[i].freq << "\n";
        }
    */

    TreeArray alpha = new tree*[alphaCount];
    TreeArray nonAlpha = new tree*[nonAlphaCount];
    int alphaItr = 0;
    int nonAlphaItr = 0;
    tree * itr;
    for (int i = 0; i < NSYMBOLS; i++)
    {
        if (Symbols[i].freq > 0)
        {
//            cout << Symbols[i].freq << endl;
            if (isalpha(Symbols[i].symbol))
            {
                itr = new tree;
                alpha[alphaItr] = itr;
                itr->index = i;
                itr->symbol = Symbols[i].symbol;
                itr->freq = Symbols[i].freq;
                itr->root = &Symbols[i];
                alphaItr++;
            }
            else
            {
                itr = new tree;
                nonAlpha[nonAlphaItr] = itr;
                itr->index = i;
                itr->symbol = Symbols[i].symbol;
                itr->freq = Symbols[i].freq;
                itr->root = &Symbols[i];
                nonAlphaItr++;
            }
        }
    }

    symbolSort(alpha, alphaCount, mode);
    symbolSort(nonAlpha, nonAlphaCount, mode);

    constructBTree(alpha, alphaCount);
    constructBTree(nonAlpha, alphaCount);

    return 0;
}
