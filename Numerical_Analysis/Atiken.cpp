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
    cout << "=====���ؽ���ٷ���=====\n";
    double x0, e, x1, x2, temp;
    int k, N;
    cout << "������x0��ֵ��"; cin >> x0;
    cout << "�����뾫��e��"; cin >> e;
    cout << "����������������N:";
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
            cout << "����ʧ��" << endl;
            break;
        }
    }
    cout << endl;
}
