#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct Word{
    char word[50];
    int num;
    struct Word *next;
}Word;

void add(Word *head,char *str);
void sort(Word *head);
void display(Word *head);
void release(Word *head);

int main(void)
{
    FILE *fp;
    char filename[]="./file.txt";
    char str[50];
    Word *head;
    head=(Word*)malloc(sizeof(Word));
    memset(head,0,sizeof(Word));
    if((fp=fopen(filename,"r"))==NULL)
    {
        printf("Program can't open file!");
        exit(0);
    }
    while(fscanf(fp,"%s",str)!=EOF)
    {
        add(head,str);
    }
    fclose(fp);
    display(head);
    sort(head);
    release(head);
    return 0;
}

void add(Word *head,char *str)
{
    Word *newnode;
    Word *p=head;
    while(true){
        if(strcmp(p->word,str)==0)
        {
            p->num++;
            return;
        }
        else
        {
            if(p->next!=NULL)
            {
                p=p->next;
            }
            else
            {
                newnode=(Word*)malloc(sizeof(Word));
                memset(newnode,0,sizeof(Word));
                sprintf(newnode->word,"%s",str);
                newnode->num++;
                p->next=newnode;
                return;
            }
        }
    }
}

void sort(Word *head)
{
    Word *temp=head->next;
    Word *tempnode=head;
    Word *prenode;
    for(int i=0;i<3;i++)
    {
        temp=head;tempnode=head;
        while(temp->next!=NULL)
        {
            if(tempnode->num<temp->next->num)
            {
                prenode=temp;
                tempnode=temp->next;
            }
            temp=temp->next;
        }
        printf("%s %d\n",tempnode->word,tempnode->num);
        prenode->next=tempnode->next;
        free(tempnode);
    }
}

void display(Word *head)
{
    int sum=0;
    Word *temp=head->next;
    while(temp!=NULL)
    {
        sum++;
        temp=temp->next;
    }
    printf("Words: %d\n",sum);
    printf("\n");
    Word *show=head->next;
    for(show;show!=NULL;show=show->next)
    {
        printf("%s %d\n",show->word,show->num);
    }
    printf("\n");
}

void release(Word *head)
{
    Word *newnode;
    Word *prenode=head;
    while(prenode!=NULL)
    {
        newnode=prenode->next;
        free(prenode);
        prenode=newnode;
    }
}
