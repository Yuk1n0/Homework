#include <iostream>
#include "RungeKutta.h"
using namespace std;

double f2(double a, double b);

void RungeKutta(void)
{
    cout << endl;
    cout << "=====龙格-库塔方法=====\n";
    double x0, y0, h, K1, K2, K3, K4, x1, y1;
    int n, N;
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
    K1 = f2(x0, y0);
    K2 = f2((x0 + (h / 2)), (y0 + ((h * K1) / 2)));
    K3 = f2((x0 + (h / 2)), (y0 + ((h * K2) / 2)));
    K4 = f2(x1, (y0 + (h * K3)));
    y1 = y0 + ((h * (K1 + 2 * K2 + 2 * K3 + K4)) / 6);
    cout << "x1=" << x1 << "  "
         << "y1=" << y1 << endl;

    while (n != N)
    {
        n = n + 1;
        x0 = x1;
        y0 = y1;

        x1 = x0 + h;
        K1 = f2(x0, y0);
        K2 = f2((x0 + (h / 2)), (y0 + ((h * K1) / 2)));
        K3 = f2((x0 + (h / 2)), (y0 + ((h * K2) / 2)));
        K4 = f2(x1, (y0 + (h * K3)));
        y1 = y0 + ((h * (K1 + 2 * K2 + 2 * K3 + K4)) / 6);
        cout << "x1=" << x1 << "  "
             << "y1=" << y1 << endl;
    }
    cout << endl;
}

double f2(double a, double b)
{
    double r;
    r = b - ((2 * a) / b);
    return r;
}
