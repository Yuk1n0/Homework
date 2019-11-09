#include<iostream>
#include<iomanip>
#include<math.h>
using namespace std;

const int MaxNumber = 100;
int  TrackOrder[MaxNumber];
int  MoveDistance[MaxNumber];    //----�ƶ�����;
int  FindOrder[MaxNumber];       //-----Ѱ�����С�
double  Distance;                //-----ƽ��Ѱ������
bool direction;                  //-----����   trueʱΪ���⣬falseΪ����
int BeginNum;                    //----��ʼ�ŵ��š�
int M;                           //----�ŵ�����
int N;                           //-----�������I/O����Ľ�����
int SortOrder[MaxNumber];        //----����������
bool Finished[MaxNumber];

void Init()
{
    cout << "������ŵ�����";
    cin >> M;
    cout << "�������������I/O����Ľ�����:";
    cin >> N;
    cout << "����������Ҫ���ʵĴŵ��ţ�";
    for (int i = 0; i < N; i++)
        cin >> TrackOrder[i];
    for (int j = 0; j < N; j++)
        MoveDistance[j] = 0;
    cout << "�����뿪ʼ�ŵ��ţ�";
    cin >> BeginNum;
    for (int k = 0; k < N; k++)
        Finished[k] = false;
    for (int l = 0; l < N; l++)
        SortOrder[l] = TrackOrder[l];
}

//=====================��������������������Ĵŵ�����С��������=================
void Sort()
{                 //------ð������
    int temp;
    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (SortOrder[j] > SortOrder[j + 1])
            {
                temp = SortOrder[j];
                SortOrder[j] = SortOrder[j + 1];
                SortOrder[j + 1] = temp;
            }
        }
    }
}

//============FCFS,�����ȷ���=================================
void FCFS()
{
    int temp;
    temp = BeginNum;                   //--------��BeginNum����temp��ΪѰ��ʱ�ĵ�ǰ���ڴŵ���
    for (int i = 0; i < N; i++)
    {
        MoveDistance[i] = abs(TrackOrder[i] - temp);        //-------�����ƶ��ŵ���
        temp = TrackOrder[i];                             //-------Ѱ���󣬽��˵���Ϊ��ǰ���ڴŵ��ţ�����temp
        FindOrder[i] = TrackOrder[i];                     //-----Ѱ�õĸ���Ѱ������
    }
}

//========SSTF,���Ѱ����=============================
void SSTF()
{
    int temp, n;
    int A = M;
    temp = BeginNum;                  //--------��BeginNum����temp��ΪѰ��ʱ�ĵ�ǰ���ڴŵ���
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)                 //-------Ѱ����̵�Ѱ������
        {
            if (abs(TrackOrder[j] - temp) < A && Finished[j] == false)
            {
                A = abs(TrackOrder[j] - temp);
                n = j;
            }
            else continue;
        }
        Finished[n] = true;            //-------���Ѿ�Ѱ�ҵ���Finished��ֵΪtrue
        MoveDistance[i] = A;           //-------Ѱ������
        temp = TrackOrder[n];          //-------��ǰѰ���š�
        A = M;                         //-----����Aֵ
        FindOrder[i] = TrackOrder[n];  //----Ѱ�õĸ���Ѱ������
    }
}

