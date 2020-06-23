#include <iostream>
#include <queue>
#include <set>
#include <fstream>
#include <ctime>
using namespace std;
//847652310
int select; //用于选择启发式函数的类型

typedef class UDuilie
{
public:
    char datas[3][3];
    void getdata()
    {
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                cin >> datas[i][j];
            }
        }
    }

    bool equals(UDuilie second)
    {
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                if (this->datas[i][j] != second.datas[i][j])
                    return false;
            }
        }
        return true;
    }
    bool operator<(UDuilie second) const
    {
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                if (this->datas[i][j] != second.datas[i][j])
                    return this->datas[i][j] < second.datas[i][j];
            }
        }
        return false;
    }
} UDuilie;

typedef class Sets
{
public:
    int f;    //记录函数值
    int step; //记录步数
    UDuilie d;
    int x;
    int y;
    Sets() : f(9), step(0) {}
    Sets(int f, int step, UDuilie d) : f(f), step(step), d(d) {}
    bool operator<(Sets second) const
    {
        return this->f > second.f;
    }
} Sets;

int total = -1; //最终多少步
priority_queue<Sets> que;
set<UDuilie> s;
int m[2][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}}; //移动零
UDuilie aim;

int isReach(char a[3][3])
{
    //记录是奇序列还是偶序列
    int xulie = 0;
    int b[9];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            b[i * 3 + j] = a[i][j] - 48;
        }
    for (int i = 0; i < 9; i++)
    {
        if (b[i] == 0)
        {
            continue;
        }
        for (int j = 0; j < i; j++)
        {
            if (b[j] > b[i])
            {
                xulie++;
            }
        }
    }
    return xulie;
}

//启发函数：即当前节点与目标节点格局相比，位置不符的数字个数。
int h1(Sets Sets)
{
    int result = 0;
    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (Sets.d.datas[i][j] != aim.datas[i][j])
                result++;
        }
    }
    return result;
}

//位置不符的数字移动到目标节点中对应位置的最短距离之和。
int h2(Sets Sets)
{
    int result = 0;
    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {

            for (int m = 0; m <= 2; m++)
                for (int n = 0; n <= 2; n++)
                {
                    if (Sets.d.datas[m][n] == aim.datas[i][j])
                    {
                        result += abs(m - i) + abs(n - j);
                    }
                }
        }
    }
    return result;
}

//为每一对逆序数字乘以一个倍数。
int h3(Sets Sets)
{
    int result;
    result = 3 * isReach(Sets.d.datas);
    return result;
}

//位置不符数字个数的总和与 3 倍数字逆序数目相加
int h4(Sets Sets)
{
    int result;
    result = h3(Sets) + h2(Sets);
    return result;
}

void change(Sets *Sets, int x, int y, int x1, int y1)
{
    char a = Sets->d.datas[x][y];
    Sets->d.datas[x][y] = Sets->d.datas[x1][y1];
    Sets->d.datas[x1][y1] = a;
}

void Search(Sets start)
{
    ofstream ofs;
    ofs.open("result.txt");
    start.step = 0;
    switch (select)
    {
    case 1:
        start.f = h1(start);
        break;
    case 2:
        start.f = h2(start);
        break;
    case 3:
        start.f = h3(start);
        break;
    case 4:
        start.f = h4(start);
        break;
    default:
        cout << "输入错误！" << endl;
    }
    //记录初始零的位置
    for (int a = 0; a <= 2; a++)
    {
        for (int b = 0; b <= 2; b++)
        {
            if (start.d.datas[a][b] == '0')
            {
                start.x = a;
                start.y = b;
                break;
            }
        }
    }
    s.insert(start.d);
    que.push(start);
    //写入队列
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ofs << start.d.datas[i][j] << " ";
        }
        ofs << endl;
    }
    ofs << endl;
    while (!que.empty())
    {
        Sets now = que.top();
        que.pop();
        if (total != -1 && now.step >= total)
            continue;
        if (now.d.equals(aim))
        {
            total = now.step;
            break;
        }
        //四次循环分别上移、下移、左移、右移
        for (int i = 0; i <= 3; i++)
        {
            //设立临时结点来辅助交换
            Sets temp = now;
            int x = temp.x, y = temp.y;
            temp.x += m[0][i];
            temp.y += m[1][i];
            //如果移动之后还在里面则交换，count记录的是是否已经存在这个状态
            if (temp.x >= 0 && temp.x <= 2 && temp.y >= 0 && temp.y <= 2)
            {
                change(&temp, x, y, temp.x, temp.y);
                switch (select)
                {
                case 1:
                    temp.f = h1(temp) + temp.step + 1;
                    break;
                case 2:
                    temp.f = h2(temp) + temp.step + 1;
                    break;
                case 3:
                    temp.f = h3(temp) + temp.step + 1;
                    break;
                case 4:
                    temp.f = h4(temp) + temp.step + 1;
                    break;
                }
                temp.step++;
                if (!s.count(temp.d))
                {
                    s.insert(temp.d);
                    que.push(temp);
                    //写入队列
                    for (int i = 0; i < 3; i++)
                    {
                        for (int j = 0; j < 3; j++)
                        {
                            ofs << temp.d.datas[i][j] << " ";
                        }
                        ofs << endl;
                    }
                    ofs << endl;
                }
            }
        }
    }
    ofs.close();
}

int main(void)
{
    cout << "--------------全局择优搜索八数码问题--------------" << endl;
    cout << endl;
    cout << "1、启发函数 h(n)定义为当前节点与目标节点差异的度量" << endl;
    cout << "2、启发函数 h(n)定义为当前节点与目标节点距离的度量" << endl;
    cout << "3、启发函数 h(n)定义为每一对逆序数字乘以一个倍数" << endl;
    cout << "4、启发函数 h(n)定义为位置不符数字个数的总和与 3 倍数字逆序数目相加" << endl;
    cout << endl;
    cout << "请选择启发式函数的类型：";
    cin >> select;
    UDuilie d;
    int bxulie; //初始状态的奇偶性
    int axulie; //目标状态的奇偶性
    clock_t startTime, endTime;
    cout << "请输入起始状态(0-8)：" << endl;
    d.getdata();
    cout << "请输入终止状态(0-8)：" << endl;
    aim.getdata();
    bxulie = isReach(d.datas);
    axulie = isReach(aim.datas);
    if (bxulie % 2 == axulie % 2) //判断初始状态与目标状态是否同奇或同偶数
    {
        cout << "状态可达！" << endl;
        cout << "准备搜索...\n";
        system("pause");
        startTime = clock(); //计时开始
        cout << "搜索中.....\n";
        Search(Sets(0, 0, d));
        cout << endl;
        endTime = clock(); //计时结束
        cout << "搜索完毕\n";
        cout << "运行时间是: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
        cout << "一共经过了" << total << "步" << endl;
    }
    else
    {
        cout << "目标状态不可达！" << endl;
        exit(0);
    }
    system("pause");
    return 0;
}
