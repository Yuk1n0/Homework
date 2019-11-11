#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

char Filename[100];
struct wnode
{
    char id;
    int n; //编号
    char text[20];
    wnode *next;
};

struct Gnode //存储产生式
{
    string gen;
    int id;
};

Gnode grammar[6];
void initGrammar(); //初始化产生式表
wnode *lexcial(wnode *head);
int check(int s, char v);                                         //查LR分析表
void gammarAnalysis(wnode *head);                                 //语法分析及进行相应的语义操作并产生四元式
void showS(int opS[], int tops, char opC[], int topc, wnode *hp); //显示分析栈的内容

//用于if-else分析
int LR[11][9] =
    {
        //________ACTION_________|___GOTO___
        // i   t   e   A   E   #   S   C   T
        {105, 0, 0, 104, 0, 0, 101, 102, 103}, //0
        {0, 0, 0, 0, 0, -1, 0, 0, 0},          //1
        {105, 0, 0, 104, 0, 0, 106, 102, 103}, //2
        {105, 0, 0, 104, 0, 0, 110, 102, 103}, //3
        {0, 0, 3, 0, 0, 3, 0, 0, 0},           //4
        {0, 0, 0, 0, 108, 0, 0, 0, 0},         //5
        {0, 0, 107, 0, 0, 1, 0, 0, 0},         //6
        {5, 0, 0, 5, 0, 0, 0, 0, 0},           //7
        {0, 109, 0, 0, 0, 0, 0, 0, 0},         //8
        {4, 0, 0, 4, 0, 0, 0, 0, 0},           //9
        {0, 0, 2, 0, 0, 2, 0, 0, 0}            //10
};

/*此表中引用记号的意义是：
 * （1）Sj          把下一状态j和现行输入符号移进栈；
 * （2）rj          按第j个产生式进行归约；
 * （3）acc         接受；(-1)
 * （4）空白格      出错标志，报错；*/

void initGrammar()
{
    grammar[0].gen = "S'->S";
    grammar[0].id = 0;
    grammar[1].gen = "S->CS";
    grammar[1].id = 1;
    grammar[2].gen = "S->TS";
    grammar[2].id = 2;
    grammar[3].gen = "S->A";
    grammar[3].id = 3;
    grammar[4].gen = "C->if E then";
    grammar[4].id = 4;
    grammar[5].gen = "T->CS else";
    grammar[5].id = 5;
    cout << "所用文法:" << endl;
    int i, j;
    for (i = 1; i < 6; i++)
        cout << grammar[i].id - 1 << '\t' << grammar[i].gen << endl;
    cout << "5" << '\t' << "T->else" << endl;
    cout << "注：i--if t--then e--else" << endl;
    cout << "    E——布尔表达式（在语法分析中看成是终结符）" << endl;
    cout << "    A——赋值语句（在语法分析中看成是终结符）" << endl;
    cout << "SLR(1)分析表：" << endl;
    cout << setw(22) << "ACTION" << setw(18) << "|" << setw(10) << "GOTO" << endl;
    cout << setw(8) << "i" << setw(6) << "t" << setw(6) << "e" << setw(6) << "A" << setw(6) << "E"
         << setw(6) << "#" << setw(6) << "S" << setw(6) << "C" << setw(6) << "T" << endl;
    for (i = 0; i < 11; i++)
    {
        cout << setw(2) << i;
        for (j = 0; j < 9; j++)
        {
            if (LR[i][j] >= 110)
                cout << setw(4) << "S" << LR[i][j] - 100;
            else if (LR[i][j] > 100)
                cout << setw(5) << "S" << LR[i][j] - 100;
            else if (LR[i][j] > 0)
                cout << setw(5) << "r" << LR[i][j];
            else if (LR[i][j] == 0)
                cout << setw(6) << " ";
            else
                cout << setw(6) << "ACC";
        }
        cout << endl;
    }
}

bool ischar(char c) //检测是否为分界符
{
    bool r = false;
    switch (c)
    {
    case ' ':
    case '\n':
    case ';':
        r = true;
        break;
    default:;
    }
    return r;
}

