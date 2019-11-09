#include <iostream>
#include <math.h>
using namespace std;

void Newton(void)
{
    cout << endl;
    cout << "=====拉格朗日插值法=====\n";
    int n, i, j;
    double A[50][50];
    double x[50], y[50];
    double K = 1, X = 0, N = 0, P;
    cout << "请输入所求均差阶数:";
    cin >> n;
    for (i = 0; i <= n; i++)
    {
        cout << "请输入x" << i << "=";
        cin >> x[i];
        cout << "请输入y" << i << "=";
        cin >> y[i];
        A[i][0] = x[i]; A[i][1] = y[i];
    }
    for (j = 2; j <= n + 1; j++)
    {
        for (i = 1; i <= n; i++)
        {
            A[i][j] = (A[i][j - 1] - A[i - 1][j - 1]) / (A[i][0] - A[i - j + 1][0]);
        }
    }
    for (i = 0; i <= n; i++)
    {
        cout << "输出第" << i << "阶均差为：" << A[i][i + 1] << endl;
    }
    cout << "请所要代入计算的x的值：x=";
    cin >> X;
    for (i = 0; i<n; i++)
    {
        K *= X - x[i];
        N += A[i + 1][i + 2] * K;
        P = A[0][1] + N;
    }
    cout << "所要求的函数值为：y=" << P << endl;
    cout << endl;
}