//=====================SCAN,ɨ���㷨==========================
void SCAN()
{
    int m, n, temp;
    temp = BeginNum;
    Sort();                                      //------����
    cout << "��ѡ��ʼ����1--����;2---����    Select:";    //------ѡ��ɨ�跽��
    cin >> m;
    if (m == 1)
        direction = false;
    else if (m == 2)
        direction = true;
    else
        cout << "�������";
    for (int i = 0; i < N; i++)
    {
        if (SortOrder[i] < BeginNum)
            continue;
        else
        {
            n = i;
            break;
        }
    }
    if (direction == true)                     //------ѡ������
    {
        for (int i = n; i < N; i++)
        {
            MoveDistance[i - n] = abs(SortOrder[i] - temp);
            temp = SortOrder[i];
            FindOrder[i - n] = SortOrder[i];
        }
        for (int j = n - 1; j >= 0; j--)
        {
            MoveDistance[N - 1 - j] = abs(SortOrder[j] - temp);
            temp = SortOrder[j];
            FindOrder[N - 1 - j] = SortOrder[j];
        }
    }
    else                                  //-------ѡ������
    {
        for (int i = n - 1; i >= 0; i--)//i=1
        {
            MoveDistance[abs(i + 1 - n)] = abs(SortOrder[i] - temp);
            temp = SortOrder[i];
            FindOrder[abs(i + 1 - n)] = SortOrder[i];
        }
        for (int j = n; j < N; j++)
        {
            MoveDistance[j] = abs(SortOrder[j] - temp);
            temp = SortOrder[j];
            FindOrder[j] = SortOrder[j];
        }
    }
}

//=================CSCAN,ѭ��ɨ���㷨=======================
void CSCAN()
{
    int m, n, temp;
    temp = BeginNum;
    Sort();
    cout << "��ѡ��ʼ����1--����;2--����    Select:";
    cin >> m;
    if (m == 1)
        direction = false;
    else if (m == 2)
        direction = true;
    else
        cout << "�������";
    for (int i = 0; i < N; i++)
    {
        if (SortOrder[i] < BeginNum)
            continue;
        else
        {
            n = i;
            break;
        }
    }
    if (direction == true)
    {
        for (int i = n; i < N; i++)
        {
            MoveDistance[i - n] = abs(SortOrder[i] - temp);
            temp = SortOrder[i];
            FindOrder[i - n] = SortOrder[i];
        }
        for (int j = 0; j < n; j++)
        {
            MoveDistance[N - n + j] = abs(SortOrder[j] - temp);
            temp = SortOrder[j];
            FindOrder[N - n + j] = SortOrder[j];
        }
    }
    else
    {
        for (int i = n - 1; i >= 0; i--)
        {
            MoveDistance[n - 1 - i] = abs(SortOrder[i] - temp);
            temp = SortOrder[i];
            FindOrder[n - 1 - i] = SortOrder[i];
        }
        for (int j = N - 1; j >= n; j--)
        {
            MoveDistance[N - j + n - 1] = abs(SortOrder[j] - temp);
            temp = SortOrder[j];
            FindOrder[N - j + n - 1] = SortOrder[j];
        }
    }
}

//========����Ѱ��ʱ��==============
void Count()
{
    int Total = 0;
    for (int i = 0; i < N; i++)
    {
        Total += MoveDistance[i];
    }
    Distance = ((double)Total);
}

void Show()
{
    cout << "================��" << BeginNum << "�Ŵŵ���ʼ=====================" << endl;
    cout << setw(20) << "�����ʵ���һ���ŵ���" << setw(20) << "�ƶ�����(�ŵ���)" << endl;
    for (int i = 0; i < N; i++)
    {
        cout << setw(15) << FindOrder[i] << setw(15) << MoveDistance[i] << endl;
    }
    cout << setw(20) << "��Ѱ������:" << Distance << endl;
    cout << endl;
}

int main(void)
{
    bool y = true;
    int s;
    Init();
    while (y)
    {
        cout << "��ѡ��Ѱ����ʽ��1--FCFS; 2--SSTF; 3--SCAN    Select:";
        cin >> s;
        switch (s)
        {
            case 1:FCFS(); Count(); Show(); break;
            case 2:SSTF(); Count(); Show(); break;
            case 3:SCAN(); Count(); Show(); break;
        }
        cout << "�Ƿ����ѡ��Ѱ���㷨��1.�ǣ�2.��    Select:";
        int p;
        cin >> p;
        if (p == 1)
            y = true;
        else if (p == 2)
            y = false;
        else
            cout << "�������" << endl;
    }
    return 0;
}
