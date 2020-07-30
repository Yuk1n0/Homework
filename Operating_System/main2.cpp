/*
gcc main2.cpp -lpthread -o main.out
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void pickup_forks(int i);
void putdown_forks(int i);
void *runner(void *);
void test(int i);

pthread_mutex_t mutex;
pthread_cond_t cond_var[5];

enum
{
    THINKING,
    HUNGRY,
    EATING
} state[5];

int main(void)
{
    int index[5];
    pthread_t tid[5];    /* the thread identifier */
    pthread_attr_t attr; /* set of thread attributes */

    pthread_mutex_init(&mutex, NULL);
    pthread_attr_init(&attr);

    for (int i = 0; i < 5; i++)
    {
        state[i] = THINKING;
        pthread_cond_init(&cond_var[i], NULL);
    }
    for (int i = 0; i < 5; i++)
    {
        index[i] = i;
        pthread_create(&tid[i], &attr, runner, &index[i]);
        //第一个参数为指向线程标识符的指针。第二个参数用来设置线程属性。第三个参数是线程运行函数的起始地址。最后一个参数是运行函数的参数。
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(tid[i], NULL);
    }
    return 0;
}

void *runner(void *args)
{
    int ind = *((int *)args);
    int cnt = 0;
    int temp, temp1, temp2;

    while (cnt < 1)
    {
        cnt++;
        temp = ind;
        printf("哲学家%d进行思考...\n", ind);
        sleep(5);
        printf("哲学家%d结束思考\n", ind);
        printf("哲学家%d进入饥饿状态...\n", ind);
        pickup_forks(ind);
        temp1 = (temp + 4) % 5;
        temp2 = (temp + 1) % 5;
        printf("哲学家%d拿起筷子进行就餐...并占用了筷子%d和%d\n", ind, temp1, temp2);
        sleep(5);
        printf("哲学家%d结束就餐\n", ind);
        putdown_forks(ind);
        printf("哲学家%d放下筷子\n", ind);
    }
    pthread_exit(0);
    return NULL;
}

//拿起筷子，首先判断第i个哲学家是否可以就餐，如果可以，则将其状态改为EATING并进行就餐；否则等待邻座结束就餐，放下筷子。
void pickup_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    test(i);
    while (state[i] != EATING)
    {
        printf("哲学家%d等待筷子可用...\n", i);
        pthread_cond_wait(&cond_var[i], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

//判断第i个哲学家是否可以就餐。如果可以，则将其状态改为EATING。
void test(int i)
{ //避免死锁策略为： 哲学家 i 可以进行就餐，当且仅当两个邻座不处于就餐状态，即(state[(i + 4) % 5] != EATING)&&(state[(i+1) % 5] != EATING)
    if ((state[(i + 4) % 5] != EATING) && (state[i] == HUNGRY) && (state[(i + 1) % 5] != EATING))
    {
        state[i] = EATING;
        pthread_cond_signal(&cond_var[i]);
    }
} //state为枚举数组

//放下筷子，即改变第i个哲学家的状态为THINKING，判断邻座的两个哲学家是否可以就餐，如果可以，则将其状态改为EATING。
void putdown_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    test((i + 4) % 5);
    test((i + 1) % 5);
    pthread_mutex_unlock(&mutex);
}
