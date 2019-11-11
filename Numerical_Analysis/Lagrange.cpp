#include <iostream>
#include "Lagrange.h"
using namespace std;

void Lagrange(void)
{
    cout << endl;
    cout << "=====拉格朗日插值法=====\n";
    double x, y, t;
    double a[MAX_SIZE] = {0}, b[MAX_SIZE] = {0};
    int k, n;
    y = 0;
    k = 0;
    cout << "请输入x的值：";
    cin >> x;
    cout << "请输入n的值：";
    cin >> n;
    for (int i = 0; i <= n; i++)
    {
        cout << "请输入x" << i << "的值：";
        cin >> a[i];
        cout << "请输入y" << i << "的值：";
        cin >> b[i];
    }

    t = 1;
    for (int j = 0; j <= n; j++)
    {
        if (j == k)
            continue;
        t = t * ((x - a[j]) / (a[k] - a[j]));
    }
    y = y + (t * b[k]);
    while (k != n)
    {
        k = k + 1;

        t = 1;
        for (int j = 0; j <= n; j++)
        {
            if (j == k)
                continue;
            t = t * ((x - a[j]) / (a[k] - a[j]));
        }
        y = y + (t * b[k]);
    }
    cout << "结果为：" << y << endl;
    cout << endl;
}
