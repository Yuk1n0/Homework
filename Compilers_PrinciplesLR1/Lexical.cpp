#include "Lexical.h"

Lexical::Lexical()
{
    CC = 0;
    LL = 0;
    ch = ' ';
    LexFileName = "sentence.txt";
    fin = fopen("sentence.txt", "r");
    init();
}

/*初始化*/
void Lexical::init()
{
    //初始化属性中的各数组
    for (int i = 0; i <= 255; i++)
    {
        ssym[i] = nul;
    }
    ssym['+'] = plu;
    ssym['-'] = sub;
    ssym['*'] = times;
    ssym['/'] = slash;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['='] = eql;
    ssym[','] = comma;
    ssym['.'] = period;
    ssym['#'] = neq;
    ssym[';'] = semicolon;

    strcpy(&(word[0][0]), "begin");
    strcpy(&(word[1][0]), "call");
    strcpy(&(word[2][0]), "const");
    strcpy(&(word[3][0]), "do");
    strcpy(&(word[4][0]), "end");
    strcpy(&(word[5][0]), "if");
    strcpy(&(word[6][0]), "odd");
    strcpy(&(word[7][0]), "procedure");
    strcpy(&(word[8][0]), "read");
    strcpy(&(word[9][0]), "then");
    strcpy(&(word[10][0]), "var");
    strcpy(&(word[11][0]), "while");
    strcpy(&(word[12][0]), "write");

    wsym[0] = beginsym;
    wsym[1] = callsym;
    wsym[2] = constsym;
    wsym[3] = dosym;
    wsym[4] = endsym;
    wsym[5] = ifsym;
    wsym[6] = oddsym;
    wsym[7] = procsym;
    wsym[8] = readsym;
    wsym[9] = thensym;
    wsym[10] = varsym;
    wsym[11] = whilesym;
    wsym[12] = writesym;
}

/*读取文件信息*/
void Lexical::getFileInfo()
{
    ifstream fin(LexFileName);
    char str[80];
    if (!fin)
    {
        cout << "文件打开错误" << endl;
    }
    else
    {
        while (fin.getline(str, sizeof(str)))
        {
            cout << '\t' << str << endl;
        }
    }
}

/*从缓冲区中读取单个字符*/
int Lexical::getch()
{
    if (CC == LL)
    { //达到缓冲区长度，重新更新缓冲区
        if (feof(fin))
        {
            cout << "program incomlete";
            return -1;
        }
        LL = 0;
        CC = 0;
        ch = ' ';
        while (ch != 10)
        {
            if (EOF == fscanf(fin, "%c", &ch))
            {
                line[LL] = 0;
                break;
            }
            line[LL] = ch; //从缓冲区中取出字符
            LL++;
        }
    }
    ch = line[CC]; //从缓冲区中取出字符
    CC++;
    return 0;
}

/*数字词法分析子程序*/
void Lexical::doNumberPro()
{
    int k = 0;
    num = 0;
    sym = number;
    do
    {
        num = 10 * num + ch - '0';
        k++;
        getch();
    } while (ch >= '0' && ch <= '9');
    cout << num;
    cout << '\t' << sym << endl;
    k--;
    if (k > 14) //超过数字发表示范围转入错误处理
    {
    }
    else
    {
        in.push_back("n");
    }
}

/*标识符和保留字的词法分析子程序*/
void Lexical::doLetterPro()
{
    int i, j, t, k = 0;
    do
    {
        if (k < 10)
        {
            a[k] = ch;
            k++;
        }
        cout << ch;
        getch();
    } while (ch >= 'a' && ch <= 'z' || ch >= '0' && ch <= '9');
    a[k] = 0;
    t = k;
    strcpy(id, a);
    i = 0;
    j = 13 - 1;
    do
    {
        k = (i + j) / 2; //二分查找，因为保留字的保存是有序的
        if (strcmp(id, word[k]) <= 0)
        {
            j = k - 1;
        }
        if (strcmp(id, word[k]) >= 0)
        {
            i = k + 1;
        }
    } while (i <= j);
    if (i - 1 > j)
    {
        sym = wsym[k];
        for (int m = 0; m < t; m++)
        {
            in.push_back(id);
        }
        cout << '\t' << sym << endl;
    }
    else
    {
        sym = ident;
        cout << '\t' << sym << endl;
        in.push_back("i");
    }
}

