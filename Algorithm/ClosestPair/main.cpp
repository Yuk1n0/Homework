#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
using namespace std;

#define eps 1e-8
#define N 10000

//定义一个保存坐标的结构体
struct point
{
    double x, y;
};
point node[N * 2];
point d[N];
point c[N];
point b[N];

int cmp(point a, point b) //比较两点之间的y值
{
    return a.y < b.y;
}

double min(double a, double b) //求a和b两者较小值
{
    return a > b ? b : a;
}

double dx(double x1, double x2)
{
    if ((x1 - x2) > eps && (x1 - x2) < eps)
    {
        return 0;
    }
    else if (x1 > x2)
    {
        return x1 - x2;
    }
    else if (x1 < x2)
    {
        return x2 - x1;
    }
}

double ds(point a, point b) //求两点之间的距离
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
/**
* 最近对问题
* 三种情况：
* 1.在子集S1中
* 2.在自己S2中
* 3.最近的两个点分别在子集S1和S2中
*/
double closestPoints(point node[], int n)
{
    int i, j;
    int Dist = 99999; //无穷大数
    if (n < 2)        //只有一个点，不存在最近对
        return 0;
    int m = (n - 1) / 2; //m是各个坐标的中位数
    for (i = m + 1; i < n; i++)
    {
        b[i].x = node[i].x;
        b[i].y = node[i].y;
    }
    //划分为两个子问题，递归求解子问题
    double d1 = closestPoints(node, m + 1);  //得到S1中的最近距离d1
    double d2 = closestPoints(b, n - m - 1); //得到S2中的最近距离d2
    double dm = min(d1, d2);                 //求得d1与d2两者之间较小值
    int f, p;                                //记录点的个数
    p = 0;
    for (i = 0; i <= m; i++) //找出S1中与x=m的距离小于dm的所有点，保存在结构体c当中
    {
        if (dx(node[i].x, node[m].x) < dm)
        {
            c[p].x = node[i].x;
            c[p].y = node[i].y;
            p++;
        }
    }
    f = 0;
    for (i = m + 1; i < n; i++) //找出S2中与x=m的距离小于dm的所有点，保存在结构题d当中
    {
        if (dx(node[i].x, node[m].x) < dm)
        {
            d[f].x = node[i].x;
            d[f].y = node[i].y;
            f++;
        }
    }
    sort(c, c + p, cmp); //按照y轴的坐标值升序排列
    sort(d, d + f, cmp);
    double ret = Dist;
    for (i = 0; i < p; i++) //遍历比较分别在S1和S2中两点之间的距离
    {
        for (j = 0; j < f; j++)
        {
            double ans = ds(c[i], d[j]);
            ret = min(ret, ans); //得出最近对距离
        }
    }
    return min(ret, dm); //返回第三种情形与前两种情形较小值
}

int main(void)
{
    int n, i;
    for (int w = 0; w < 6; w++)
    {
        cout << "输入坐标的数目：" << endl;
        cin >> n;
        srand((unsigned)time(NULL));
        for (i = 0; i < n; i++)
        {
            node[i].x = rand() / (double)(RAND_MAX / 10000);
            node[i].y = rand() / (double)(RAND_MAX / 10000);
        }
        sort(node, node + n, cmp);
        clock_t start, end;
        start = clock();
        closestPoints(node, n); //系统调用十次分治法函数。
        closestPoints(node, n);
        closestPoints(node, n);
        closestPoints(node, n);
        closestPoints(node, n);
        closestPoints(node, n);
        closestPoints(node, n);
        closestPoints(node, n);
        closestPoints(node, n);
        closestPoints(node, n);
        end = clock();
        cout << "分治法求最近对用时为" << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
        cout << "===========================================================" << endl;
    }
    return 0;
}
