#include "Lexical.h"
#include <string>
#include <iostream>
#include "LR(1).h"
using namespace std;

int main(void)
{
	string input = "";
	char *st[] = {(char *)"不能识别的字符\t", (char *)"自定义标识符\t", (char *)"数字\t", (char *)"加号\t", (char *)"减号\t", (char *)"乘号\t", (char *)"除号\t", (char *)"左括号\t", (char *)"右括号\t", (char *)"等号\t", (char *)"逗号\t", (char *)"句号\t", (char *)"终结符\t", (char *)"分号\t", (char *)"保留字begin\t",
				  (char *)"保留字call\t", (char *)"保留字const\t", (char *)"保留字do\t", (char *)"保留字end\t", (char *)"保留字if\t", (char *)"保留字odd\t", (char *)"保留字proc\t", (char *)"保留字read\t", (char *)"保留字then\t", (char *)"保留字var\t", (char *)"保留字while\t",
				  (char *)"保留字write\t", (char *)"赋值号\t", (char *)"小于等于号\t", (char *)"小于号\t", (char *)"大于等于号\t", (char *)"大于号\t", (char *)""};
	Lexical lexical;
	cout << "单词类型对照表为:" << endl;
	lexical.printCompareTable(st);
	cout << "\n\n"
		 << "需分析的字符串为:" << endl;
	lexical.getFileInfo();
	cout << endl;
	cout << endl;
	cout << "词法分析:" << endl;
	lexical.lexAnalysis(input);

	ifstream fin("grammar.txt");
	char str[80];
	string s = "";
	Item grm;
	set<char> begin;
	begin.insert('#');
	if (!fin)
	{
		cout << "文件打开错误" << endl;
	}
	else
	{
		char start;
		int rank = 0;
		cout << "文法:" << endl;
		while (fin.getline(str, sizeof(str)))
		{
			//读取文件
			s = str;
			if (s == "#")
			{
				break;
			}
			if (rank == 0)
			{
				start = s[0];
			}
			char left = s[0];					 //得到产生式左部
			string right = s.substr(2);			 //得到产生式右部
			Program p(left, right, begin, rank); //构造文法
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
		cout << '\n'
			 << "LR(1)分析表:"
			 << "\n\n";
		lr.showTable();
		cout << '\n'
			 << "LR(1)分析过程:"
			 << "\n\n"
			 << "\t"
			 << "步骤"
			 << "\t\t"
			 << "状态栈"
			 << "\t\t\t"
			 << "符号栈"
			 << "\t\t"
			 << "输入流"
			 << "\t\t"
			 << "ACTION"
			 << "\t\t"
			 << "GOTO" << endl;
		lr.analyse();
	}
	return 0;
}
