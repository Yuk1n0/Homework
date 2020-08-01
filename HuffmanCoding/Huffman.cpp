#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Huffman.h"
using namespace std;

int HuffmanCoding(HuffCode &pHC, HuffmanTree &pHT)
{
    char cd[SIZE] = {'\0'}; //记录访问路径
    int cdlen = 0;          //记录当前路径长度
    for (int i = 1; i < 2 * SIZE; i++)
    {
        pHT[i].weight = 0; //遍历Huffman树时用作节点的状态标志
    }
    int p = SIZE * 2 - 1; //根节点
    while (p != 0)
    {
        if (pHT[p].weight == 0)
        {
            pHT[p].weight = 1;
            if (pHT[p].lchild != 0)
            {
                p = pHT[p].lchild;
                cd[cdlen++] = '0';
            }
            if (pHT[p].rchild == 0)
            {
                pHC[p] = (char *)malloc((cdlen + 1) * sizeof(char));
                cd[cdlen] = '\0';
                strcpy(pHC[p], cd);
            }
        }
        else if (pHT[p].weight == 1)
        {
            pHT[p].weight = 2;
            if (pHT[p].rchild != 0)
            {
                p = pHT[p].rchild;
                cd[cdlen++] = '1';
            }
        }
        else //退回父节点，编码长度减1
        {
            pHT[p].weight = 0;
            p = pHT[p].parent;
            --cdlen;
        }
    }
    return 1;
}

int Select(HuffmanTree pHT, int nSize)
{
    int minValue = 0x7fffffff;
    int min = 0;
    for (int i = 1; i <= nSize; i++)
    {
        if (pHT[i].parent == 0 && pHT[i].weight < minValue)
        {
            minValue = pHT[i].weight;
            min = i;
        }
    }
    return min;
}

void CreatHuffmanTree(HuffmanTree *pHT, const int weight[])
{
    HTNode *cur = NULL;
    int s1, s2;
    int nNum = 2 * SIZE - 1;
    cur = (HTNode *)malloc(sizeof(HTNode) * (nNum + 1));
    for (int i = 1; i <= nNum; ++i)
    {
        cur[i].weight = i <= SIZE ? weight[i - 1] : 0;
        cur[i].lchild = cur[i].rchild = cur[i].parent = 0;
    }
    for (int i = SIZE + 1; i <= nNum; ++i)
    {
        s1 = Select(cur, i - 1);
        cur[s1].parent = i;
        s2 = Select(cur, i - 1);
        cur[s2].parent = i;
        cur[i].lchild = s1;
        cur[i].rchild = s2;
        cur[i].weight = cur[s1].weight + cur[s2].weight;
    }
    *pHT = cur;
}
