#include "stdio.h"
#include "stdlib.h"
#define StuNum1 4 //�궨��ѧ������1
#define StuNum2 4 //�궨��ѧ������2

typedef struct student
{
	int xuehao;
	int score;
	struct student* next;
}Student, * Pstudent;

void CreatLink(Pstudent head, int size)
{
	Pstudent phead = head, pstu;
	for (int i = 0; i < size; i++)
	{
		pstu = (Pstudent)malloc(sizeof(student));
		pstu->score = head[i].score;
		pstu->xuehao = head[i].xuehao;
		pstu->next = NULL;
		phead->next = pstu;
		phead = pstu;
	}
}
//���ɼ���С���� ֻ�ǽ�ԭʼ�����������������
void Sort(Pstudent pstu, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (pstu[j].score < pstu[j + 1].score)
			{
				int score = pstu[j].score;
				int xh = pstu[j].xuehao;
				pstu[j].score = pstu[j + 1].score;
				pstu[j].xuehao = pstu[j + 1].xuehao;
				pstu[j + 1].score = score;
				pstu[j + 1].xuehao = xh;
			}
		}
	}
}
void print(Pstudent head)
{
	head = head->next;
	while (head)
	{
		printf("ѧ�ţ�%d�� �ɼ���%d\n", head->xuehao, head->score);
		head = head->next;
	}
	return;
}
//�ϲ����������������ʵ��
Pstudent Combination(Pstudent head1, Pstudent head2)
{
	Pstudent pCom = (Pstudent)malloc(sizeof(student));
	Pstudent temp = pCom, p1 = head1->next, p2 = head2->next;
	while (p1 != NULL || p2 != NULL)
	{
		if (p1->score > p2->score)
		{
			pCom->next = p1;
			pCom = p1;
			if (p1->next == NULL)
			{
				break;
			}
			p1 = p1->next;
		}
		else
		{
			pCom->next = p2;
			pCom = p2;
			if (p2->next == NULL)
			{
				break;
			}
			p2 = p2->next;
		}
	}
	if (p1->next == NULL)
	{
		pCom->next = p2;
	}
	else
	{
		pCom->next = p1;
	}
	return temp;
}

int main(void)
{
	Student stu1[StuNum1], stu2[StuNum2];
	printf("�������һ��ѧ����Ϣ��");
	for (int i = 0; i < StuNum1; i++)
	{
		printf("��1. %d ��ͬѧ��ѧ��,�ɼ�Ϊ ��", i + 1);
		scanf("%d", &stu1[i].xuehao);
		scanf("%d", &stu1[i].score);
		stu1[i].next = NULL;
	}
	printf("������ڶ���ѧ����Ϣ��");
	for (int i = 0; i < StuNum2; i++)
	{
		printf("��2. %d ��ͬѧ��ѧ��,�ɼ�Ϊ ��", i + 1);
		scanf("%d", &stu2[i].xuehao);
		scanf("%d", &stu2[i].score);
		stu2[i].next = NULL;
	}
	Sort(stu1, StuNum1);
	Sort(stu2, StuNum2);
	CreatLink(stu1, StuNum1);
	CreatLink(stu2, StuNum2);
	Pstudent ps = Combination(stu1, stu2);
	printf("�ϲ���ĵ������\n");
	print(ps);
	return 0;
}
