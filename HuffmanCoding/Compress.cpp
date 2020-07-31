#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Compress.h"
#include "Huffman.h"
using namespace std;

int Compress(char *pFilename)
{
    HTNode *pHT = NULL;
    HuffCode pHC = (char **)malloc((SIZE + 1) * sizeof(char *));
    for (int j = 0; j < SIZE; j++)
    {
        pHC[j] = (char *)malloc((SIZE + 1) * sizeof(char)); //这个指针数组的每个指针元素又指向一个数组。
    }

    //读取原文件,获得权重保存进weight[]
    int weight[SIZE] = {0};
    int ch = 0;
    unsigned long nSize = 0; //缓冲区大小即文件所占字节

    char *fileName = pFilename;
    FILE *in = fopen(fileName, "rb");
    while (in == NULL)
    {
        cout << "输入的文件名无效或文件不存在！" << endl;
        cout << "请重新输入文件名：";
        cin >> fileName;
        in = fopen(fileName, "rb");
    }
    while ((ch = getc(in)) != EOF)
    {
        weight[ch]++;
    }
    fclose(in);
    in = NULL;

    unsigned long fileSize = 0;
    for (int i = 0; i < SIZE; i++)
    {
        fileSize += weight[i];
    }
    cout << fileSize << "Byte" << endl;

    //调用HuffmanTree()及HuffmanCoding()生成Huffman编码
    CreatHuffmanTree(&pHT, weight);
    if (!HuffmanCoding(pHC, pHT))
    {
        return 0;
    }

    //显示256种字节的出现次数
    cout << "Byte "
         << "Weight" << endl;
    for (int i = 0; i < 256; i++)
    {
        printf("0x%02X %d\n", i, weight[i]);
    }

    //获取缓存区大小
    for (int i = 0; i < SIZE; ++i)
    {
        nSize += weight[i] * strlen(pHC[i + 1]);
    }
    nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

    //调用Encode()函数，实现文件编码保存在内存缓冲区
    char *pBuffer = NULL;
    pBuffer = Encode(pFilename, pHC, pBuffer, nSize);
    if (!pBuffer)
    {
        return 0;
    }

    HEAD sHead;
    unsigned long len = 0;
    if (InitHead(pFilename, sHead))
    {
        len = WriteFile(pFilename, sHead, pBuffer, nSize);
    }
    cout << len << "Byte" << endl;
    double per;
    per = (len * 1.0 / fileSize) * 100;
    printf("压缩比率：%6.4f", per);
    cout << "%" << endl;
    return 1;
}

int InitHead(const char *pFilename, HEAD &sHead)
{
    strcpy(sHead.type, "HUF"); //文件类型
    sHead.length = 0;
    for (int i = 0; i < SIZE; i++)
    {
        sHead.weight[i] = 0; //权值
    }

    FILE *in = fopen(pFilename, "rb");
    if (!in)
    {
        printf("文件打开失败！");
        return 0;
    }

    int ch = 0;
    while ((ch = getc(in)) != EOF)
    {
        sHead.weight[ch]++;
        sHead.length++;
    }
    fclose(in);
    in = NULL;
    return 1;
}

char *Encode(const char *pFilename, const HuffCode pHC, char *pBuffer, const int nSize)
{
    FILE *in = fopen(pFilename, "rb");
    pBuffer = (char *)malloc(nSize * sizeof(char));
    if (!pBuffer)
    {
        cerr << "创建缓冲区失败" << endl;
        return 0;
    }

    char cd[SIZE] = {0}; //工作区
    int pos = 0;         //缓冲区指针
    int ch = 0;

    //扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓冲区中。
    while ((ch = fgetc(in)) != EOF)
    {
        strcat(cd, pHC[ch + 1]); //从HC复制编码串到cd,压缩编码
        while (strlen(cd) >= 8)
        {
            //截取字符串左边的8个字符，编码成字节
            pBuffer[pos++] = Str2byte(cd);
            //字符串整体左移
            for (int i = 0; i < SIZE - 8; i++)
            {
                cd[i] = cd[i + 8];
            }
        }
    }

    if (strlen(cd) > 0)
    {
        pBuffer[pos++] = Str2byte(cd);
    } //strlen所作的仅仅是一个计数器的工作，它从内存的某个位置（可以是字符串开头，中间某个位置，甚至是某个不确定的内存区域）开始扫描，直到碰到第一个字符串结束符'\0'为止，然后返回计数器值(长度不包含'\0')。
    return pBuffer;
}

char Str2byte(const char *pBinStr)
{
    int b = 0x00;
    for (int i = 0; i < 8; i++)
    {
        b = b << 1; //左移一位,<<为左移运算符
        if (pBinStr[i] == '1')
        {
            b = b | 0x01;
        }
    }
    return b;
}

int WriteFile(const char *pFilename, const HEAD sHead, const char *pBuffer, const int nSize)
{
    char filename[SIZE] = {0};
    strcpy(filename, pFilename);
    strcat(filename, ".huf"); //将两个char类型连接
    FILE *out = fopen(filename, "wb");
    if (!out)
    {
        return 0;
    }
    fwrite(&sHead, sizeof(HEAD), 1, out);
    fwrite(pBuffer, sizeof(char), nSize, out);
    fclose(out);
    out = NULL;
    cout << "生成压缩文件：" << filename << endl;
    int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
    return len;
}