/*符号的词法分析子程序*/
void Lexical::doSymbolPro(int &tag)
{
    cout << ch;
    if (ch == ':')
    {
        getch();
        if (ch == '=')
        {
            in.push_back(":="); //把该符号存入数组中（对于标识符数字等，用语法中的相应终结符标识，以便之后转化成字符串取出传递给语法分析
            cout << ch;
            sym = becomes; //此时类型是赋值符
            cout << '\t' << sym << endl;
            getch();
        }
        else
        {
            sym = nul; //此时类型是null
            cout << '\t' << sym << endl;
        }
    }
    else
    {
        if (ch == '<')
        {
            in.push_back("<");
            getch();
            if (ch == '=')
            {
                in.push_back("="); //把该符号存入数组中（对于标识符数字等，用语法中的相应终结符标识，以便之后转化成字符串取出传递给语法分析
                cout << ch;
                sym = leq;
                cout << '\t' << sym << endl; /*此时类型是小于等于*/
                getch();
            }
            else
            {
                sym = lss;
                cout << '\t' << sym << endl;
            }
        }
        else
        {
            if (ch == '>')
            {
                in.push_back(">"); //把该符号存入数组中（对于标识符数字等，用语法中的相应终结符标识，以便之后转化成字符串取出传递给语法分析
                getch();
                if (ch == '=')
                {
                    in.push_back("="); //把该符号存入数组中（对于标识符数字等，用语法中的相应终结符标识，以便之后转化成字符串取出传递给语法分析
                    cout << ch;
                    sym = geq;
                    cout << '\t' << sym << endl; //此时类型是大于等于
                    getch();
                }
                else
                {
                    sym = gtr;
                    cout << '\t' << sym << endl;
                }
            }
            else
            {
                char a[2];
                a[0] = ch;
                a[1] = 0;
                in.push_back(a); //把该符号存入数组中（对于标识符数字等，用语法中的相应终结符标识，以便之后转化成字符串取出传递给语法分析
                sym = ssym[ch];
                cout << '\t' << sym << endl;
                if (sym != neq) //当读取符号为“#”结束程序
                {
                    getch();
                }
                else
                {
                    tag = -1;
                }
            }
        }
    }
}

/*词法分析主程序*/
int Lexical::getsym()
{
    while (ch == ' ' || ch == 10 || ch == 0)
    { //当时空格，分号，‘\0'时跳过，读下一个字符
        getch();
    }
    if (ch >= 'a' && ch <= 'z')
    { //a-z转入标识符和保留字的词法分析子程序
        doLetterPro();
    }
    else
    {
        if (ch >= '0' && ch <= '9')
        { //0-9转入数字分析子程序
            doNumberPro();
        }
        else
        {
            int tag = 0;
            doSymbolPro(tag);
            return tag;
        }
    }
    return 0;
}

/*输出单词类型对照表*/
void Lexical::printCompareTable(char **s)
{
    int i = 0;
    while (1)
    {
        if (i % 5 == 0)
        {
            if (i == 0)
            {
                cout << '\t';
            }
            else
            {
                cout << endl
                     << '\t';
            }
        }
        if (s[i] != "")
        {
            cout << setw(5) << i << "-" << s[i];
        }
        else
        {
            break;
        }
        i++;
    }
}

/*词法分析*/
void Lexical::lexAnalysis(string &input)
{
    cout << '\t' << "单词" << '\t' << "类型" << endl;
    while (1)
    {
        cout << '\t';
        if (getsym() == -1)
        {
            break;
        }
    }
    input = "";
    for (vector<char>::size_type ix = 0; ix < in.size(); ix++)
    {
        //把vector数组中的元素连接起来转成字符串
        input.append(this->in[ix]);
    }
    this->in.clear();
}
