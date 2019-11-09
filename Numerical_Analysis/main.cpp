#include <iostream>
#include "QJS.h"
#include "Lagrange.h"
#include "Newton.h"
#include "Euler.h"
#include "RungeKutta.h"
#include "Bisection.h"
#include "LterativeMethod.h"
#include "Atiken.h"
#include "Gauss.h"
using namespace std;
int main(void)
{
	int x = 1;
	cout << "=====请选择需要执行的操作=====\n";
	cout << "1.秦九韶算法\n";
	cout << "2.拉格朗日插值法\n";
	cout << "3.牛顿插值法\n";
	cout << "4.改进欧拉方法\n";
	cout << "5.龙格-库塔方法\n";
	cout << "6.二分法\n";
	cout << "7.迭代法\n";
	cout << "8.埃特金加速方法\n";
	cout << "9.高斯消去法\n";
	cout << "==============================\n";
	while (x)
	{
        cout << "请输入要执行的操作："; cin >> x;
		switch (x)
		{
		case 1:QJS(); break;
		case 2:Lagrange(); break;
		case 3:Newton(); break;
		case 4:Euler(); break;
		case 5:RungeKutta(); break;
		case 6:Bisection(); break;
		case 7:LterativeMethod(); break;
		case 8:Atiken(); break;
		case 9:Gauss(); break;
		case 0:cout << "退出系统！" << endl; break;
		default:cout << "输入错误请重新输入\n";
		}
	}
	system("pause");
	return 0;
}
