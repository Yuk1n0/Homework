#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//定义结构体
typedef struct Student
{
    int num;
    struct Student *next;
} Student;

//初始化链表
Student *init()
{
    Student *head = (Student *)malloc(sizeof(Student));
    if (NULL == head)
    {
        printf("初始化内存失败！\n");
        return NULL;
    }
    else
    {
        printf("结构体大小为：");
        printf("%ld \n", sizeof(Student));
        return head;
    }
}

//创建新链表并初次添加数据
Student *create(Student *head)
{
    Student *p, *q = NULL;
    int i = 0;
    p = head;
    while (true)
    {
        printf("请输入要存储的数据（输入0结束）：");
        scanf("%d", &i);
        if (i != 0)
        {
            q = (Student *)malloc(sizeof(Student));
            q->num = i;
            q->next = NULL;
            p->next = q;
            p = q;
        }
        else
        {
            if (head->next == NULL)
            {
                printf("未输入任何数据，请重新输入！\n");
            }
            else
            {
                printf("输入结束！\n");
                break;
            }
        }
    }
    printf("\n");
    return head;
}

//添加数字
Student *insert(Student *head, int num)
{
    Student *p, *q = NULL;
    p = head->next;
    while (p->next != NULL)
    {
        p = p->next;
    }
    q = (Student *)malloc(sizeof(Student));
    q->num = num;
    q->next = NULL;
    p->next = q;
    printf("\n");
    return head;
}

//删除数字
Student *del(Student *head, int num)
{
    Student *p, *q = NULL;
    q = head;
    int flag = 0;
    for (p = head->next; p != NULL; p = p->next)
    {
        if (p->num == num)
        {
            q->next = p->next;
            free(p);
            p = q;
            flag++;
        }
        else
        {
            q = q->next;
        }
    }
    if (flag == 0)
    {
        printf("在链表内找不到该数\n");
    }
    printf("\n");
    return head;
}

//输出链表内全部数据
void *print(Student *head)
{
    Student *p = NULL;
    p = head->next;
    if (head->next == NULL)
    {
        printf("链表为空！\n");
    }
    else
    {
        while (p != NULL)
        {
            printf("当前结构体数据为：%d   结构体地址为：%p   指针地址为：%p \n", p->num, (void *)p, (void *)&p);
            p = p->next;
        }
    }
    printf("读取链表内数据结束！\n");
    printf("\n");
    return head;
}

int main(void)
{
    int num;
    Student *head = NULL;
    head = init();
    create(head);
    print(head);
    printf("请输入要插入的数字：");
    scanf("%d", &num);
    insert(head, num);
    print(head);
    printf("请输入要删除的数字：");
    scanf("%d", &num);
    del(head, num);
    print(head);
    return 0;
}
