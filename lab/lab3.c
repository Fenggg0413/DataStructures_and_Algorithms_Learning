#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4  //元素不存在
#define Duplicate 5  //元素重复
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;

typedef struct mGraph
{
    ElemType **adjMat; //邻接矩阵
    int vertexNums;  //图的当前顶点数
    int edges;  //图的当前边数
    ElemType noEdge; //两顶点间无边时的值
} MGraph;

// 邻接矩阵的初始化
Status Init(MGraph *mg, int nsize, ElemType noEdgeValue)
{
    mg->vertexNums = nsize;
    mg->edges = 0;
    mg->noEdge = noEdgeValue;
    mg->adjMat = (ElemType **)malloc(nsize * sizeof(ElemType *));
    if(!mg->adjMat) //如果内存分配失败
        return ERROR;
    for (int i = 0; i < mg->vertexNums; ++i)
    {
        mg->adjMat[i] = (ElemType *)malloc(nsize * sizeof(ElemType));
        for (int j = 0; j < mg->vertexNums; ++j)
        {
            mg->adjMat[i][j] = 0;
        }
    }
    return OK;
}

// 销毁邻接矩阵避免内存泄漏
void Destroy(MGraph *mg)
{
    for (int i = 0; i < mg->vertexNums; ++i)
        free(mg->adjMat[i]);
    free(mg->adjMat);
}

// 搜索节点u到v之间是否存在边
Status Searchedge(MGraph *mg, int u, int v)
{
    if(u < 0 || v < 0 || u > mg->vertexNums-1 || v > mg->vertexNums-1 || u == v || mg->adjMat[u][v] == mg->noEdge)
        return ERROR;
    return OK;
}

// 插入边
Status Insert(MGraph *mg, int u, int v, ElemType w)
{
    if (u < 0 || v < 0 || u > mg->vertexNums - 1 || v > mg->vertexNums - 1 || u == v)
        return ERROR;
    if(mg->adjMat[u][v] != mg->noEdge)
        return Duplicate;
    mg->adjMat[u][v] = w;
    mg->edges++;
    return OK;
}

// 删除边
Status Remove(MGraph *mg, int u, int v)
{
    if (u < 0 || v < 0 || u > mg->vertexNums - 1 || v > mg->vertexNums - 1 || u == v)
        return ERROR;
    if (mg->adjMat[u][v] == mg->noEdge)
        return NotPresent;
    mg->adjMat[u][v] = mg->noEdge;
    mg->edges--;
    return OK;
}

typedef struct eNode
{
    int adjVex;  //邻接节点
    ElemType w;  //边的权值
    struct eNode *next; 
} ENode;
typedef struct lGraph
{
    int vertexNums;
    int edges;
    ENode **a;  
};

// 深度优先搜索
void dfs(int isVisited[], MGraph *mg, int i)
{
    isVisited[i] = TRUE;
    printf("%d ", i);
    for (int j = 0; j < mg->vertexNums; ++j)
        if(!isVisited[j] && mg->adjMat[i][j] != mg->noEdge) // 如果对于顶点j没有访问过, 并且顶点i到j之间存在边
            dfs(isVisited, mg, j);
}
void dfsTraverse(MGraph *mg)
{
    int *isVisited = (int *)malloc(mg->vertexNums * sizeof(int));
    for (int i = 0; i < mg->vertexNums; ++i)
        isVisited[i] == FALSE;
    for (int i = 0; i < mg->vertexNums; ++i)
        if(!isVisited[i])
            dfs(isVisited, mg, i);
    free(isVisited);
}
