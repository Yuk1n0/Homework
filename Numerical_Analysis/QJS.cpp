#include <iostream>
#include "QJS.h"
using namespace std;
void QJS(void)
{
	int n = 0, k;
	double v, x;
	double a[MAX_SIZE] = { 0 };
	cout << endl;
	cout << "=====�ؾ����㷨=====\n";
	cout << "������n�Ĵ�С��"; cin >> n;
	for (int i = 0; i <= n; i++)
	{
		cout << "a" << i << "��";
		cin >> a[i];
	}
	cout << "������x��ֵ��"; cin >> x;
	v = a[n];
	k = 1;
	v = (x*v) + a[n - k];
	while (k != n)
	{
        k = k + 1;
		v = (x*v) + a[n - k];
	}
	cout << "���Ϊ��" << v << endl;
	cout << endl;
}