int word()
{
    char ch = ' ';
    int num = 0;
    ifstream source("source.txt");
    ofstream analysis("analysis.txt");
    char yunsuanfu[11] = {'+', '-', '*', '/', '<', '>', '=', '!', '%', '&', '|'};
    char jiefu[9] = {',', ';', '(', ')', '{', '}', '[', ']', '#'};
    char *guanjianzi[20] = {
        (char *)"int",
        (char *)"if",
        (char *)"else",
        (char *)"then",
        (char *)"do",
        (char *)"while",
        (char *)"break",
        (char *)"continue",
        (char *)"switch",
        (char *)"return",
        (char *)"when",
        (char *)"for",
        (char *)"double",
        (char *)"main",
        (char *)"break",
        (char *)"include",
        (char *)"short",
        (char *)"long",
        (char *)"float",
        (char *)"char",
    };
    char *biaoshifu[100] = {(char *)"\0"};
    while (!source.eof())
    {
        source.get(ch);
        char shuzi[20] = "";
        int i = 1;
        if (ch >= '0' && ch <= '9') //判断数字
        {
            shuzi[0] = ch;
            source.get(ch);
            while (((ch >= '0' && ch <= '9') || ch == '.') && !source.eof())
            {
                cout << ch;
                shuzi[i++] = ch;
                source.get(ch);
            }
            analysis << shuzi << "数字" << endl;
        }
        for (i = 0; i <= 10; i++) //运算符判断
        {
            if (ch == yunsuanfu[i])
            {
                analysis << ch << "运算符" << endl;
            }
        }
        for (i = 0; i < 9; i++) //界符
        {
            if (ch == jiefu[i])
            {
                analysis << ch << "界符" << endl;
            }
        }
        if (ch >= 'a' && ch <= 'z') //关键字判断
        {
            char str1[20];
            int sign = 0;
            int n = 0;
            while (((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '_') && !source.eof())
            {
                str1[n] = ch;
                source.get(ch);
                n++;
            }
            str1[n] = '\0';
            for (i = 0; i < 20; i++)
            {
                if (!strcmp(str1, guanjianzi[i]))
                {
                    analysis << str1 << "关键字" << endl;
                    sign = 1;
                }
            }
            if (sign == 0)
            {
                analysis << str1 << "标识符" << endl;
            }
            for (i = 0; i <= 10; i++) //运算符判断
            {
                if (ch == yunsuanfu[i])
                {
                    analysis << ch << "运算符" << endl;
                }
            }
            for (i = 0; i < 9; i++) //界符
            {
                if (ch == jiefu[i])
                {
                    analysis << ch << "界符" << endl;
                }
            }
        }
    }
    analysis.close();
    source.close();
    return 0;
}

wnode *lexcial(wnode *head)
{
    string str;
    int loc = -1;
    char c;
    int i, k = 0, mark = 0;
    int Acount = 0, Ecount = 0;
    wnode *p, *q;
    p = head;
    q = new wnode;
    q->text[0] = '\0';
    q->n = 0;
    q->next = NULL;
    fstream infile(Filename); //根据输入的路径名来打开这个文件
    while (infile.get(c))
    {
        if (ischar(c))
        {
            if (mark == 1)
            {
                q->text[k] = '\0';
                for (i = 0; q->text[i] != '\0'; i++)
                    if (q->text[i] == '=')
                        loc = i;
                if (p->id == 'i')
                {
                    q->id = 'E';
                    q->n = ++Ecount;
                }
                else if (loc != -1)
                {
                    q->id = 'A';
                    q->n = ++Acount;
                }
                else
                {
                    q->id = q->text[0];
                    if (q->id == 'i')
                        head->n++;
                }
                p->next = q;
                p = q;
                mark = 0;
            }
        }
        else
        {
            if (mark == 0)
            {
                q = new wnode;
                q->n = 0;
                q->next = NULL;
                loc = -1;
                k = 0;
                mark = 1;
            }
            q->text[k++] = c;
        }
    }
    //在末尾加上一个'#'
    q = new wnode;
    q->next = NULL;
    q->id = '#';
    q->text[0] = '\0';
    q->n = 0;
    p->next = q;
    return head;
}

//语法分析
void gammarAnalysis(wnode *head)
{
    char E[20];
    char A[20];
    char r, d1, d2;
    int tn = 0, en = head->n;
    ofstream table;
    table.open("siyuanshi.txt");
    if (!table)
    {
        cout << "Cannot open output file!" << endl;
        exit(1);
    }
    cout << "语法分析过程：" << endl;
    cout << "分析栈   输入串   操作" << endl;
    int opS[20];  //记录状态，状态栈
    char opC[20]; //记录符号，符号栈
    int mark = -1, i, count = 0;
    int loc = 99; //指示程序指令地址
    char c;
    wnode *p;
    p = head->next;
    int tops = 0;
    int topc = 0;
    opS[tops] = 0;
    opC[topc] = '#';
    while (p)
    {
        showS(opS, tops, opC, topc, p);
        if (tops < topc)
            c = opC[tops + 1];
        else
        {
            c = p->id;
            if (c == 'E')
            {
                for (i = 0; i < 20 && p->text[i] != '\0'; i++)
                    E[i] = p->text[i];
                E[i] = '\0';
            }
            if (c == 'A')
            {
                for (i = 0; i < 20 && p->text[i] != '\0'; i++)
                    A[i] = p->text[i];
                A[i++] = ';';
                A[i] = '\0';
            }
        }
        mark = check(opS[tops], c);
        switch (mark)
        {
        case -1:
            cout << '\t' << "语法分析,翻译成功~~~" << endl;
            table << ++loc;
            table.close();
            return;
        case 1:
            tops = tops - 2;
            topc = topc - 1;
            opC[topc] = 'S';
            cout << '\t' << '\t' << " 归约  " << grammar[1].gen << endl;
            break;
        case 2:
            tops = tops - 2;
            topc = topc - 1;
            opC[topc] = 'S';
            cout << '\t' << '\t' << " 归约  " << grammar[2].gen << endl;
            break;
        case 3:
            tops = tops - 1;
            topc = topc - 0;
            opC[topc] = 'S';
            cout << '\t' << '\t' << " 归约  " << grammar[3].gen << endl;
            r = A[3];
            d1 = A[2];
            d2 = A[4];
            table << ++loc << "\t(" << r << '\t' << d1 << '\t' << d2 << '\t' << 'T' << ++tn << ')' << endl;
            table << ++loc << "\t(" << '=' << '\t' << 'T' << tn << '\t' << '\t' << A[0] << ')' << endl;
            break;
        case 4:
            tops = tops - 3;
            topc = topc - 2;
            opC[topc] = 'C';
            cout << '\t' << '\t' << " 归约  " << grammar[4].gen << endl;
            r = E[2];
            d1 = E[1];
            if (r == '=')
                d2 = E[4];
            else
                d2 = E[3];
            table << ++loc << "\t(" << r;
            if (r == '=')
                table << r << '\t' << d1 << '\t' << d2 << '\t' << loc + 2 << ')' << endl;
            else
                table << '\t' << d1 << '\t' << d2 << '\t' << loc + 2 << ')' << endl;
            if (en == 1)
                table << ++loc << "\t("
                      << "goto" << '\t' << '\t' << '\t' << loc + 4 << ')' << endl;
            else
                table << ++loc << "\t("
                      << "goto" << '\t' << '\t' << '\t' << loc + 4 + 2 * (en) << ')' << endl;
            break;
        case 5:
            tops = tops - 3;
            topc = topc - 2;
            opC[topc] = 'T';
            cout << '\t' << '\t' << " 归约  " << grammar[5].gen << endl;
            table << ++loc << "\t("
                  << "goto" << '\t' << '\t' << '\t' << loc + 3 << ')' << endl;
            break;
        case 101:
        case 102:
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
        case 109:
        case 110:
            if (tops == topc)
                p = p->next;
            opS[++tops] = mark - 100;
            if (tops > topc)
                opC[++topc] = c;
            cout << '\t' << '\t' << " 移入" << endl;
            break;
        case 0:
            cout << "ERROR!" << endl;
            return;
        }
    }
}

void showS(int opS[], int tops, char opC[], int topc, wnode *hp)
{
    int i = 0, j = 0;
    wnode *tp = hp;
    for (i = 0; i <= topc; i++)
        cout << opC[i];
    cout << '\t';
    while (tp)
    {
        cout << tp->id;
        tp = tp->next;
    }
    cout << endl;
    for (i = 0; i <= tops; i++)
        cout << opS[i];
}

int check(int s, char v)
{
    int t = -1;
    switch (v)
    {
    case 'i':
        t = 0;
        break;
    case 't':
        t = 1;
        break;
    case 'e':
        t = 2;
        break;
    case 'A':
        t = 3;
        break;
    case 'E':
        t = 4;
        break;
    case '#':
        t = 5;
        break;
    case 'S':
        t = 6;
        break;
    case 'C':
        t = 7;
        break;
    case 'T':
        t = 8;
        break;
    default:;
    }
    int r = LR[s][t];
    return r;
}

int main(void)
{
    FILE *fp;
    int n = 100;
    cout << "***IF-ELSE条件语句的翻译程序设计（LR方法、输出四元式）***" << endl;
    initGrammar();
    cout << "请输入文件名:";
    cin.getline(Filename, n);
    fp = fopen(Filename, "r");
    while (fp == NULL) //若打入的文件没有，则提示继续打入有效的路径名
    {
        cout << "Sorry,文件不存在!" << endl;
        cout << "请重新输入文件名:";
        cin.getline(Filename, n);
        fp = fopen(Filename, "r");
    }
    wnode *wlist;
    wlist = new wnode;
    wlist->id = '#';
    wlist->n = 0;
    wlist->text[0] = '\0';
    wlist->next = NULL;
    wlist = lexcial(wlist);
    fclose(fp);
    word();
    gammarAnalysis(wlist);
    ifstream fin("siyuanshi.txt");
    string s;
    cout << "输出四元式为：" << endl;
    while (getline(fin, s))
    {
        cout << s << endl;
    }
    return 0;
}
