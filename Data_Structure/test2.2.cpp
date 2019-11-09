#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define error 0
#define ok 1
#define overflow -1
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OPSETSIZE 7

char OPSET[OPSETSIZE] = { '+','-','*','/','(',')','#' };
unsigned char Prior[7][7] = 
{ // ���������ȹ�ϵ
	'>','>','<','<','<','>','>',
	'>','>','<','<','<','>','>',
	'>','>','>','>','<','>','>',
	'>','>','>','>','<','>','>',
	'<','<','<','<','<','=',' ',
	'>','>','>','>',' ','>','>',
	'<','<','<','<','<',' ','='
};

typedef int Status;
template <typename T>
struct SqStack
{
	T* top;
	T* base;
	int stacksize;
};//˳��ջ�ṹģ��

template <typename T1, typename T2>

Status InitStack(T1& S)
{
	S.base = (T2*)malloc(STACK_INIT_SIZE * sizeof(T2));
	if (!S.base) exit(overflow);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return ok;
}//��ʼ��ջ����ģ��

template <typename T1, typename T2>

Status Push(T1& S, T2 e)
{
	if (S.top - S.base >= S.stacksize)
	{
		S.base = (T2*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(T2));
		if (!S.base) exit(overflow);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return ok;
}//��ջ����ģ��

template <typename T1, typename T2>

Status Pop(T1& S, T2& e)
{
	if (S.top == S.base) return error;
	e = *--S.top;
	return ok;
}//��ջ����ģ��

template <typename T1, typename T2>

T2 GetTop(T1 S)
{
	if (S.top == S.base)
		return error;
	else
		return *(S.top - 1);
}//��ȡջ��Ԫ��ģ��

Status In(char Test, char* TestOp)
{
	bool Find = false;
	for (int i = 0; i < OPSETSIZE; i++)
	{
		if (Test == TestOp[i]) Find = true;
	}
	return Find;
}//�ж��Ƿ�Ϊ�����

float Operate(float a, unsigned char theta, float b)
{
	switch (theta) 
    {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	default: return 0;
	}
}//����

int ReturnOpOrd(char op, char* TestOp)
{
	int i;
	for (i = 0; i < OPSETSIZE; i++)
	{
		if (op == TestOp[i]) return i;
	}
	return 0;
}

char precede(char Aop, char Bop)
{
	return Prior[ReturnOpOrd(Aop, OPSET)][ReturnOpOrd(Bop, OPSET)];
}//ReturnOpOrd��precede��ϣ��ж���������ȼ�

float EvaluateExpression()
{
	// �������ʽ��ֵ����������㷨��
	// ��OPTR��OPND�ֱ�Ϊ�����ջ��������ջ��OPSETΪ��������ϡ�
	SqStack<char> OPTR; // �����ջ���ַ�Ԫ��
	SqStack<float> OPND; // ������ջ��ʵ��Ԫ��
	char TempData[20];
	float Data, a, b;
	char theta, c, x, Dr[2];
	InitStack<SqStack<char>, char>(OPTR);
	Push(OPTR, '#');
	InitStack <SqStack<float>, float>(OPND);
	strcpy(TempData, "\0");//��TempData��Ϊ��
	c = getchar();
	while (c != '#' || GetTop<SqStack<char>, char>(OPTR) != '#')
	{
		if (!In(c, OPSET))
		{
			Dr[0] = c;
			Dr[1] = '\0';//��ŵ�����
			strcat(TempData, Dr);//������������TempData�У��γ��ַ���
			c = getchar();
			if (In(c, OPSET))//�����������������ַ���TempDataת����ʵ������ջ���������ÿ�
			{
				Data = (float)atof(TempData);
				Push(OPND, Data);
				strcpy(TempData, "\0");
			}
		}
		else
		{ // ������������ջ
			switch (precede(GetTop<SqStack<char>, char>(OPTR), c))
			{
			case '<': // ջ��Ԫ������Ȩ��
				Push(OPTR, c);
				c = getchar();
				break;
			case '=': // �����Ų�������һ�ַ�
				Pop(OPTR, x);
				c = getchar();
				break;
			case '>': // ��ջ������������ջ
				Pop(OPTR, theta);
				Pop(OPND, b);
				Pop(OPND, a);
				Push(OPND, Operate(a, theta, b));
				break;
			} // switch
		}
	} // while
	return GetTop<SqStack<float>, float>(OPND);
} // EvaluateExpression

int main(void)
{
	printf("��������ʽ��end #����\n");
	printf("%f\n", EvaluateExpression());
    return 0;
}
