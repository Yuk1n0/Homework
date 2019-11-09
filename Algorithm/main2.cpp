#include<stdio.h>
#include<string.h>

const int MAX = 64;
//�ֵ�����С�����߷���
const int Length[8] = { -1, 1, -2, 2, -2, 2, -1, 1 };
const int Width[8] = { -2, -2, -1, -1, 1, 1, 2, 2 };
int p, q;
bool Visited[MAX][MAX];
bool isTraveled; //�Ƿ�ɹ������ı��

struct path
{
	char x, y;
} path[MAX];

void DFS(int x, int y, int num)
{
	path[num].x = x + '0';
	path[num].y = y + 'A' - 1;   //int תΪ char

	if (num == p * q)
	{
		isTraveled = true;
		return;
	}
	for (int i = 0; i < 8; i++)
	{
		int x1 = x + Length[i];
		int y1 = y + Width[i];
		if (0 < x1 && x1 <= p && 0 < y1 && y1 <= q && !Visited[x1][y1] && !isTraveled)
		{
			Visited[x1][y1] = true;
			DFS(x1, y1, num + 1);
			Visited[x1][y1] = false;    //�����ò�
		}
	}
}

int main(void)
{
	int count;
	scanf("%d", &count);
	for (int i = 1; i <= count; i++)
	{
		scanf("%d %d", &p, &q);
		isTraveled = false;
		memset(Visited, false, sizeof(Visited));
		Visited[1][1] = true;    //���
		DFS(1, 1, 1);
		printf("Scenario #%d:\n", i);
		if (isTraveled)
		{
			for (int i = 1; i <= p * q; i++)
			{
				printf("%c%c", path[i].y, path[i].x);
			}
			printf("\n");
		}
		else
			printf("impossible\n");
	}
	return 0;
}
