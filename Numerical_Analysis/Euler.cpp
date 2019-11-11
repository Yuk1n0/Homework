#include <iostream>
#include "Euler.h"
using namespace std;

double f1(double a, double b);

void Euler(void)
{
    cout << endl;
    cout << "=====改进欧拉方法=====\n";
    double x0, y0, h, x1, y1, yp, yc;
    int N, n;
    cout << "请输入x0的值：";
    cin >> x0;
    cout << "请输入y0的值：";
    cin >> y0;
    cout << "请输入步长h：";
    cin >> h;
    cout << "请输入步数N：";
    cin >> N;
    n = 1;

    x1 = x0 + h;
    yp = y0 + h * f1(x0, y0);
    yc = y0 + h * f1(x1, yp);
    y1 = (yp + yc) / 2;
    cout << "x1=" << x1 << "  "
         << "y1=" << y1 << endl;
    while (n != N)
    {
        n = n + 1;
        x0 = x1;
        y0 = y1;

        x1 = x0 + h;
        yp = y0 + h * f1(x0, y0);
        yc = y0 + h * f1(x1, yp);
        y1 = (yp + yc) / 2;
        cout << "x1=" << x1 << "  "
             << "y1=" << y1 << endl;
    }
    cout << endl;
}

double f1(double a, double b)
{
    double r;
    r = b - ((2 * a) / b);
    return r;
}
