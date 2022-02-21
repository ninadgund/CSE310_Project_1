
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

// Types of sorting algorithms supported and implemented
enum class SortAlgo
{
    DEFAULT_NONE,
    INSERTION_SORT,
    MERGE_SORT,
};

// Comparison logic to be used between tree nodes
int symbolComp(const tree * s1, const tree * s2)
{
    // First comparing based on frequency
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
        // In case of same frequency, compare based on lexicographical value
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

// Iterative function for insertion sort, sorts the array in place
void insertionSort(TreeArray Symbols, int num)
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
}

// Internal merge function for mergesort
void merge(TreeArray Symbols, int p, int q, int r)
{
    int ln = q - p + 1;
    int rn = r - q;

    // Temporary left, right subarrays
    TreeArray lArr = new tree*[ln];
    TreeArray rArr = new tree*[rn];
    
    // Coping data to temp arrays
    for (int i = 0; i < ln; i++)
    {
        lArr[i] = Symbols[p + i];
    }
    for (int i = 0; i < rn; i++)
    {
        rArr[i] = Symbols[q + 1 + i];
    }

    int lItr = 0;
    int rItr = 0;
    int mergedItr = p;

    // Merging temp arrays to original array
    while (lItr < ln && rItr < rn)
    {
        if (symbolComp(lArr[lItr], rArr[rItr]) <= 0)
//        if (lArr[lItr] <= rArr[rItr])
        {
            Symbols[mergedItr] = lArr[lItr];
            lItr++;
        }
        else
        {
            Symbols[rItr] = rArr[rItr];
            rItr++;
        }
        mergedItr++;
    }
    // Copy remaining elements, if any
    while (lItr < ln)
    {
        Symbols[mergedItr] = lArr[lItr];
        lItr++;
        mergedItr++;
    }
    while (rItr < rn)
    {
        Symbols[mergedItr] = rArr[rItr];
        rItr++;
        mergedItr++;
    }
    delete lArr;
    delete rArr;
}

// Internal recursive function for mergesort
void mergeSort_rec(TreeArray Symbols, int p, int r)
{
    if (p >= r)
    {
        return;
    }
    int q = p + ((r - p) / 2);
    mergeSort_rec(Symbols, p, q);
    mergeSort_rec(Symbols, q + 1, r);
    merge(Symbols, p, q, r);
}

// Wrapper function for merge sort, sorts the array in place
void mergeSort(TreeArray Symbols, int num)
{
    mergeSort_rec(Symbols, 0, num - 1);
}

// Sorts the array using specified sorting algo
bool symbolSort(TreeArray Symbols, int num, SortAlgo mode)
{
    if (mode == SortAlgo::INSERTION_SORT)
    {
        insertionSort(Symbols, num);
        return true;                                // Return success
    }
    else if (mode == SortAlgo::MERGE_SORT)
    {
        mergeSort(Symbols, num);
        return true;                                // Return success
    }
    return false;                                   // Return failure
}

// Constructs btree from tree* array iteratively
int constructBTree(TreeArray Symbols, int num)
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
        if (step == 2)
        {
            Symbols[num - step] = currTree;
        }
        num--;
    }
    return num;
}

// Returns a new node with left and right nodes as l, r params
tree * combineTrees(tree * left, tree * right)
{
    symbol * rootNode = new symbol;
    rootNode->parent = NULL;
    rootNode->freq = left->freq + right->freq;
    rootNode->left = left->root;
    rootNode->right = right->root;

    left->root->parent = rootNode;
    right->root->parent = rootNode;

    tree * rootTree = new tree;
    rootTree-> freq = rootNode->freq;
    rootTree->root = rootNode;
    return rootTree;
}

// Traverses the btree to set the encoding value of all node characters
void encodeTree(symbol * symNode, char bit, int level)
{
    if(symNode == NULL)
    {
        return;
    }
    if (level < E_LEN)
    {
        strncpy(symNode->encoding, symNode->parent->encoding, level);
        symNode->encoding[level] = bit;
        symNode->encoding[level+1] = '\0';
        encodeTree(symNode->left, '0', level + 1);
        encodeTree(symNode->right, '1', level + 1);
    }
}

// Wrapper function to encode all characters in the btree
void encodeTree(tree * rootTree)
{
    encodeTree(rootTree->root->left, '0', 0);
    encodeTree(rootTree->root->right, '1', 0);
}

// Getter function to return encoded value of a character
string encodeChar(symbol * Symbols, char c)
{
    return string(Symbols[(int)c].encoding);
}

// Function to decode encoded string using btree
string decodeText(tree * rootNode, string &input)
{
    string out = "";
    symbol * node = rootNode->root;
    for (int i = 0; i < input.length(); i++)
    {
        if(input[i] == '0')
        {
            if (node->left == nullptr)
            {
                out += node->symbol;
                node = rootNode->root;
                i--;
                continue;
            }
            node = node->left;
        }
        else if(input[i] == '1')
        {
            if (node->right == nullptr)
            {
                out += node->symbol;
                node = rootNode->root;
                i--;
                continue;
            }
            node = node->right;
        }
    }
    out += '\n';
    return out;
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

    TreeArray alpha = new tree*[alphaCount];
    TreeArray nonAlpha = new tree*[nonAlphaCount];
    int alphaItr = 0;
    int nonAlphaItr = 0;
    tree * itr;
    for (int i = 0; i < NSYMBOLS; i++)
    {
        if (Symbols[i].freq > 0)
        {
            if (isalpha(Symbols[i].symbol))
            {
                itr = new tree;
                itr->index = i;
                itr->symbol = Symbols[i].symbol;
                itr->freq = Symbols[i].freq;
                itr->root = &Symbols[i];
                alpha[alphaItr] = itr;
                alphaItr++;
            }
            else
            {
                itr = new tree;
                itr->index = i;
                itr->symbol = Symbols[i].symbol;
                itr->freq = Symbols[i].freq;
                itr->root = &Symbols[i];
                nonAlpha[nonAlphaItr] = itr;
                nonAlphaItr++;
            }
        }
    }
    
    symbolSort(alpha, alphaCount, mode);
    symbolSort(nonAlpha, nonAlphaCount, mode);

    constructBTree(alpha, alphaCount);
    constructBTree(nonAlpha, nonAlphaCount);

    tree * rootTree = combineTrees(alpha[0], nonAlpha[0]);
    delete alpha[0];
    delete nonAlpha[0];

    // Reading 'n', number of symbols with non zero frequency
    string in_line;
    int sym_n = 0;
    if (getline(cin, in_line))
    {
        sym_n = stoi(in_line);
        for (int i = 0; i < (sym_n + 2); i++)
        {
            getline(cin, in_line);
        }
    }

    // Reading encoded input
    string plaintext;
    if(getline(cin, in_line))
    {
        plaintext = decodeText(rootTree, in_line);
    }
    // Printing decoded output
    cout << plaintext;

    return 0;
}
