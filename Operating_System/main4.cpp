#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

struct first_fit
{ /*描述分区信息*/
	int begin;
	int size;
	int No;
	struct first_fit* next;
	first_fit() /*默认构造函数*/
	{
		begin = 0;
		size = 0;
		No = 0;
		next = NULL;
	}
	void set_data(int size, int begin = 0, int No = 0) /*设置分区信息*/
	{
		this->size = size;
		this->begin = begin;
		this->No = No;
		return;
	}
};

void init(struct first_fit* head, int size) /*初始化空闲分区*/
{
	struct first_fit* temp = new first_fit();
	temp->set_data(size);
	head->next = temp;
	return;
}

void Print1(struct first_fit* t)
{ /*输出一个分区信息*/
	printf("进程号=%d ,起始地址=%d ,终止地址=%d ,块大小=%d \n", t->No, t->begin, t->begin + t->size, t->size);
	return;
}

void PrintAll(struct first_fit* head) /*输出所有分区信息*/
{
	for (struct first_fit* t = head->next; t; t = t->next)
	{
		Print1(t);
	}
	printf("\n");
}

void best_fit(struct first_fit* create)//最佳适应算法
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
			//相邻的节点比较
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

void worst_fit(struct first_fit* create)//最坏适应算法
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
			//相邻的节点比较
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

/*分配分区给作业*/
void memory_malloc(struct first_fit* create, struct first_fit* free)
{
	printf("请选择空闲分配算法 1.最先适应算法 2.最佳适应算法 3.最坏适应算法\n");
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
	printf("请输入进程号及其所需的内存大小\n");
	scanf("%d%d", &No, &size);

	struct first_fit* t = NULL;
	for (t = create; t->next; t = t->next)
	{ /*查找能够满足作业要求的空闲分区*/
		if (t->next->size >= size)
		{ /*能够满足要求*/
			struct first_fit* temp = new  first_fit();
			temp->begin = t->next->begin;
			temp->size = size;
			temp->No = No;
			temp->next = free->next;
			free->next = temp; /*已分配的分区加入到已分配分区链表*/
			if (!(t->next->size - size))
			{ /*正好满足*/
				struct first_fit* p = t->next;
				t->next = t->next->next;
				delete p;
				return;
			}
			else
			{ /*大于需求*/
				t->next->set_data(t->next->size - size, t->next->begin + size);
				return;
			}
		}
	}
	if (t->next == NULL)
	{ /*没有能够满足需求的则返回*/
		printf("内存分配失败\n");
		return;
	}
	return;
}

/*回收分区*/
void  memory_free(struct first_fit* create, struct first_fit* free)
{
	int No;
	printf("请输入要结束的进程号：");
	scanf("%d", &No);

	struct first_fit* p1 = NULL;
	struct first_fit* p2 = NULL;

	for (p1 = free; p1->next; p1 = p1->next) /*遍历已分配的分区*/
		if (p1->next->No == No)
		{
			p2 = p1->next;
			p1->next = p1->next->next;
			break;
		}
	if (!p2)
	{ /*查找不到则返回*/
		printf("该进程没有被创建\n");
		return;
	}

	for (struct first_fit* q1 = create->next; q1; q1 = q1->next)
	{ /*遍历空闲分区*/
		if (p2->begin + p2->size == q1->begin)
		{ /*已分配分区与空闲分区相邻且在空闲分区的上方*/
			printf("\n空闲合并成功！\n");
			q1->set_data(q1->size + p2->size, p2->begin, q1->No);
			delete p2;
			return;
		}
		else if (q1->begin + q1->size == p2->begin)
		{ /*已分配分区与空闲分区相邻且在空闲分区的下方*/
			printf("\n空闲合并成功！\n");
			q1->set_data(q1->size + p2->size, q1->begin, q1->No);
			delete p2;
			return;
		}
		else if (q1->begin + q1->size == p2->begin && p2->begin + p2->size == q1->next->begin)
		{/*已分配分区与空闲分区相邻且在空闲分区的中间*/
			q1->set_data(q1->size + q1->next->size + p2->size, q1->begin, q1->No);
			struct first_fit* q2 = q1->next;
			q1->next = q1->next->next;
			delete q2;
			return;
		}
	}
	p2->set_data(p2->size, p2->begin); /*设置空闲分区状态为未分配*/

	struct first_fit* q = NULL;
	for (q = create; q->next; q = q->next) /*把已分区插入到第一个比其起始地址大的未分配分区前*/
		if (q->next->begin > p2->begin)
		{
			p2->next = q->next;
			q->next = p2;
			return;
		}
	p2->next = NULL;
	q->next = p2; /*把已分配分区插入到未分配分区前*/
	return;
}

int menu()
{
	printf("1.创建一个进程\n");
	printf("2.结束一个进程\n");
	printf("0.退出程序\n");
	printf("请输入数字: ");
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
	struct first_fit* create = new first_fit(); /*空闲分区链表*/
	struct first_fit* free = new first_fit(); /*已分配分区链表*/
	int size;
	int temp;
	printf("请输入内存大小:");
	scanf("%d", &size);
	init(create, size); /*初始化空闲分区*/
	printf("内存使用情况：（进程号数为0的块表示空闲内存）\n");
	PrintAll(create); /*输出空闲分区信息*/

	while ((temp = menu()))
	{
		switch (temp)
		{
		case 1: memory_malloc(create, free); break; /*分配空闲分区*/
		case 2: memory_free(create, free); break; /*回收空闲分区*/
		case 0: printf("输入错误\n"); break;
		}
		printf("\n进程所占分区\n");
		PrintAll(free);
		printf("空闲分区\n");
		PrintAll(create);
	}
	return 0;
}
