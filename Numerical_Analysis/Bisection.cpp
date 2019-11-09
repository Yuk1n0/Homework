#include <iostream>
#include <cmath>
#include "Bisection.h"
using namespace std;
double f(double z);

void Bisection(void)
{
	cout << endl;
	cout << "=======���ַ�=======" << endl;
	double a, b, e;
	double x, y, y0;
	bool judge = true;
	cout << "������a��ֵ��"; cin >> a;
	cout << "������b��ֵ��"; cin >> b;
	cout << "������e��ֵ��"; cin >> e;
	y0 = f(a);

	while (judge)
	{
		x = (a + b) / 2;
		y = f(x);

		if ((y*y0) > 0)
		{
			a = x;
		}
		else
		{
			b = x;
		}

		if ((b - a) < e)
		{
			judge = false;
		}
	}
	cout << "x��ֵΪ��" << x << endl;
	cout << "y��ֵΪ��" << y << endl;
	cout << endl;
}

double f(double z)
{
	double result;
	result = (z*z*z) - z - 1;
	return result;
}