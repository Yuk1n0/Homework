#include <iostream>
#include <cmath>
#include "Atiken.h"
using namespace std;

double Fi(double x)
{
    double r;
    r = exp(-x);
    return r;
}

void Atiken(void)
{
    cout << endl;
    cout << "=====埃特金加速方法=====\n";
    double x0, e, x1, x2, temp;
    int k, N;
    cout << "请输入x0的值："; cin >> x0;
    cout << "请输入精度e："; cin >> e;
    cout << "请输入最大迭代次数N:";
    cin >> N;
    k = 1;
    
    x1 = Fi(x0);
    x2 = Fi(x1);
    x2 = x2 - (((x2 - x1)*(x2 - x1)) / (x2 - (2 * x1) + x0));
    temp = abs(x2 - x0);
    cout << "x2=" << x2 << endl;
    while (temp >= e)
    {
        k = k + 1;
        x0 = x2;
        
        x1 = Fi(x0);
        x2 = Fi(x1);
        x2 = x2 - (((x2 - x1)*(x2 - x1)) / (x2 - (2 * x1) + x0));
        temp = abs(x2 - x0);
        cout << "x2=" << x2 << endl;
        if (k == N)
        {
            cout << "迭代失败" << endl;
            break;
        }
    }
    cout << endl;
}
