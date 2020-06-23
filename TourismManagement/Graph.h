#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTEX_NUM 20
struct Vex
{
    int num;         //景点编号
    char name[20];   //景点名字
    char desc[1024]; //景点介绍
};

struct Edge
{
    int vex1;   //边的第一个顶点
    int vex2;   //边的第二个顶点
    int weight; //权值
};

typedef struct Path
{
    int vexs[20]; //保存一条路径
    Path *next;   //保存下一条路径
} * PathList;

class CGraph
{
public:
    void init(void);
    bool insertVex(Vex sVex);
    bool insertEdge(Edge sEdge);
    Vex GetVex(int v);
    int FindEdge(int v, Edge aEdge[]);
    int GetVexnum(void);
    void DFS(int nVex, bool bVisit[], int &nIndex, PathList &pList);
    void DFSs(int nVex, bool bVisit[], int &nIndex, PathList &pList);
    void DFSTraverse(int nVex, PathList &pList);
    void FindShortPath(int nVexStart, int nVexEnd, Edge *&aEdge);
    int FindShortPaths(int nVexStart, int nVexEnd, Edge aEdge[]);
    void FindMinTree(Edge aPath[]);

public:
    int m_aAdjMatrix[20][20]; //邻接矩阵,显示点间长度
    Vex m_aVex[20];           //顶点数组
    int m_nVexNum;            //顶点个数
};

#endif // !GRAPH_H
