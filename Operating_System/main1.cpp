#include <iostream>
#include <iomanip>
using namespace std;

static const int MaxNum = 100;
double ArrivalTime[MaxNum];
double ServiceTime[MaxNum];
double FinishTime[MaxNum];
int Priority[MaxNum];
double WholeTime[MaxNum];
double WeightWholeTime[MaxNum];
double AverageWT, AverageWWT;
double WT, WWT;

void FCFS(int n)
{
    int m[MaxNum] = {0};
    cout << endl;
    cout << "FCFS:" << endl;
    cout << "   进程ID"
         << "         到达时间"
         << "         完成时间"
         << "         周转时间"
         << "      带权周转时间" << endl;

    //完成时间计算
    FinishTime[0] = ArrivalTime[0] + ServiceTime[0];
    double temp[MaxNum] = {0};
    for (int i = 1; i < n; i++)
    {
        temp[i] = ArrivalTime[i];
    }

    ////////////////////////////////////////////////////////
    m[0] = 0;
    double temps;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
            if (temp[j] > temp[j + 1])
            {
                temps = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = temps;
            }
    }
    ////////////////////////////////////////////////////////

    for (int k = 1; k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            if (temp[k] == ArrivalTime[l])
                m[k] = l;
        }
    }

    for (int i = 1; i < n; i++)
    {
        if ((ArrivalTime[m[i]] - FinishTime[m[i - 1]]) > 0)
        {
            FinishTime[m[i]] = ArrivalTime[m[i]] + ServiceTime[m[i]];
        }
        else
        {
            FinishTime[m[i]] = FinishTime[m[i - 1]] + ServiceTime[m[i]];
        }
    }

    for (int i = 0; i < n; i++)
    {
        WholeTime[i] = FinishTime[i] - ArrivalTime[i];
        WeightWholeTime[i] = (double)WholeTime[i] / (double)ServiceTime[i];
        WT = WT + WholeTime[i];
        WWT = WWT + WeightWholeTime[i];
        cout << "\t" << setprecision(3) << i + 1 << "\t\t" << setprecision(3) << ArrivalTime[i] << "\t\t" << setprecision(3) << FinishTime[i] << "\t\t" << setprecision(3) << WholeTime[i] << "\t\t" << setprecision(3) << WeightWholeTime[i];
        cout << endl;
    }
    cout << endl;
    AverageWWT = WWT / n;
    AverageWT = WT / n;
    cout << "平均周转时间为：        " << setprecision(3) << AverageWT << endl;
    cout << "平均带权周转时间为:     " << setprecision(3) << AverageWWT << endl;
    cout << "执行顺序：";
    for (int i = 0; i < n - 1; i++)
    {
        cout << m[i] + 1 << " -> ";
    }
    cout << m[n - 1] + 1;
    WT = 0;  //WT和WWT最后要置零，因为单独把计算周转时间等作为一个函数
    WWT = 0; //如果不置零将导致后续引用该函数的出错
    cout << endl;
}

void SJF(int n)
{
    cout << endl;
    cout << "SJF(非抢占式):" << endl;
    cout << "   进程ID"
         << "         到达时间"
         << "         完成时间"
         << "         周转时间"
         << "      带权周转时间" << endl;
    int m[MaxNum] = {0};

    bool judge = false;
    ;
    for (int i = 1; i < n; i++)
    {
        if (ArrivalTime[i] < ArrivalTime[0])
        {
            judge = true;
        }
    }

    if (judge == false)
    {
        FinishTime[0] = ArrivalTime[0] + ServiceTime[0];
        double temp[MaxNum] = {0};
        for (int i = 1; i < n; i++)
        {
            temp[i] = ServiceTime[i];
        }

        ////////////////////////////////////////////////////////
        m[0] = 0;
        double temps;
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n - i; j++)
                if (temp[j] > temp[j + 1])
                {
                    temps = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = temps;
                }
        }
        ////////////////////////////////////////////////////////

        for (int k = 1; k < n; k++)
        {
            for (int l = 0; l < n; l++)
            {
                if (temp[k] == ServiceTime[l])
                    m[k] = l;
            }
        }

        for (int i = 1; i < n; i++)
        {
            if ((ArrivalTime[m[i]] - FinishTime[m[i - 1]]) > 0)
            {
                FinishTime[m[i]] = ArrivalTime[m[i]] + ServiceTime[m[i]];
            }
            else
            {
                FinishTime[m[i]] = FinishTime[m[i - 1]] + ServiceTime[m[i]];
            }
        }

        for (int i = 0; i < n; i++)
        {

            WholeTime[i] = FinishTime[i] - ArrivalTime[i];
            WeightWholeTime[i] = WholeTime[i] / ServiceTime[i];
            WT = WT + WholeTime[i];
            WWT = WWT + WeightWholeTime[i];
            cout << "\t" << setprecision(3) << i + 1 << "\t\t" << setprecision(3) << ArrivalTime[i] << "\t\t" << setprecision(3) << FinishTime[i] << "\t\t" << setprecision(3) << WholeTime[i] << "\t\t" << setprecision(3) << WeightWholeTime[i];
            cout << endl;
        }
        AverageWWT = WWT / n;
        AverageWT = WT / n;
        cout << "平均周转时间为：        " << setprecision(3) << AverageWT << endl;
        cout << "平均带权周转时间为:     " << setprecision(3) << AverageWWT << endl;
        cout << "执行顺序：";
        for (int i = 0; i < n - 1; i++)
        {
            cout << m[i] + 1 << " -> ";
        }
        cout << m[n - 1] + 1;
        WT = 0;  //WT和WWT最后要置零，因为我单独把计算周转时间等作为一个函数
        WWT = 0; //如果不置零将导致后续引用该函数的出错
        cout << endl;
    }
    else
    {
    }
}

