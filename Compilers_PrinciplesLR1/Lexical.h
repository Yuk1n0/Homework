#pragma once
#include "pl0.h"
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

class Lexical 
{
private:
	string LexFileName;	//文件名
	FILE* fin;	//FILE指针
	char ch;	//保存词法分析中读取的单个字符
	int CC, LL;	//缓冲区长度
	int num;	//保存词法分析中的数字
	vector<string>in;	//输入流提供给语法分析
	;
	char a[11];	//读取组成标识符或保留字的单个字符
	char id[11];	//保存保留字或标识符
	char line[81];	//缓冲区
	char word[13][10];	//保存保留字
	enum symbol wsym[13];	//保存枚举类型中定义的保留字
	enum symbol ssym[256];	//保存枚举类型中定义的符号
	enum symbol sym;	//单词类型，从枚举类型中取出

public:
	Lexical();	//构造函数
	void init();	//初始化函数
	void getFileInfo();		//读取文件的信息并输出
	int getch();	//读出文件中的单个字符并保存在缓冲区中
	void doNumberPro();	//数字词法分析子程序
	void doLetterPro();	//标识符和保留字的词法分析子程序
	void doSymbolPro(int& tag);	//符号的词法分析子程序
	int getsym();	//词法分析主程序
	void printCompareTable(char** s); //输出单词类型对照表
	void lexAnalysis(string& input); //词法分析
};
