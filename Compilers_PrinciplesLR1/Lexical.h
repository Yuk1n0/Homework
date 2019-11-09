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
	string LexFileName;	//�ļ���
	FILE* fin;	//FILEָ��
	char ch;	//����ʷ������ж�ȡ�ĵ����ַ�
	int CC, LL;	//����������
	int num;	//����ʷ������е�����
	vector<string>in;	//�������ṩ���﷨����
	;
	char a[11];	//��ȡ��ɱ�ʶ�������ֵĵ����ַ�
	char id[11];	//���汣���ֻ��ʶ��
	char line[81];	//������
	char word[13][10];	//���汣����
	enum symbol wsym[13];	//����ö�������ж���ı�����
	enum symbol ssym[256];	//����ö�������ж���ķ���
	enum symbol sym;	//�������ͣ���ö��������ȡ��

public:
	Lexical();	//���캯��
	void init();	//��ʼ������
	void getFileInfo();		//��ȡ�ļ�����Ϣ�����
	int getch();	//�����ļ��еĵ����ַ��������ڻ�������
	void doNumberPro();	//���ִʷ������ӳ���
	void doLetterPro();	//��ʶ���ͱ����ֵĴʷ������ӳ���
	void doSymbolPro(int& tag);	//���ŵĴʷ������ӳ���
	int getsym();	//�ʷ�����������
	void printCompareTable(char** s); //����������Ͷ��ձ�
	void lexAnalysis(string& input); //�ʷ�����
};
