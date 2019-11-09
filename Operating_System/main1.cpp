#include<iostream>  
#include<iomanip>  
using namespace std;

static const int MaxNum = 100;
double  ArrivalTime[MaxNum];
double  ServiceTime[MaxNum];
double  FinishTime[MaxNum];
int Priority[MaxNum];
double  WholeTime[MaxNum];
double  WeightWholeTime[MaxNum];
double AverageWT, AverageWWT;
double WT, WWT;

void FCFS(int n)
{
    double min = 5000.0;
    int m[MaxNum] = { 0 };
    cout << endl;
    cout << "FCFS:" << endl;
    cout << "   ����ID" << "         ����ʱ��" << "         ���ʱ��" << "         ��תʱ��" << "      ��Ȩ��תʱ��" << endl;
    //���ʱ�����  
    
    FinishTime[0] = ArrivalTime[0] + ServiceTime[0];
    double temp[MaxNum] = { 0 };
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
        double t = 0.0;
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
    cout << "ƽ����תʱ��Ϊ��        " << setprecision(3) << AverageWT << endl;
    cout << "ƽ����Ȩ��תʱ��Ϊ:     " << setprecision(3) << AverageWWT << endl;
    cout << "ִ��˳��";
    for (int i = 0; i < n - 1; i++)
    {
        cout << m[i] + 1 << " -> ";
    }
    cout << m[n - 1] + 1;
    WT = 0;                         //WT��WWT���Ҫ���㣬��Ϊ�����Ѽ�����תʱ�����Ϊһ������  
    WWT = 0;                        //��������㽫���º������øú����ĳ���  
    cout << endl;
}

void SJF(int n)
{
    cout << endl;
    cout << "SJF(����ռʽ):" << endl;
    cout << "   ����ID" << "         ����ʱ��" << "         ���ʱ��" << "         ��תʱ��" << "      ��Ȩ��תʱ��" << endl;
    double min = 5000.0;
    int m[MaxNum] = { 0 };
    
    bool judge = false;;
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
        double temp[MaxNum] = { 0 };
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
            double t = 0.0;
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
        cout << "ƽ����תʱ��Ϊ��        " << setprecision(3) << AverageWT << endl;
        cout << "ƽ����Ȩ��תʱ��Ϊ:     " << setprecision(3) << AverageWWT << endl;
        cout << "ִ��˳��";
        for (int i = 0; i < n - 1; i++)
        {
            cout << m[i] + 1 << " -> ";
        }
        cout << m[n - 1] + 1;
        WT = 0;                         //WT��WWT���Ҫ���㣬��Ϊ�ҵ����Ѽ�����תʱ�����Ϊһ������  
        WWT = 0;                        //��������㽫���º������øú����ĳ���  
        cout << endl;
    }
    else
    {
        
    }
}

