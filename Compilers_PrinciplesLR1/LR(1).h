#pragma once
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <iostream>
using namespace std;

#define INT 1
#define CHAR 2

/*action*/
enum act
{
    error = 0, //错误
    shift,     //移进
    reduce,    //规约
    accept     //接受
};

/*项目类*/
class Program
{
    /*项目集类和LR类作为友元*/
    friend class Item;
    friend class LR;

    friend bool operator==(const Program &a, const Program &b); //判断两个项目是否相等
    friend bool operator==(const Item &a, const Item &b);       //判断两个项目集是否相等

public:
    Program(char l, string r, set<char> s, int rank);
    Program &operator=(const Program &b); //重载赋值运算符

private:
    char left;        //产生式左部
    string right;     //产生式右部
    int rank;         //由文法中的哪个产生式得来
    set<char> search; //搜索符集
};

/*项目集类*/
class Item
{
    friend class LR;
    friend bool operator==(const Item &a, const Item &b); //判断两个项目集是否相等

public:
    bool addPro(const Program &pro, Item &i); //往项目集中加入项目
    void insertVT(Item &i, Item g);           //构造该项目的终结符集
    void insertVN(Item &i);                   //构造该项目集的非终结符集
    void insertV(Item &i);                    //构造该项目集的所有符号集
private:
    vector<Program> pro; //项目集
    vector<char> vn;     //该项目集的非终结符集
    vector<char> vt;     //该项目集的终结符集
    vector<char> v;      //该项目集的所有符号集
};

/*LR(1)*/
class LR
{
private:
    Item g;                                      //扩展文法
    char start;                                  //开始符号
    vector<Item> M;                              //所有项目集的集合
    string input;                                //输入符号串
    map<pair<int, char>, pair<act, int>> ACTION; //ACTION表，第一个pair中int为原项目集的序号，char表示终结符，第二个pair中act表示通过这个终结符所要做的动作，int表示目的项目集
    map<pair<int, char>, int> GOTO;              //GOTO表，pair中的int表示原项目集序号，char表示非终结符，int表示通过该符号所到达的项目集
    map<char, set<char>> FIRST;                  //搜索符集，通过非终结来获取
    map<pair<int, char>, int> GO;                //GO表，通过原项目集和相关符号来获取
    stack<int> state;                            //状态栈
    stack<char> symbol;                          //符号栈
public:
    LR(char start, Item g, string input);               //构造函数
    Item getClosure(Item &i);                           //得到项目集的CLOSURE闭包
    set<char> getFirst(const string &r, const char &N); //得到搜索符集
    void go();                                          //GO函数构建GO表
    void getAction();                                   //构建ACTION表
    void getGoto();                                     //构建GOTO表
    void showTable();                                   //输出分析表
    bool analyse();                                     //分析过程
    void unionSet(Program &a, const Program &b);        //合并搜索符集
    template <typename T>
    string turnFromStack(stack<T> s, int TYPE); //将栈中的一个个元素连成字符串
};
