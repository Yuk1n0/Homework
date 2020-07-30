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
void display(Word *head);
void sort(Word *head);
void release(Word *head);

int main(void)
{
    clock_t starttime, endtime;
    double cost;
    starttime = clock();

    FILE *fp = NULL;
    char filename[] = "./data.dat";
    char str[50] = {0};

    Word *head = NULL;
    head = (Word *)malloc(sizeof(Word));
    if (head == NULL)
    {
        printf("Can't initialize node !\n");
        exit(0);
    }
    memset(head, 0, sizeof(Word));

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Program can't open this file !\n");
        exit(0);
    }

    while (fscanf(fp, "%s", str) != EOF)
    {
        add(head, str);
    }
    fclose(fp);

    display(head);
    sort(head);
    release(head);

    endtime = clock();
    cost = (double)(endtime - starttime) / CLOCKS_PER_SEC;
    printf("Running time: %lf sec\n", cost);
    return 0;
}

void add(Word *head, char *str)
{
    char *test = str;
    char *index = str + 1;

    if ((int)*test >= 32 && (int)*test <= 47)
    {
        *test = 0;
        int i = 0;
        for (i = 0; i < 49; i++)
        {
            *test = *index;
            test = test + 1;
            index = index + 1;
        }
    }

    for (test = str; (int)*test != 0; test++)
    {
        if ((int)*(test + 1) == 0)
        {
            if (((int)*test >= 32 && (int)*test <= 47) || ((int)*test >= 58 && (int)*test <= 64))
            {
                *test = 0;
            }
        }
    }

    Word *newnode;
    Word *p = head;
    while (true)
    {
        if (strcasecmp(p->word, str) == 0)
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

void display(Word *head)
{
    int count = 0;
    Word *word = head->next;
    while (word != NULL)
    {
        count++;
        word = word->next;
    }
    printf("Words: %d\n", count);
    printf("\n");
    word = head->next;
    for (word; word != NULL; word = word->next)
    {
        printf("%s %d\n", word->word, word->num);
    }
    printf("\n");
}

void sort(Word *head)
{
    int i;
    Word *traversal, *maxnode, *curnode;
    for (i = 0; i < 3; i++)
    {
        traversal = head;
        maxnode = head;
        while (traversal->next != NULL)
        {
            if (maxnode->num < traversal->next->num)
            {
                curnode = traversal;
                maxnode = traversal->next;
            }
            traversal = traversal->next;
        }
        printf("%s %d\n", maxnode->word, maxnode->num);
        curnode->next = maxnode->next;
        free(maxnode);
    }
}

void release(Word *head)
{
    Word *cur;
    Word *pre = head;
    while (pre != NULL)
    {
        cur = pre->next;
        free(pre);
        pre = cur;
    }
}