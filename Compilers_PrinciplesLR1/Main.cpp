#include"Lexical.h"
#include<string>
#include<iostream>
#include"LR(1).h"
using namespace std;

int main(void)
{
	string input = "";
	char* st[] = { (char*)"����ʶ����ַ�\t", (char*)"�Զ����ʶ��\t", (char*)"����\t", (char*)"�Ӻ�\t", (char*)"����\t", (char*)"�˺�\t", (char*)"����\t",(char*)"������\t", (char*)"������\t", (char*)"�Ⱥ�\t", (char*)"����\t",(char*) "���\t",(char*) "�ս��\t", (char*)"�ֺ�\t", (char*)"������begin\t",
	(char*)"������call\t", (char*)"������const\t",(char*) "������do\t", (char*)"������end\t",(char*)"������if\t", (char*)"������odd\t", (char*)"������proc\t", (char*)"������read\t", (char*) "������then\t",(char*) "������var\t",(char*) "������while\t",
	(char*)"������write\t", (char*)"��ֵ��\t",(char*) "С�ڵ��ں�\t", (char*)"С�ں�\t",(char*) "���ڵ��ں�\t", (char*)"���ں�\t", (char*)"" };
	Lexical lexical;
	cout << "�������Ͷ��ձ�Ϊ:" << endl;
	lexical.printCompareTable(st);
	cout << "\n\n" << "��������ַ���Ϊ:" << endl;
	lexical.getFileInfo();
	cout << endl; cout << endl;
	cout << "�ʷ�����:" << endl;
	lexical.lexAnalysis(input);

	ifstream fin("grammar.txt");
	char str[80];
	string s = "";
	Item grm;
	set<char> begin;
	begin.insert('#');
	if (!fin)
	{
		cout << "�ļ��򿪴���" << endl;
	}
	else
	{
		char start;
		int rank = 0;
		cout << "�ķ�:" << endl;
		while (fin.getline(str, sizeof(str))) 
        {	
            //��ȡ�ļ�
			s = str;
			if (s == "#") 
            {
				break;
			}
			if (rank == 0) 
            {
				start = s[0];
			}
			char left = s[0];	//�õ�����ʽ��
			string right = s.substr(2);	//�õ�����ʽ�Ҳ�
			Program p(left, right, begin, rank);	//�����ķ�
			grm.addPro(p, grm);
			rank++;
			cout << '\t' << " " << str << endl;
		}
		grm.insertVN(grm);
		grm.insertVT(grm, grm);
		grm.insertV(grm);
		LR lr(start, grm, input);
		lr.go();
		lr.getAction();
		lr.getGoto();
		cout << '\n' << "LR(1)������:" << "\n\n";
		lr.showTable();
		cout << '\n' << "LR(1)��������:" << "\n\n" << "\t" << "����" << "\t\t" << "״̬ջ" << "\t\t\t" << "����ջ" << "\t\t" << "������" << "\t\t" << "ACTION" << "\t\t" << "GOTO" << endl;
		lr.analyse();
	}
	system("pause");
	return 0;
}
