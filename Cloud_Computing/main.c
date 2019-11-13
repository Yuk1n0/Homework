#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct Word
{
    char word[50];
    int num;
    struct Word *next;
} Word;

void add(Word *head, char *str);
void sort(Word *head);
void display(Word *head);
void release(Word *head);

int main(void)
{
    clock_t starttime, endtime;
    double cost;
    starttime = clock();
    FILE *fp = NULL;
    char filename[] = "./file.txt";
    char str[50] = {0};
    Word *head = NULL;
    head = (Word *)malloc(sizeof(Word));
    memset(head, 0, sizeof(Word));
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Program can't open this file!");
        exit(0);
    }
    while (fscanf(fp, "%s", str) != EOF)
    {
        add(head, str);
    }
    printf("头指针地址为:%p ,文件指针为地址:%p ,数组首地址为:%p\n", (void *)head, (void *)fp, (void *)str);
    fclose(fp);
    display(head);
    sort(head);
    release(head);
    endtime = clock();
    cost = (double)(endtime - starttime) / CLOCKS_PER_SEC;
    printf("程序运行时间为: %lf秒\n", cost);
    return 0;
}

void add(Word *head, char *str)
{
    char *test = str;
    for (test = str; (int)*test != 0; test++)
    {
        if ((int)*test >= 32 && (int)*test <= 47)
        {
            *test = 0;
        }
    }
    Word *newnode;
    Word *p = head;
    while (true)
    {
        if (strcmp(p->word, str) == 0)
        {
            p->num++;
            return;
        }
        else if (strcmp((p->word) + 1, str + 1) == 0)
        {
            p->num++;
            return;
        }
        else
        {
            if (p->next != NULL)
            {
                p = p->next;
            }
            else
            {
                newnode = (Word *)malloc(sizeof(Word));
                memset(newnode, 0, sizeof(Word));
                sprintf(newnode->word, "%s", str);
                newnode->num++;
                p->next = newnode;
                return;
            }
        }
    }
}

void sort(Word *head)
{
    Word *traversal, *tempnode, *prenode;
    for (int i = 0; i < 3; i++)
    {
        traversal = head;
        tempnode = head;
        while (traversal->next != NULL)
        {
            if (tempnode->num < traversal->next->num)
            {
                prenode = traversal;
                tempnode = traversal->next;
            }
            traversal = traversal->next;
        }
        printf("%s %d\n", tempnode->word, tempnode->num);
        prenode->next = tempnode->next;
        free(tempnode);
    }
}

void display(Word *head)
{
    int sum = 0;
    Word *temp = head->next;
    while (temp != NULL)
    {
        sum++;
        temp = temp->next;
    }
    printf("Words: %d\n", sum);
    printf("\n");
    Word *show = head->next;
    for (show; show != NULL; show = show->next)
    {
        printf("%s %d\n", show->word, show->num);
    }
    printf("\n");
}

void release(Word *head)
{
    Word *curnode;
    Word *prenode = head;
    while (prenode != NULL)
    {
        curnode = prenode->next;
        free(prenode);
        prenode = curnode;
    }
}
