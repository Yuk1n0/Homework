#include <iostream>
#include "QJS.h"
using namespace std;
void QJS(void)
{
	int n = 0, k;
	double v, x;
	double a[MAX_SIZE] = { 0 };
	cout << endl;
	cout << "=====秦九韶算法=====\n";
	cout << "请输入n的大小："; cin >> n;
	for (int i = 0; i <= n; i++)
	{
		cout << "a" << i << "：";
		cin >> a[i];
	}
	cout << "请输入x的值："; cin >> x;
	v = a[n];
	k = 1;
	v = (x*v) + a[n - k];
	while (k != n)
	{
        k = k + 1;
		v = (x*v) + a[n - k];
	}
	cout << "结果为：" << v << endl;
	cout << endl;
}