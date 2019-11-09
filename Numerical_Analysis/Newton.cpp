#include <iostream>
#include <math.h>
using namespace std;

void Newton(void)
{
    cout << endl;
    cout << "=====�������ղ�ֵ��=====\n";
    int n, i, j;
    double A[50][50];
    double x[50], y[50];
    double K = 1, X = 0, N = 0, P;
    cout << "����������������:";
    cin >> n;
    for (i = 0; i <= n; i++)
    {
        cout << "������x" << i << "=";
        cin >> x[i];
        cout << "������y" << i << "=";
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
        cout << "�����" << i << "�׾���Ϊ��" << A[i][i + 1] << endl;
    }
    cout << "����Ҫ��������x��ֵ��x=";
    cin >> X;
    for (i = 0; i<n; i++)
    {
        K *= X - x[i];
        N += A[i + 1][i + 2] * K;
        P = A[0][1] + N;
    }
    cout << "��Ҫ��ĺ���ֵΪ��y=" << P << endl;
    cout << endl;
}
