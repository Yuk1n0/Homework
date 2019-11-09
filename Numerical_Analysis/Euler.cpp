#include <iostream>
#include "Euler.h"
using namespace std;
double f1(double a, double b);

void Euler(void)
{
    cout << endl;
    cout << "=====�Ľ�ŷ������=====\n";
    double x0, y0, h, x1, y1, yp, yc;
    int N, n;
    cout << "������x0��ֵ��"; cin >> x0;
    cout << "������y0��ֵ��"; cin >> y0;
    cout << "�����벽��h��"; cin >> h;
    cout << "�����벽��N��"; cin >> N;
    n = 1;
    
    x1 = x0 + h;
    yp = y0 + h*f1(x0, y0);
    yc = y0 + h*f1(x1, yp);
    y1 = (yp + yc) / 2;
    cout << "x1=" << x1 << "  " << "y1=" << y1 << endl;
    while (n != N)
    {
        n = n + 1;
        x0 = x1; y0 = y1;
        
        x1 = x0 + h;
        yp = y0 + h * f1(x0, y0);
        yc = y0 + h * f1(x1, yp);
        y1 = (yp + yc) / 2;
        cout << "x1=" << x1 << "  " << "y1=" << y1 << endl;
    }
    cout << endl;
}

double f1(double a, double b)
{
    double r;
    r = b - ((2 * a) / b);
    return r;
}
