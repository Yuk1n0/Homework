#include <iostream>
#include "Gauss.h"
using namespace std;
void Gauss(void)
{
	cout << endl;
	cout << "=====高斯消去法=====" << endl;	cout << "请输入n元方程中n的值：";	int n;	cin >> n;	double **a = new double*[n];	for (int i = 0; i != n; i++)	{		a[i] = new double[n];	}	double *b = new double[n];	cout << "请输入各项的系数：" << endl;	for (int i = 0; i != n; i++)	{		for (int j = 0; j != n; j++)		{			cout << "a[" << i + 1 << "]" << "[" << j + 1 << "]:";			cin >> a[i][j];		}	}	for (int i = 0; i != n; i++)	{		cout << "b[" << i + 1 << "]：";		cin >> b[i];	}	for (int i = 0; i != n; i++)	{		for (int j = i + 1; j != n; j++)		{			a[i][j] = a[i][j] / a[i][i];		}		b[i] = b[i] / a[i][i];		for (int s = i + 1; s != n; s++)		{			for (int l = i + 1; l != n; l++)			{				a[s][l] = a[s][l] - a[s][i] * a[i][l];			}			b[s] = b[s] - a[s][i] * b[i];		}	}	double t = 0;;	for (int i = n - 1; i > 0; i--)	{		for (int j = i + 1; j < n; j++)		{			t = t + a[i][j] * b[j];		}		b[i] = b[i] - t;	}	for (int i = 0; i < n; i++)	{		cout << "方程的解x" << i + 1 << "=" << b[i];	}
	cout << endl;
}