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
	cout << "=====��ѡ����Ҫִ�еĲ���=====\n";
	cout << "1.�ؾ����㷨\n";
	cout << "2.�������ղ�ֵ��\n";
	cout << "3.ţ�ٲ�ֵ��\n";
	cout << "4.�Ľ�ŷ������\n";
	cout << "5.����-��������\n";
	cout << "6.���ַ�\n";
	cout << "7.������\n";
	cout << "8.���ؽ���ٷ���\n";
	cout << "9.��˹��ȥ��\n";
	cout << "==============================\n";
	while (x)
	{
        cout << "������Ҫִ�еĲ�����"; cin >> x;
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
		case 0:cout << "�˳�ϵͳ��" << endl; break;
		default:cout << "�����������������\n";
		}
	}
	system("pause");
	return 0;
}
