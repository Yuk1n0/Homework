#pragma once
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<stack>
#include<iostream>
#define INT 1
#define CHAR 2
using namespace std;

/*action*/
enum act 
{
    error = 0,	//����
    shift,	//�ƽ�
    reduce,	//��Լ	
    accept	//����
};

/*��Ŀ��*/
class Program 
{
    /*��Ŀ�����LR����Ϊ��Ԫ*/
    friend class Item;
    friend class LR;
    
    friend bool operator == (const Program& a, const  Program& b);	//�ж�������Ŀ�Ƿ����
    friend bool operator == (const Item& a, const Item& b);		//�ж�������Ŀ���Ƿ����
    
public:
    Program(char l, string r, set<char> s, int rank);
    Program& operator = (const Program& b);	//���ظ�ֵ�����
    
private:
    char left;	//����ʽ��
    string right;	//����ʽ�Ҳ�
    int rank;	//���ķ��е��ĸ�����ʽ����
    set<char> search;	//��������
};

/*��Ŀ����*/
class Item 
{
    friend class LR;
    friend bool operator == (const Item& a, const Item& b);	//�ж�������Ŀ���Ƿ����
    
public:
    bool addPro(const Program& pro, Item& i);	//����Ŀ���м�����Ŀ
    void insertVT(Item& i, Item g);	//�������Ŀ���ս����
    void insertVN(Item& i);	//�������Ŀ���ķ��ս����
    void insertV(Item& i);	//�������Ŀ�������з��ż�
private:
    vector<Program> pro;	//��Ŀ��
    vector<char> vn;		//����Ŀ���ķ��ս����
    vector<char> vt;		//����Ŀ�����ս����
    vector<char> v;			//����Ŀ�������з��ż�
};

/*LR(1)*/
class LR 
{
private:
    Item g; //��չ�ķ�
    char start;	//��ʼ����
    vector<Item> M;	//������Ŀ���ļ���
    string input;	//������Ŵ�
    map<pair<int, char>, pair<act, int>> ACTION;	//ACTION����һ��pair��intΪԭ��Ŀ������ţ�char��ʾ�ս�����ڶ���pair��act��ʾͨ������ս����Ҫ���Ķ�����int��ʾĿ����Ŀ��
    map<pair<int, char>, int> GOTO;	//GOTO��pair�е�int��ʾԭ��Ŀ����ţ�char��ʾ���ս����int��ʾͨ���÷������������Ŀ��
    map<char, set<char>> FIRST;	//����������ͨ�����ս�����ȡ
    map<pair<int, char>, int> GO;	//GO��ͨ��ԭ��Ŀ������ط�������ȡ
    stack<int> state;	//״̬ջ
    stack<char>symbol;	//����ջ
public:
    LR(char start, Item g, string input);	//���캯��
    Item getClosure(Item& i);	//�õ���Ŀ����CLOSURE�հ�
    set<char> getFirst(const string& r, const char& N);	//�õ���������
    void go();	//GO��������GO��
    void getAction();	//����ACTION��
    void getGoto();	//����GOTO��
    void showTable();	//���������
    bool analyse();	//��������
    void unionSet(Program& a, const Program& b);	//�ϲ���������
    template <typename T>
    string turnFromStack(stack<T> s, int TYPE);	//��ջ�е�һ����Ԫ�������ַ���
};