void HRN(int n)
{
    int m[MaxNum] = {0};
    m[0] = 0;
    double ResponseRatio[MaxNum] = {600000.0};
    cout << endl;
    cout << "HRN:" << endl;
    cout << "   进程ID"
         << "         到达时间"
         << "         完成时间"
         << "         周转时间"
         << "      带权周转时间" << endl;
    FinishTime[0] = ArrivalTime[0] + ServiceTime[0]; //计算第一个进程的终止时间
    double temp[MaxNum] = {0};
    int var = 0;
    double a = 500000.0;
    for (int i = 1; i < n - 1; i++)
    {
        //计算每次执行下一个进程调度时，剩余各个进程的响应比，若该进程已计算过，则忽略
        for (int j = 1; j < n; j++)
        {
            if (j == m[i - 1])
            {
                ResponseRatio[j] = a;
                a--;
                break;
            }
            ResponseRatio[j] = 1 + ((FinishTime[m[i - 1]] - ArrivalTime[j]) / ServiceTime[j]);
        }
        //temp数组拷贝 ResponseRatio进程响应比数组的信息
        for (int k = 0; k < n; k++)
        {
            temp[k] = ResponseRatio[k];
        }
        //将响应比运用冒泡排序由大到小排序
        double temps;
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < n - x; y++)
                if (temp[y] < temp[y + 1])
                {
                    temps = temp[y];
                    temp[y] = temp[y + 1];
                    temp[y + 1] = temps;
                }
        }
        //对排好序的响应比数组进行对应，将排列好的进程顺序一一对应，并将进程顺序保存咋m数组中
        for (int x1 = 0; x1 < n; x1++)
        {
            for (int x2 = 0; x2 < n; x2++)
            {
                if (temp[x1] == ResponseRatio[x2])
                    m[x1] = x2;
            }
        }
        var = m[i];
        //计算下一个调入进程的终止时间，若该进程的到达时间比上一个进程的终止时间还要晚，则更改终止时间为该进程到达时间+响应时间
        if ((ArrivalTime[m[i]] - FinishTime[m[i - 1]]) > 0)
        {
            FinishTime[m[i]] = ArrivalTime[m[i]] + ServiceTime[m[i]];
        }
        else
        {
            FinishTime[m[i]] = FinishTime[m[i - 1]] + ServiceTime[m[i]];
        }
    }
    //计算最后一个数组的终止时间
    int x3 = n - 1;
    if ((ArrivalTime[m[x3]] - FinishTime[m[x3 - 1]]) > 0)
    {
        FinishTime[m[x3]] = ArrivalTime[m[x3]] + ServiceTime[m[x3]];
    }
    else
    {
        FinishTime[m[x3]] = FinishTime[m[x3 - 1]] + ServiceTime[m[x3]];
    }
    //计算进程调度结束后每个进程的周转时间与平均周转时间，并计算整个过程的平均周转时间和平均带权周转时间
    for (int i = 0; i < n; i++)
    {
        WholeTime[i] = FinishTime[i] - ArrivalTime[i];
        WeightWholeTime[i] = (double)WholeTime[i] / (double)ServiceTime[i];
        WT = WT + WholeTime[i];
        WWT = WWT + WeightWholeTime[i];
        cout << "\t" << setprecision(3) << i + 1 << "\t\t" << setprecision(3) << ArrivalTime[i] << "\t\t" << setprecision(3) << FinishTime[i] << "\t\t" << setprecision(3) << WholeTime[i] << "\t\t" << setprecision(3) << WeightWholeTime[i];
        cout << endl;
    }
    cout << endl;
    AverageWWT = WWT / n;
    AverageWT = WT / n;
    cout << "平均周转时间为：        " << setprecision(3) << AverageWT << endl;
    cout << "平均带权周转时间为:     " << setprecision(3) << AverageWWT << endl;
    cout << "执行顺序：";
    for (int i = 0; i < n - 1; i++)
    {
        cout << m[i] + 1 << " -> "; //输出调度顺序
    }
    cout << m[n - 1] + 1;
    WT = 0;  //WT和WWT最后要置零，因为单独把计算周转时间等作为一个函数
    WWT = 0; //如果不置零将导致后续引用该函数的出错
    cout << endl;
}

