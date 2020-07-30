#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Graph.h"
using namespace std;

#define F_PATH1 "Vex.txt"
#define F_PATH2 "Edge.txt"

void CGraph::init()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            m_aAdjMatrix[i][j] = 0;
        }
    }

    for (int k = 0; k < 20; k++)
    {
        m_aVex[k].num = k;
        strcpy(m_aVex[k].name, " ");
        strcpy(m_aVex[k].desc, " ");
    }

    m_nVexNum = 0;
}

bool CGraph::insertVex(Vex sVex)
{
    if (m_nVexNum == MAX_VERTEX_NUM)
    {
        return false; //顶点已满
    }
    m_aVex[m_nVexNum] = sVex;
    m_nVexNum = m_nVexNum + 1;
    return true;
}

bool CGraph::insertEdge(Edge sEdge)
{
    if (sEdge.vex1 < 0 || sEdge.vex1 >= MAX_VERTEX_NUM || sEdge.vex2 < 0 || sEdge.vex2 >= MAX_VERTEX_NUM)
    {
        return false; //下标越界
    }
    m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
    m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
    return true;
}

Vex CGraph::GetVex(int v)
{
    return m_aVex[v];
}

int CGraph::FindEdge(int v, Edge aEdge[])
{
    int k = 0;
    for (int i = 0; i < m_nVexNum; i++)
    {
        if (m_aAdjMatrix[v][i] != 0)
        {
            aEdge->vex1 = m_aVex[v].num;
            aEdge->vex2 = m_aVex[i].num;
            aEdge->weight = m_aAdjMatrix[v][i];
            k++;
            Vex vex1, vex2;
            vex1 = GetVex(aEdge->vex1);
            vex2 = GetVex(aEdge->vex2);
            cout << vex1.name << "->" << vex2.name << "  " << m_aAdjMatrix[v][i] << endl;
        }
    }
    return k;
}

int CGraph::GetVexnum(void)
{
    return m_nVexNum;
}

void CGraph::DFS(int nVex, bool bVisit[], int &nIndex, PathList &pList) //输入参数：nVex顶点编号，aVisit[]记录某个顶点是否被遍历过，&nIndex记录遍历深度。输出参数：&pList遍历得到的结果
{
    bVisit[nVex] = true;
    pList->vexs[nIndex++] = nVex;
    for (int i = 0; i < m_nVexNum; i++)
    {
        if (i == nVex)
        {
            continue;
        }
        if (m_aAdjMatrix[nVex][i] > 0 && !bVisit[i])
        {
            cout << nVex << "  " << i << "  ";
            cout << m_aAdjMatrix[nVex][i] << endl;
            DFS(i, bVisit, nIndex, pList);
        }
    }
}

void CGraph::DFSs(int nVex, bool bVisit[], int &nIndex, PathList &pList)
{
    bVisit[nVex] = true;
    pList->vexs[nIndex++] = nVex;
    int nVexnum = 0;
    for (int i = 0; i < m_nVexNum; i++)
    {
        if (bVisit[i])
            nVexnum++;
    }
    if (nVexnum == m_nVexNum)
    {
        pList->next = (PathList)malloc(sizeof(Path));
        for (int i = 0; i < m_nVexNum; i++)
        {
            pList->next->vexs[i] = pList->vexs[i];
        }
        pList = pList->next;
        pList->next = NULL;
    }
    else
    {
        for (int i = 0; i < m_nVexNum; i++)
        {
            if (i == nVex)
            {
                continue;
            }
            if (m_aAdjMatrix[nVex][i] > 0 && !bVisit[i])
            {
                DFSs(i, bVisit, nIndex, pList);
                bVisit[i] = false;
                nIndex--;
            }
        }
    }
}

void CGraph::DFSTraverse(int nVex, PathList &pList)
{
    int nIndex = 0;
    bool aVisit[MAX_VERTEX_NUM] = {false};
    DFSs(nVex, aVisit, nIndex, pList);
}

void CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge *&aEdge)
{
    int nIndex = 0;
    int temp = 0;
    bool aVisit[MAX_VERTEX_NUM] = {false};
    aVisit[nVexStart] = true;
    aEdge->vex1 = nVexStart;
    aEdge->weight = 0;
    temp = m_aAdjMatrix[nVexStart][0];
    if (m_aAdjMatrix[nVexStart][nVexEnd] > 0)
    {
        aEdge->vex2 = nVexEnd;
        aEdge->weight = m_aAdjMatrix[nVexStart][nVexEnd];
        return;
    }
    for (int i = 0; i < m_nVexNum; i++)
    {
        if (temp >= m_aAdjMatrix[nVexStart][i] && !aVisit[i])
        {
            temp = m_aAdjMatrix[nVexStart][i];
        }
    }
    int w = 0;
    for (w; w < m_nVexNum; w++)
    {
        if (m_aAdjMatrix[nVexStart][w] == temp)
        {
            break;
        }
    }
    aVisit[w] = true;
}

int CGraph::FindShortPaths(int nVexStart, int nVexEnd, Edge aEdge[])
{
    int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int nShortDistance[MAX_VERTEX_NUM];
    bool aVisit[MAX_VERTEX_NUM] = {false};
    int v;
    for (v = 0; v < m_nVexNum; v++) //初始化操作
    {
        if (m_aAdjMatrix[nVexStart][v])
        {
            nShortDistance[v] = m_aAdjMatrix[nVexStart][v]; //相连，默认为两点间距离
        }
        else
        {
            nShortDistance[v] = 0x7FFFFFFF; //不相连，min保存为最大整数
        }
        nShortPath[v][0] = nVexStart; //设置初始点
        for (int w = 1; w < m_nVexNum; w++)
        {
            nShortPath[v][w] = -1; //初始化最短路径
        }
    }
    aVisit[nVexStart] = true;
    int min;
    for (int i = 1; i < m_nVexNum; i++)
    {
        min = 0x7FFFFFFF;
        bool bAdd = false; //判断是否还有点可加入集合
        for (int w = 0; w < m_nVexNum; w++)
        {
            if (!aVisit[w])
            {
                if (nShortDistance[w] < min)
                {
                    v = w;
                    min = nShortDistance[w];
                    bAdd = true;
                }
            }
        }
        if (!bAdd) //如果没有点可加入，跳出循环
        {
            break;
        }
        aVisit[v] = true;
        nShortPath[v][i] = v;
        for (int w = 0; w < m_nVexNum; w++)
        { //以w为过渡计算起点通过w到每个顶点的距离
            if (!aVisit[w] && (min + m_aAdjMatrix[v][w] < nShortDistance[w]) && m_aAdjMatrix[v][w] != 0)
            {
                nShortDistance[w] = min + m_aAdjMatrix[v][w];
                for (int i = 0; i < m_nVexNum; i++)
                {
                    nShortPath[w][i] = nShortPath[v][i];
                }
            }
        }
    }
    //保存结构体
    int nIndex = 0;
    int nVex1 = nVexStart;
    for (int i = 1; i < m_nVexNum; i++)
    {
        if (nShortPath[nVexEnd][i] != -1)
        {
            aEdge[nIndex].vex1 = nVex1;
            aEdge[nIndex].vex2 = nShortPath[nVexEnd][i];
            aEdge[nIndex].weight = m_aAdjMatrix[aEdge[nIndex].vex1][aEdge[nIndex].vex2];
            nVex1 = nShortPath[nVexEnd][i];
            nIndex++;
        }
    }
    return nIndex;
}

void CGraph::FindMinTree(Edge aPath[])
{
    bool aVisit[MAX_VERTEX_NUM] = {false};
    aVisit[0] = true;
    int min;
    int nVex1, nVex2;
    for (int k = 0; k < m_nVexNum - 1; k++)
    {
        min = 0x7FFFFFFF;
        for (int v = 0; v < m_nVexNum; v++)
        {
            if (aVisit[v]) //从集合中取一个顶点
            {
                for (int w = 0; w < m_nVexNum; w++)
                {
                    if (!aVisit[w]) //从不在集合的顶点中取出一个顶点
                    {
                        if ((m_aAdjMatrix[v][w] < min) && (m_aAdjMatrix[v][w] != 0))
                        {
                            nVex1 = v;
                            nVex2 = w;
                            min = m_aAdjMatrix[v][w]; //找出最短的边
                        }
                    }
                }
            }
        }
        aPath[k].vex1 = nVex1;
        aPath[k].vex2 = nVex2;
        aPath[k].weight = m_aAdjMatrix[nVex1][nVex2];
        aVisit[nVex1] = true;
        aVisit[nVex2] = true;
    }
}
