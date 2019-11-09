#include<cstdio> 
#include<iostream>
#include<cstdlib>
#include<string> 
#include<string.h> 
#include<stack>
using namespace std;

int getRank(char sign)
{
	switch (sign)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	}
	return -1;
}

int main(void)
{
	int i = 0;
	stack<char> expStack;
	string expression;
	cin >> expression;

	for (i = 0; i < expression.length(); i++)
	{
		if (expression[i] >= '0' && expression[i] <= '9')
		{
			cout << expression[i];
		}
		else if (expression[i] == '(')
		{
			expStack.push(expression[i]);
		}
		else if (expression[i] == ')')
		{
			char top = expStack.top();
			expStack.pop();
			while (!expStack.empty() && top != '(')
			{
				cout << top;
				top = expStack.top();
				expStack.pop();
			}
		}
		else
		{
			int now = getRank(expression[i]);
			if (expStack.empty() || now > getRank(expStack.top()))
			{
				expStack.push(expression[i]);
			}
			else
			{
				while (!expStack.empty() && now <= getRank(expStack.top()))
				{
					cout << expStack.top();
					expStack.pop();
				}
				expStack.push(expression[i]);
			}
		}
	}

	while (!expStack.empty())
	{
		cout << expStack.top();
		expStack.pop();
	}
	return 0;
}
