#include <iostream>
#include <cmath>
#include "LterativeMethod.h"
using namespace std;

double fi(double x)
{
    double r;
    //	r = pow((x + 1), 1.0 / 3.0);
    r = exp(-x);
    return r;
}

void LterativeMethod(void)
{
    cout << endl;
    cout << "=====������=====\n";
    double x0, e, x1, temp;
    int k, N;
    cout << "������x0��ֵ��"; cin >> x0;
    cout << "�����뾫��e��"; cin >> e;
    cout << "����������������N:"; 
    cin >> N;
    k = 1;
    
    x1 = fi(x0);
    temp = abs(x1 - x0);
    cout << "x1=" << x1 << endl;
    while (temp >= e)
    {
        k = k + 1;
        x0 = x1;
        
        x1 = fi(x0);
        temp = abs(x1 - x0);
        cout << "x1=" << x1 << endl;
        if (k == N)
        {
            cout << "����ʧ��" << endl;
            break;
        }
    }
    cout << endl;
}