void HRN(int n)
{
    double min = 5000.0;
    int m[MaxNum] = { 0 }; m[0] = 0;
    double ResponseRatio[MaxNum] = { 600000.0 };
    cout << endl;
    cout << "HRN:" << endl;
    cout << "   ����ID" << "         ����ʱ��" << "         ���ʱ��" << "         ��תʱ��" << "      ��Ȩ��תʱ��" << endl;
    FinishTime[0] = ArrivalTime[0] + ServiceTime[0];  //�����һ�����̵���ֹʱ��
    double temp[MaxNum] = { 0 };
    int var = 0; double a = 500000.0;
    for (int i = 1; i < n - 1; i++)
    {
        //����ÿ��ִ����һ�����̵���ʱ��ʣ��������̵���Ӧ�ȣ����ý����Ѽ�����������
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
        //temp���鿽�� ResponseRatio������Ӧ���������Ϣ
        for (int k = 0; k < n; k++)
        {
            temp[k] = ResponseRatio[k];
        }
        //����Ӧ������ð�������ɴ�С����
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
        //���ź������Ӧ��������ж�Ӧ�������кõĽ���˳��һһ��Ӧ����������˳�򱣴�զm������
        for (int x1 = 0; x1 < n; x1++)
        {
            for (int x2 = 0; x2 < n; x2++)
            {
                if (temp[x1] == ResponseRatio[x2])
                    m[x1] = x2;
            }
        }
        var = m[i];
        //������һ��������̵���ֹʱ�䣬���ý��̵ĵ���ʱ�����һ�����̵���ֹʱ�仹Ҫ���������ֹʱ��Ϊ�ý��̵���ʱ��+��Ӧʱ��
        double t = 0.0;
        if ((ArrivalTime[m[i]] - FinishTime[m[i - 1]]) > 0)
        {
            FinishTime[m[i]] = ArrivalTime[m[i]] + ServiceTime[m[i]];
        }
        else
        {
            FinishTime[m[i]] = FinishTime[m[i - 1]] + ServiceTime[m[i]];
        }
    }
    //�������һ���������ֹʱ��
    int x3 = n - 1;
    if ((ArrivalTime[m[x3]] - FinishTime[m[x3 - 1]]) > 0)
    {
        FinishTime[m[x3]] = ArrivalTime[m[x3]] + ServiceTime[m[x3]];
    }
    else
    {
        FinishTime[m[x3]] = FinishTime[m[x3 - 1]] + ServiceTime[m[x3]];
    }
    //������̵��Ƚ�����ÿ�����̵���תʱ����ƽ����תʱ�䣬�������������̵�ƽ����תʱ���ƽ����Ȩ��תʱ��
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
    cout << "ƽ����תʱ��Ϊ��        " << setprecision(3) << AverageWT << endl;
    cout << "ƽ����Ȩ��תʱ��Ϊ:     " << setprecision(3) << AverageWWT << endl;
    cout << "ִ��˳��";
    for (int i = 0; i < n - 1; i++)
    {
        cout << m[i] + 1 << " -> "; //�������˳��
    }
    cout << m[n - 1] + 1;
    WT = 0;                         //WT��WWT���Ҫ���㣬��Ϊ�����Ѽ�����תʱ�����Ϊһ������  
    WWT = 0;                        //��������㽫���º������øú����ĳ���  
    cout << endl;
}

void PriorityFunction(int n)
{
    double min = 5000.0;
    int m[MaxNum] = { 0 };
    cout << endl;
    cout << "���ȼ��㷨:" << endl;
    cout << "   ����ID" << "         ����ʱ��" << "         ���ʱ��" << "         ��תʱ��" << "      ��Ȩ��תʱ��" << endl;
    
    //���ʱ�����  
    FinishTime[0] = ArrivalTime[0] + ServiceTime[0];
    double temp[MaxNum] = { 0 };
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
        double t = 0.0;
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
    cout << "ƽ����תʱ��Ϊ��        " << setprecision(3) << AverageWT << endl;
    cout << "ƽ����Ȩ��תʱ��Ϊ:     " << setprecision(3) << AverageWWT << endl;
    cout << "ִ��˳��";
    for (int i = 0; i < n - 1; i++)
    {
        cout << m[i] + 1 << " -> ";
    }
    cout << m[n - 1] + 1;
    WT = 0;                         //WT��WWT���Ҫ���㣬��Ϊ�����Ѽ�����תʱ�����Ϊһ������  
    WWT = 0;                        //��������㽫���º������øú����ĳ���  
    cout << endl;
}

int main(void)
{
    int n;
    int k;
    cout << "��������̵�����n��";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "���������" << i + 1 << "�ĵ���ʱ��,����ʱ������ȼ������Կո���:";
        cin >> ArrivalTime[i];
        cin >> ServiceTime[i];
        cin >> Priority[i];
    }
    cout << endl;
    cout << "1.FCFS�㷨  ";
    cout << "2.SJF�㷨  ";
    cout << "3.HRN�㷨  ";
    cout << "4.���ȼ��㷨\n";
    while (1)
    {
        cout << endl;
        cout << "������Ҫִ�е��㷨��"; cin >> k;
        cout << endl;
        switch (k)
        {
            case 1: FCFS(n); break;
            case 2:SJF(n); break;
            case 3:HRN(n); break;
            case 4:PriorityFunction(n); break;
            case 0:cout << "�������˳���" << endl; goto s; break;
            default:cout << "����������������룡" << endl;
        }
    }
    s:	system("pause");
    return 0;
}
