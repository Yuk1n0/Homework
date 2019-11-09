#include <iostream>
#include "Lagrange.h"
using namespace std;
void Lagrange(void)
{
	cout << endl;
	cout << "=====�������ղ�ֵ��=====\n";
	double x, y, t;
	double a[MAX_SIZE] = { 0 }, b[MAX_SIZE] = { 0 };
	int k, n;
	y = 0; k = 0; 
	cout << "������x��ֵ��"; cin >> x;
	cout << "������n��ֵ��"; cin >> n;
	for (int i = 0; i <= n; i++)
	{
		cout << "������x" << i << "��ֵ��"; cin >> a[i];
		cout << "������y" << i << "��ֵ��"; cin >> b[i];
	}

	t = 1;
	for (int j=0; j<= n; j++)
	{
		if (j == k)
			continue;
		t = t * ((x - a[j]) / (a[k] - a[j]));
	}
	y = y + (t*b[k]);
	while (k != n)
	{
		k = k + 1;

		t = 1;
		for (int j=0; j <= n; j++)
		{
			if (j == k)
				continue;
			t = t * ((x - a[j]) / (a[k] - a[j]));
		}
		y = y + (t*b[k]);
	}
	cout << "���Ϊ��" << y << endl;
	cout << endl;
}