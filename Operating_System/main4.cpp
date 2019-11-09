#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

struct first_fit
{ /*����������Ϣ*/
	int begin;
	int size;
	int No;
	struct first_fit* next;
	first_fit() /*Ĭ�Ϲ��캯��*/
	{
		begin = 0;
		size = 0;
		No = 0;
		next = NULL;
	}
	void set_data(int size, int begin = 0, int No = 0) /*���÷�����Ϣ*/
	{
		this->size = size;
		this->begin = begin;
		this->No = No;
		return;
	}
};

void init(struct first_fit* head, int size) /*��ʼ�����з���*/
{
	struct first_fit* temp = new first_fit();
	temp->set_data(size);
	head->next = temp;
	return;
}

void Print1(struct first_fit* t)
{ /*���һ��������Ϣ*/
	printf("���̺�=%d ,��ʼ��ַ=%d ,��ֹ��ַ=%d ,���С=%d \n", t->No, t->begin, t->begin + t->size, t->size);
	return;
}

void PrintAll(struct first_fit* head) /*������з�����Ϣ*/
{
	for (struct first_fit* t = head->next; t; t = t->next)
	{
		Print1(t);
	}
	printf("\n");
}

void best_fit(struct first_fit* create)//�����Ӧ�㷨
{
	if ((create->next == NULL) || (create->next->next == NULL))
	{
		return;
	}

	struct first_fit* head, * pre, * cur, * next, * end, * temp;
	head = create;
	end = NULL;

	while (head->next != end)
	{
		for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
		{
			//���ڵĽڵ�Ƚ�
			if (cur->size < next->size)
			{
				cur->next = next->next;
				pre->next = next;
				next->next = cur;
				temp = next;
				next = cur;
				cur = temp;
			}
		}
		end = cur;
	}
}

void worst_fit(struct first_fit* create)//���Ӧ�㷨
{
	if ((create->next == NULL) || (create->next->next == NULL))
	{
		return;
	}

	struct first_fit* head, * pre, * cur, * next, * end, * temp;
	head = create;
	end = NULL;

	while (head->next != end)
	{
		for (pre = head, cur = pre->next, next = cur->next; next != end; pre = pre->next, cur = cur->next, next = next->next)
		{
			//���ڵĽڵ�Ƚ�
			if (cur->size > next->size)
			{
				cur->next = next->next;
				pre->next = next;
				next->next = cur;
				temp = next;
				next = cur;
				cur = temp;
			}
		}
		end = cur;
	}
}

/*�����������ҵ*/
void memory_malloc(struct first_fit* create, struct first_fit* free)
{
	printf("��ѡ����з����㷨 1.������Ӧ�㷨 2.�����Ӧ�㷨 3.���Ӧ�㷨\n");
	int choice;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:break;
	case 2: best_fit(create); break;
	case 3: worst_fit(create); break;
	default:break;
	}

	int No, size;
	printf("��������̺ż���������ڴ��С\n");
	scanf("%d%d", &No, &size);

	struct first_fit* t = NULL;
	for (t = create; t->next; t = t->next)
	{ /*�����ܹ�������ҵҪ��Ŀ��з���*/
		if (t->next->size >= size)
		{ /*�ܹ�����Ҫ��*/
			struct first_fit* temp = new  first_fit();
			temp->begin = t->next->begin;
			temp->size = size;
			temp->No = No;
			temp->next = free->next;
			free->next = temp; /*�ѷ���ķ������뵽�ѷ����������*/
			if (!(t->next->size - size))
			{ /*��������*/
				struct first_fit* p = t->next;
				t->next = t->next->next;
				delete p;
				return;
			}
			else
			{ /*��������*/
				t->next->set_data(t->next->size - size, t->next->begin + size);
				return;
			}
		}
	}
	if (t->next == NULL)
	{ /*û���ܹ�����������򷵻�*/
		printf("�ڴ����ʧ��\n");
		return;
	}
	return;
}

/*���շ���*/
void  memory_free(struct first_fit* create, struct first_fit* free)
{
	int No;
	printf("������Ҫ�����Ľ��̺ţ�");
	scanf("%d", &No);

	struct first_fit* p1 = NULL;
	struct first_fit* p2 = NULL;

	for (p1 = free; p1->next; p1 = p1->next) /*�����ѷ���ķ���*/
		if (p1->next->No == No)
		{
			p2 = p1->next;
			p1->next = p1->next->next;
			break;
		}
	if (!p2)
	{ /*���Ҳ����򷵻�*/
		printf("�ý���û�б�����\n");
		return;
	}

	for (struct first_fit* q1 = create->next; q1; q1 = q1->next)
	{ /*�������з���*/
		if (p2->begin + p2->size == q1->begin)
		{ /*�ѷ����������з����������ڿ��з������Ϸ�*/
			printf("\n���кϲ��ɹ���\n");
			q1->set_data(q1->size + p2->size, p2->begin, q1->No);
			delete p2;
			return;
		}
		else if (q1->begin + q1->size == p2->begin)
		{ /*�ѷ����������з����������ڿ��з������·�*/
			printf("\n���кϲ��ɹ���\n");
			q1->set_data(q1->size + p2->size, q1->begin, q1->No);
			delete p2;
			return;
		}
		else if (q1->begin + q1->size == p2->begin && p2->begin + p2->size == q1->next->begin)
		{/*�ѷ����������з����������ڿ��з������м�*/
			q1->set_data(q1->size + q1->next->size + p2->size, q1->begin, q1->No);
			struct first_fit* q2 = q1->next;
			q1->next = q1->next->next;
			delete q2;
			return;
		}
	}
	p2->set_data(p2->size, p2->begin); /*���ÿ��з���״̬Ϊδ����*/

	struct first_fit* q = NULL;
	for (q = create; q->next; q = q->next) /*���ѷ������뵽��һ��������ʼ��ַ���δ�������ǰ*/
		if (q->next->begin > p2->begin)
		{
			p2->next = q->next;
			q->next = p2;
			return;
		}
	p2->next = NULL;
	q->next = p2; /*���ѷ���������뵽δ�������ǰ*/
	return;
}

int menu()
{
	printf("1.����һ������\n");
	printf("2.����һ������\n");
	printf("0.�˳�����\n");
	printf("����������: ");
	int m;
	scanf("%d", &m);
	switch (m)
	{
	case 0:
	case 1:
	case 2:
		return m; break;
	default:
		return 0;
	}
	return m;
}

int main(void)
{
	struct first_fit* create = new first_fit(); /*���з�������*/
	struct first_fit* free = new first_fit(); /*�ѷ����������*/
	int size;
	int temp;
	printf("�������ڴ��С:");
	scanf("%d", &size);
	init(create, size); /*��ʼ�����з���*/
	printf("�ڴ�ʹ������������̺���Ϊ0�Ŀ��ʾ�����ڴ棩\n");
	PrintAll(create); /*������з�����Ϣ*/

	while ((temp = menu()))
	{
		switch (temp)
		{
		case 1: memory_malloc(create, free); break; /*������з���*/
		case 2: memory_free(create, free); break; /*���տ��з���*/
		case 0: printf("�������\n"); break;
		}
		printf("\n������ռ����\n");
		PrintAll(free);
		printf("���з���\n");
		PrintAll(create);
	}
	return 0;
}
