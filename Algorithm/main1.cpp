#include<stdio.h>
#include<stdlib.h>

const int MAX = 50;
int a[MAX];
int b[MAX];
int temp[MAX];

int main(void)
{
	int count1, count2;
	scanf("%d", &count1);
	while (count1--)
	{
		scanf("%d", &count2);
		for (int i = 1; i <= count2; i++)
		{
			scanf("%d", &a[i]);
		}
		temp[0] = a[1];
		for (int i = 1; i < count2; i++)
		{
			temp[i] = a[i + 1] - a[i];
		}
		for (int i = 1; i <= count2; i++)
		{
			int j;
			for (j = i - 1; j >= 0; j--)
			{
				if (temp[j] > 0)
				{
					temp[j]--;
					break;
				}
			}
			b[i] = i - j;
		}
		for (int i = 1; i < count2; i++)
			printf("%d ", b[i]);
		printf("%d\n", b[count2]);
	}
	system("pause");
	return 0;
}
/*
POJ 1068 Parencodings
��ģ��
������temp[i]��ʾ��i�������ź͵�i+1�������ż����������
Ȼ�����Һ�������ƥ���������������λ��
i-j
*/
