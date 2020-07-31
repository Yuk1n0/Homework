#pragma once
#ifndef COMPRESS_H
#define COMPRESS_H
#include "Huffman.h"

//文件头
struct HEAD
{
    char type[4];     //文件类型
    int length;       //源文件长度
    int weight[SIZE]; //权值数值
};

int InitHead(const char *pFilename, HEAD &sHead);
int Compress(char *pFilename); //
char Str2byte(const char *pBinStr);
char *Encode(const char *pFilename, const HuffCode pHC, char *pBuffer, const int nSize);
int WriteFile(const char *pFilename, const HEAD sHead, const char *pBuffer, const int nSzie);

#endif // !COMPRESS_H