void PriorityFunction(int n)
{
    int m[MaxNum] = {0};
    cout << endl;
    cout << "优先级算法:" << endl;
    cout << "   进程ID"
         << "         到达时间"
         << "         完成时间"
         << "         周转时间"
         << "      带权周转时间" << endl;

    //完成时间计算
    FinishTime[0] = ArrivalTime[0] + ServiceTime[0];
    double temp[MaxNum] = {0};
    for (int i = 1; i < n; i++)
    {
        temp[i] = Priority[i];
    }

    ////////////////////////////////////////////////////////
    m[0] = 0;
    double temps;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
            if (temp[j] > temp[j + 1])
            {
                temps = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = temps;
            }
    }
    ////////////////////////////////////////////////////////

    for (int k = 1; k < n; k++)
    {
        for (int l = 0; l < n; l++)
        {
            if (temp[k] == Priority[l])
                m[k] = l;
        }
    }

    for (int i = 1; i < n; i++)
    {
        if ((ArrivalTime[m[i]] - FinishTime[m[i - 1]]) > 0)
        {
            FinishTime[m[i]] = ArrivalTime[m[i]] + ServiceTime[m[i]];
        }
        else
        {
            FinishTime[m[i]] = FinishTime[m[i - 1]] + ServiceTime[m[i]];
        }
    }

    for (int i = 0; i < n; i++)
    {
        WholeTime[i] = FinishTime[i] - ArrivalTime[i];
        WeightWholeTime[i] = (double)WholeTime[i] / (double)ServiceTime[i];
        WT = WT + WholeTime[i];
        WWT = WWT + WeightWholeTime[i];
        cout << "\t" << setprecision(3) << i + 1 << "\t\t" << setprecision(3) << ArrivalTime[i] << "\t\t" << setprecision(3) << FinishTime[i] << "\t\t" << setprecision(3) << WholeTime[i] << "\t\t" << setprecision(3) << WeightWholeTime[i];
        cout << endl;
    }
    cout << endl;
    AverageWWT = WWT / n;
    AverageWT = WT / n;
    cout << "平均周转时间为：        " << setprecision(3) << AverageWT << endl;
    cout << "平均带权周转时间为:     " << setprecision(3) << AverageWWT << endl;
    cout << "执行顺序：";
    for (int i = 0; i < n - 1; i++)
    {
        cout << m[i] + 1 << " -> ";
    }
    cout << m[n - 1] + 1;
    WT = 0;  //WT和WWT最后要置零，因为单独把计算周转时间等作为一个函数
    WWT = 0; //如果不置零将导致后续引用该函数的出错
    cout << endl;
}

int main(void)
{
    int n;
    int k;
    cout << "请输入进程的数量n：";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "请输入进程" << i + 1 << "的到达时间,服务时间和优先级，并以空格间隔:";
        cin >> ArrivalTime[i];
        cin >> ServiceTime[i];
        cin >> Priority[i];
    }
    cout << endl;
    cout << "1.FCFS算法  ";
    cout << "2.SJF算法  ";
    cout << "3.HRN算法  ";
    cout << "4.优先级算法\n";
    while (1)
    {
        cout << endl;
        cout << "请输入要执行的算法：";
        cin >> k;
        cout << endl;
        switch (k)
        {
        case 1:
            FCFS(n);
            break;
        case 2:
            SJF(n);
            break;
        case 3:
            HRN(n);
            break;
        case 4:
            PriorityFunction(n);
            break;
        case 0:
            cout << "程序已退出！" << endl;
            goto s;
            break;
        default:
            cout << "输入错误，请重新输入！" << endl;
        }
    }
s:
    return 0;
}
