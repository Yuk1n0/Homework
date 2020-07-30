#pragma once
#define SIZE 256

typedef struct HTNode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} * HuffmanTree;

typedef char **HuffCode;
void CreatHuffmanTree(HuffmanTree *pHT, const int weight[]);
int HuffmanCoding(HuffCode &pHC, HuffmanTree &pHT);
int Select(HuffmanTree pHT, int nSize);
