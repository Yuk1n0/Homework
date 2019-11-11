#include <iostream>
#include <cmath>
#include "Bisection.h"
using namespace std;

double f(double z);

void Bisection(void)
{
    cout << endl;
    cout << "=======二分法=======" << endl;
    double a, b, e;
    double x, y, y0;
    bool judge = true;
    cout << "请输入a的值：";
    cin >> a;
    cout << "请输入b的值：";
    cin >> b;
    cout << "请输入e的值：";
    cin >> e;
    y0 = f(a);

    while (judge)
    {
        x = (a + b) / 2;
        y = f(x);

        if ((y * y0) > 0)
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
    cout << "x的值为：" << x << endl;
    cout << "y的值为：" << y << endl;
    cout << endl;
}

double f(double z)
{
    double result;
    result = (z * z * z) - z - 1;
    return result;
}
