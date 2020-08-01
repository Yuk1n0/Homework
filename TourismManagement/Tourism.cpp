#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Graph.h"
using namespace std;

#define F_PATH1 "Vex.txt"
#define F_PATH2 "Edge.txt"

CGraph Graph;

void CreateGraph(void)
{
    Graph.init();
    Vex vex;
    int buf;
    FILE *fp1, *fp2;
    fp1 = fopen(F_PATH1, "r");
    fp2 = fopen(F_PATH2, "r");

    fscanf(fp1, "%d", &buf);
    while (!feof(fp1))
    {
        fscanf(fp1, "%d", &vex.num);
        fscanf(fp1, "%s", &vex.name);
        fscanf(fp1, "%s", &vex.desc);
        if (!Graph.insertVex(vex))
        {
            cout << "景点插入失败！" << endl;
            continue;
        }
    }
    cout << "=====创建景点园区图=====\n";
    cout << "顶点数目：" << buf << endl;
    cout << "======顶点======\n";
    for (int k = 0; k < buf; k++)
    {
        cout << Graph.m_aVex[k].num << "--" << Graph.m_aVex[k].name << endl;
    }

    Edge sEdge;
    cout << "=======边=======" << endl;
    while (fscanf(fp2, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != EOF)
    {
        cout << "(v" << sEdge.vex1 << "->v" << sEdge.vex2 << ")  " << sEdge.weight << endl;
        if (!Graph.insertEdge(sEdge))
        {
            cout << "边插入失败！" << endl;
            continue;
        }
    }

    fclose(fp1);
    fclose(fp2);
    fp1 = NULL;
    fp2 = NULL;
}

void GetSpotInfo(void)
{
    int i, k;
    cout << "请输入要查询的顶点编号：";
    cin >> i;
    Vex vex;
    vex = Graph.GetVex(i);
    cout << "该顶点的编号为：" << vex.num << endl;
    cout << "该顶点的名称为：" << vex.name << endl;
    cout << "该顶点的介绍为：" << vex.desc << endl;
    cout << "======周边景区======" << endl;
    Edge edge;
    k = Graph.FindEdge(i, &edge);
    cout << "共有" << k << "处周边景区\n";
}

void TravelPath(void)
{
    int nVex;
    int x = 1;
    PathList pList;
    pList = (PathList)malloc(sizeof(Path));
    cout << "请输入景区编号：";
    cin >> nVex;
    Graph.DFSTraverse(nVex, pList);
    for (x; x < Graph.m_nVexNum - 1; x++)
    {
        cout << Graph.m_aVex[pList->vexs[x]].name << "->";
    }
    cout << Graph.m_aVex[pList->vexs[x]].name << endl;
}

void TravelPaths(void)
{
    int nVex;
    PathList pList, head;
    pList = (PathList)malloc(sizeof(Path));
    head = pList;
    cout << "请输入景区编号：";
    cin >> nVex;
    Graph.DFSTraverse(nVex, pList);
    pList = head;
    int a = 1;
    while (pList->next)
    {
        cout << "路线" << a << "：";
        int x = 0;
        for (x; x < (Graph.m_nVexNum - 1); x++)
        {
            cout << Graph.m_aVex[pList->vexs[x]].name << "->";
        }
        cout << Graph.m_aVex[pList->vexs[x]].name << endl;
        PathList temp = pList;
        pList = pList->next;
        free(temp);
        a++;
    }
}

void FindShortPath(void)
{
    int nVexStart, nVexEnd;
    int num;
    cout << "=====请输入两个景点的编号=====\n";
    cout << "请输入起点编号：";
    cin >> nVexStart;
    cout << "请输入终点编号：";
    cin >> nVexEnd;
    //	Edge *aList;
    //	aList = new Edge;
    Edge aEdge[MAX_VERTEX_NUM];
    num = Graph.FindShortPaths(nVexStart, nVexEnd, aEdge);
    Vex svex = Graph.GetVex(aEdge[0].vex1);
    int length = 0;
    cout << "最短路径为：";
    cout << svex.name;
    for (int i = 0; i < num; i++)
    {
        svex = Graph.GetVex(aEdge[i].vex2);
        cout << "->" << svex.name;
        length += aEdge[i].weight;
    }
    cout << endl;
    cout << "最短距离为：" << length << endl;
}

void DesignPath(void)
{
    Edge aPath[MAX_VERTEX_NUM];
    Graph.FindMinTree(aPath);
    Vex vex1, vex2;
    int weight;
    int sum = 0;
    cout << "======铺设电路规划======\n";
    for (int i = 0; i < (Graph.GetVexnum() - 1); i++)
    {
        vex1 = Graph.GetVex(aPath[i].vex1);
        vex2 = Graph.GetVex(aPath[i].vex2);
        weight = aPath[i].weight;
        sum += aPath[i].weight;
        cout << vex1.name << "--" << vex2.name << "   " << weight << "米" << endl;
    }
    cout << "铺设电路的总长度为：" << sum << "米" << endl;
}
