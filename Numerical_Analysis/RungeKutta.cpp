#include <iostream>
#include "RungeKutta.h"
using namespace std;
double f2(double a, double b);

void RungeKutta(void)
{
    cout << endl;
    cout << "=====����-��������=====\n";
    double x0, y0, h, K1, K2, K3, K4, x1, y1;
    int n, N;
    cout << "������x0��ֵ��"; cin >> x0;
    cout << "������y0��ֵ��"; cin >> y0;
    cout << "�����벽��h��"; cin >> h;
    cout << "�����벽��N��"; cin >> N;
    n = 1;
    
    x1 = x0 + h;
    K1 = f2(x0, y0);
    K2 = f2((x0 + (h / 2)), (y0 + ((h*K1) / 2)));
    K3 = f2((x0 + (h / 2)), (y0 + ((h*K2) / 2)));
    K4 = f2(x1, (y0 + (h * K3)));
    y1 = y0 + ((h*(K1 + 2 * K2 + 2 * K3 + K4)) / 6);
    cout << "x1=" << x1 << "  " << "y1=" << y1 << endl;
    
    while (n != N)
    {
        n = n + 1;
        x0 = x1; y0 = y1;
        
        x1 = x0 + h;
        K1 = f2(x0, y0);
        K2 = f2((x0 + (h / 2)), (y0 + ((h*K1) / 2)));
        K3 = f2((x0 + (h / 2)), (y0 + ((h*K2) / 2)));
        K4 = f2(x1, (y0 + (h * K3)));
        y1 = y0 + ((h*(K1 + 2 * K2 + 2 * K3 + K4)) / 6);
        cout << "x1=" << x1 << "  " << "y1=" << y1 << endl;
    }
    cout << endl;
}

double f2(double a, double b)
{
    double r;
    r = b - ((2 * a) / b);
    return r;
}
