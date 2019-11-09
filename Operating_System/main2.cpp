#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<pthread.h>
#include<iostream>
#pragma comment(lib, "pthreadVC2.lib")
using namespace std;
void pickup_forks(int i);
void putdown_forks(int i);
void* runner(void*);
void test(int i);

pthread_mutex_t mutex;
pthread_cond_t cond_var[5];

enum
{
	THINKING, HUNGRY, EATING
} state[5];

int main(void)
{
	int index[5];
	//	srand(time(NULL));

	pthread_t tid[5]; /* the thread identifier */
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
		//��һ������Ϊָ���̱߳�ʶ����ָ�롣�ڶ����������������߳����ԡ��������������߳����к�������ʼ��ַ�����һ�����������к����Ĳ�����
	}
	for (int i = 0; i < 5; i++)
	{
		pthread_join(tid[i], NULL);
	}
	system("pause");
	return 0;
}

void* runner(void* args)
{
	int ind = *((int*)args);
	int cnt = 0;

	int temp, temp1, temp2;

	while (cnt < 1)
	{
		cnt++; temp = ind;
		printf("��ѧ��%d����˼��...\n", ind);
		Sleep(500);
		printf("��ѧ��%d����˼��\n", ind);
		printf("��ѧ��%d���뼢��״̬...\n", ind);
		pickup_forks(ind);
		temp1 = (temp + 4) % 5; temp2 = (temp + 1) % 5;
		printf("��ѧ��%d������ӽ��оͲ�...��ռ���˿���%d��%d\n", ind, temp1, temp2);
		Sleep(500);
		printf("��ѧ��%d�����Ͳ�\n", ind);
		putdown_forks(ind);
		printf("��ѧ��%d���¿���\n", ind);
	}
	pthread_exit(0);
	return NULL;
}
//������ӣ������жϵ�i����ѧ���Ƿ���ԾͲͣ�������ԣ�����״̬��ΪEATING�����оͲͣ�����ȴ����������Ͳͣ����¿��ӡ�
void pickup_forks(int i)
{
	pthread_mutex_lock(&mutex);
	state[i] = HUNGRY;
	test(i);
	while (state[i] != EATING)
	{
		printf("��ѧ��%d�ȴ����ӿ���...\n", i);
		pthread_cond_wait(&cond_var[i], &mutex);
	}
	pthread_mutex_unlock(&mutex);
}

//�жϵ�i����ѧ���Ƿ���ԾͲ͡�������ԣ�����״̬��ΪEATING��
void test(int i)
{   //������������Ϊ�� ��ѧ�� i ���Խ��оͲͣ����ҽ����������������ھͲ�״̬����(state[(i + 4) % 5] != EATING)&&(state[(i+1) % 5] != EATING)
	if ((state[(i + 4) % 5] != EATING) && (state[i] == HUNGRY) && (state[(i + 1) % 5] != EATING))
	{
		state[i] = EATING;
		pthread_cond_signal(&cond_var[i]);
	}
}//stateΪö������

//���¿��ӣ����ı��i����ѧ�ҵ�״̬ΪTHINKING���ж�������������ѧ���Ƿ���ԾͲͣ�������ԣ�����״̬��ΪEATING��
void putdown_forks(int i)
{
	pthread_mutex_lock(&mutex);
	state[i] = THINKING;
	test((i + 4) % 5);
	test((i + 1) % 5);
	pthread_mutex_unlock(&mutex);
}
