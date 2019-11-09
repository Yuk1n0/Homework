#include"Lexical.h"
Lexical::Lexical() 
{
    CC = 0;
    LL = 0;
    ch = ' ';
    LexFileName = "sentence.txt";
    fin = fopen("sentence.txt", "r");
    init();
}

/*��ʼ��*/
void Lexical::init() 
{	
    //��ʼ�������еĸ�����
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

/*��ȡ�ļ���Ϣ*/
void Lexical::getFileInfo() 
{
    ifstream fin(LexFileName);
    char str[80];
    if (!fin)
    {
        cout << "�ļ��򿪴���" << endl;
    }
    else 
    {
        while (fin.getline(str, sizeof(str))) 
        {
            cout << '\t' << str << endl;
        }
    }
}

/*�ӻ������ж�ȡ�����ַ�*/
int Lexical::getch() 
{
    if (CC == LL) 
    {	//�ﵽ���������ȣ����¸��»�����
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
            line[LL] = ch;	//�ӻ�������ȡ���ַ�
            LL++;
        }
    }
    ch = line[CC];	//�ӻ�������ȡ���ַ�
    CC++;
    return 0;
}

/*���ִʷ������ӳ���*/
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
    if (k > 14)	//�������ַ���ʾ��Χת�������
    {
        
    }
    else 
    {
        in.push_back("n");
    }
}

/*��ʶ���ͱ����ֵĴʷ������ӳ���*/
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
        k = (i + j) / 2;	//���ֲ��ң���Ϊ�����ֵı����������
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

/*���ŵĴʷ������ӳ���*/
void Lexical::doSymbolPro(int& tag)
{
    cout << ch;
    if (ch == ':')
    {
        getch();
        if (ch == '=') 
        {
            in.push_back(":=");	//�Ѹ÷��Ŵ��������У����ڱ�ʶ�����ֵȣ����﷨�е���Ӧ�ս����ʶ���Ա�֮��ת�����ַ���ȡ�����ݸ��﷨����
            cout << ch;
            sym = becomes;	//��ʱ�����Ǹ�ֵ��
            cout << '\t' << sym << endl;
            getch();
        }
        else 
        {
            sym = nul;	//��ʱ������null
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
                in.push_back("=");	//�Ѹ÷��Ŵ��������У����ڱ�ʶ�����ֵȣ����﷨�е���Ӧ�ս����ʶ���Ա�֮��ת�����ַ���ȡ�����ݸ��﷨����
                cout << ch;
                sym = leq;
                cout << '\t' << sym << endl;	/*��ʱ������С�ڵ���*/
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
                in.push_back(">");	//�Ѹ÷��Ŵ��������У����ڱ�ʶ�����ֵȣ����﷨�е���Ӧ�ս����ʶ���Ա�֮��ת�����ַ���ȡ�����ݸ��﷨����
                getch();
                if (ch == '=')
                {
                    in.push_back("=");	//�Ѹ÷��Ŵ��������У����ڱ�ʶ�����ֵȣ����﷨�е���Ӧ�ս����ʶ���Ա�֮��ת�����ַ���ȡ�����ݸ��﷨����
                    cout << ch;
                    sym = geq;
                    cout << '\t' << sym << endl;	//��ʱ�����Ǵ��ڵ���
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
                in.push_back(a);	//�Ѹ÷��Ŵ��������У����ڱ�ʶ�����ֵȣ����﷨�е���Ӧ�ս����ʶ���Ա�֮��ת�����ַ���ȡ�����ݸ��﷨����
                sym = ssym[ch];
                cout << '\t' << sym << endl;
                if (sym != neq)     //����ȡ����Ϊ��#����������
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

/*�ʷ�����������*/
int Lexical::getsym()
{
    while (ch == ' ' || ch == 10 || ch == 0) 
    {	//��ʱ�ո񣬷ֺţ���\0'ʱ����������һ���ַ�
        getch();
    }
    if (ch >= 'a' && ch <= 'z') 
    {		//a-zת���ʶ���ͱ����ֵĴʷ������ӳ���
        doLetterPro();
    }
    else 
    {
        if (ch >= '0' && ch <= '9') 
        {		//0-9ת�����ַ����ӳ���
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

/*����������Ͷ��ձ�*/
void Lexical::printCompareTable(char** s) 
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
                cout << endl << '\t';
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

/*�ʷ�����*/
void Lexical::lexAnalysis(string& input)
{
    cout << '\t' << "����" << '\t' << "����" << endl;
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
        //��vector�����е�Ԫ����������ת���ַ���
        input.append(this->in[ix]);
    }
    this->in.clear();
}
