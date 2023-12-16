#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define Overflow 2
#define Underflow 3
#define NotPresent 4 // 元素不存在
#define Duplicate 5  // 元素重复
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;

typedef struct mGraph
{
    ElemType **adjMat; // 邻接矩阵
    int vertexNums;    // 图的当前顶点数
    int edges;         // 图的当前边数
    ElemType noEdge;   // 两顶点间无边时的值
} MGraph;

// 邻接矩阵的初始化
Status Init(MGraph *mg, int nsize, ElemType noEdgeValue)
{
    mg->vertexNums = nsize;
    mg->edges = 0;
    mg->noEdge = noEdgeValue;
    mg->adjMat = (ElemType **)malloc(nsize * sizeof(ElemType *));
    if (!mg->adjMat) // 如果内存分配失败
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
    if (u < 0 || v < 0 || u > mg->vertexNums - 1 || v > mg->vertexNums - 1 || u == v || mg->adjMat[u][v] == mg->noEdge)
        return ERROR;
    return OK;
}

// 插入边
Status Insert(MGraph *mg, int u, int v, ElemType w)
{
    if (u < 0 || v < 0 || u > mg->vertexNums - 1 || v > mg->vertexNums - 1 || u == v)
        return ERROR;
    if (mg->adjMat[u][v] != mg->noEdge)
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

// 邻接表
typedef struct eNode
{
    int adjVex; // 邻接节点
    ElemType w; // 边的权值
    struct eNode *next;
} ENode;
typedef struct lGraph
{
    int vertexNums;
    int edges;
    ENode **a; // 顶点表, 存储的指针指向一个边表
} LGraph;

Status lGraphInit(LGraph *lg, int nsize)
{
    lg->edges = 0;
    lg->vertexNums = nsize;
    lg->a = (ENode **)malloc(nsize * sizeof(ENode *));
    if (!lg->a)
        return ERROR;
    for (int i = 0; i < nsize; ++i)
        lg->a[i] = NULL;
    return OK;
}

void lGraphDestroy(LGraph *lg)
{
    for (int i = 0; i < lg->vertexNums; ++i)
    {
        ENode *cur = lg->a[i];
        // 释放掉顶点i的单链表中所有边节点
        while (cur)
        {
            ENode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        lg->a[i] = NULL; // 将指针置空
    }
    free(lg->a); // free整个顶点数组
}

// 搜索节点u到v之间是否存在边
Status lGraphSerchEdge(LGraph *lg, int u, int v)
{
    if (u < 0 || v < 0 || u > lg->vertexNums - 1 || v > lg->vertexNums - 1 || u == v)
        return ERROR;
    ENode *cur = lg->a[u];
    while (cur && cur->adjVex != v)
        cur = cur->next;
    if (!cur)
        return ERROR;
    return OK;
}

// 在u和v之间插入边
Status lGraphInsert(LGraph *lg, int u, int v, int w)
{
    if (u < 0 || v < 0 || u > lg->vertexNums - 1 || v > lg->vertexNums - 1 || u == v)
        return ERROR;
    if (lGraphSerchEdge(lg, u, v))
        return Duplicate;
    ENode *newEdgeNode = (ENode *)malloc(sizeof(ENode));
    newEdgeNode->adjVex = v;
    newEdgeNode->w = w;
    // 头插
    newEdgeNode->next = lg->a[u];
    lg->a[u] = newEdgeNode;
    lg->edges++;
    return OK;
}

// 删除u和v之间的边
Status lGraphRemove(LGraph *lg, int u, int v)
{
    if (u < 0 || v < 0 || u > lg->vertexNums - 1 || v > lg->vertexNums - 1 || u == v)
        return ERROR;
    if (!lGraphSerchEdge(lg, u, v))
        return NotPresent;
    ENode *cur = lg->a[u];
    ENode *pre = NULL;
    while (cur && cur->adjVex != v)
    {
        pre = cur;
        cur = cur->next;
    }
    if(!cur)
        return NotPresent;
    if (pre)
        pre->next = cur->next;
    else
        lg->a[u] = cur->next;
    free(cur);
    lg->edges--;
    return OK;
}

// 深度优先搜索
void dfs(int isVisited[], LGraph *lg, int i)
{
    isVisited[i] = TRUE;
    printf("%d ", i);
    for (int j = 0; j < lg->vertexNums; ++j)
        if (!isVisited[j] && lGraphSerchEdge(lg, i, j)) // 如果对于顶点j没有访问过, 并且顶点i到j之间存在边
            dfs(isVisited, lg, j);
}
void dfsTraverse(LGraph *lg)
{
    int *isVisited = (int *)malloc(lg->vertexNums * sizeof(int));
    for (int i = 0; i < lg->vertexNums; ++i)
        isVisited[i] = FALSE;  // 初始化访问节点数组
    for (int i = 0; i < lg->vertexNums; ++i)
        if (!isVisited[i])
            dfs(isVisited, lg, i);
    printf("\n");
    free(isVisited);
}

int main()
{
    LGraph lg;
    lGraphInit(&lg, 4);
    lGraphInsert(&lg, 0, 1, 8);
    lGraphInsert(&lg, 0, 2, 8);
    lGraphInsert(&lg, 0, 3, 8);
    lGraphInsert(&lg, 1, 2, 8);
    lGraphInsert(&lg, 1, 3, 8);
    lGraphInsert(&lg, 2, 3, 8);
    if(lGraphSerchEdge(&lg, 2, 3))
        printf("节点2和节点3之间存在边\n");
    else
        printf("节点2和节点3之间不存在边\n");
    lGraphRemove(&lg, 2, 3);
    if (lGraphSerchEdge(&lg, 2, 3))
        printf("节点2和节点3之间存在边\n");
    else
        printf("节点2和节点3之间不存在边\n");
    dfsTraverse(&lg);
    lGraphRemove(&lg, 1, 3);
    lGraphRemove(&lg, 0, 3);
    dfsTraverse(&lg);
    lGraphDestroy(&lg);
    return 0;
}
