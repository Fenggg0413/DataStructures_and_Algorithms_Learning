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
#define MAX 65535

typedef int Status;
typedef int ElemType;

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
    // Insert edge (u, v)
    if (lGraphSerchEdge(lg, u, v))
        return Duplicate;
    ENode *newEdgeNode1 = (ENode *)malloc(sizeof(ENode));
    newEdgeNode1->adjVex = v;
    newEdgeNode1->w = w;
    newEdgeNode1->next = lg->a[u];
    lg->a[u] = newEdgeNode1;

    // 如果为无向图, 那么对于insert(u,v)则也该有insert(v,u)
    // Insert edge (v, u)
    if (lGraphSerchEdge(lg, v, u))
        return Duplicate;
    ENode *newEdgeNode2 = (ENode *)malloc(sizeof(ENode));
    newEdgeNode2->adjVex = u;
    newEdgeNode2->w = w;
    newEdgeNode2->next = lg->a[v];
    lg->a[v] = newEdgeNode2;

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
    if (!cur)
        return NotPresent;
    if (pre)
        pre->next = cur->next;
    else
        lg->a[u] = cur->next;
    free(cur);
    lg->edges--;
    return OK;
}

// dist数组表示v到任意节点的最短距离, path数组用于存储最短路径下标的数组
void Dijkstra(LGraph *lg, int v, int dist[], int path[])
{
    int nsize = lg->vertexNums; // 顶点个数
    // visited[i] = TRUE表示求得顶点v到i的最短路径已经求出
    int *visited = (int *)malloc(nsize * sizeof(int));
    // 初始化dist数组, visited数组和path数组
    for (int i = 0; i < nsize; ++i)
    {
        visited[i] = FALSE;
        dist[i] = MAX;
        path[i] = -1;
    }
    ENode *cur = lg->a[v];
    while (cur)
    {
        dist[cur->adjVex] = cur->w;
        cur = cur->next;
    }
    dist[v] = 0; // v到v的最短路径为0
    visited[v] = TRUE;
    int t = 0;
    for (int i = 1; i < nsize; ++i)
    {
        int min = MAX;
        for (int j = 0; j < nsize; ++j) // 寻找距离v最近的顶点
        {
            if (!visited[j] && dist[j] < min)
            {
                t = j;
                min = dist[j];
            }
        }
        visited[t] = TRUE; // 找到了v到t的最短路径
        ENode *cur = lg->a[t]; // 用cur遍历t顶点的边集数组
        // min此时为顶点v到顶点t的最短路径
        // 更新dist数组, 伪代码:dist[j] = min(dist[j], min+G[t][j])
        while(cur)
        {
            if (cur && min + cur->w < dist[cur->adjVex])
            {
                dist[cur->adjVex] = min + cur->w;
                path[cur->adjVex] = t; // 表示在v到j的最短路径中, t是j的前驱
            }
            cur = cur->next;
        }
    }
    free(visited);
}

int main()
{
    LGraph lg;
    lGraphInit(&lg, 9);
    lGraphInsert(&lg, 0, 1, 1);
    lGraphInsert(&lg, 0, 2, 5);
    lGraphInsert(&lg, 1, 2, 3);
    lGraphInsert(&lg, 1, 3, 7);
    lGraphInsert(&lg, 1, 4, 5);
    lGraphInsert(&lg, 2, 4, 1);
    lGraphInsert(&lg, 2, 5, 7);
    lGraphInsert(&lg, 3, 4, 2);
    lGraphInsert(&lg, 3, 6, 3);
    lGraphInsert(&lg, 4, 6, 6);
    lGraphInsert(&lg, 4, 7, 9);
    lGraphInsert(&lg, 4, 5, 3);
    lGraphInsert(&lg, 5, 7, 5);
    lGraphInsert(&lg, 6, 7, 2);
    lGraphInsert(&lg, 6, 8, 7);
    lGraphInsert(&lg, 7, 8, 4);
    int dist[9], path[9];
    Dijkstra(&lg, 0, dist, path);
    printf("0节点到各节点的最短路径:\n");
    for (int i = 0; i < 9; ++i)
        printf("%d ", dist[i]);
    printf("\n");
    printf("各最短路径的表示:\n");
    for (int i = 0; i < 9; ++i)
        printf("%d ", path[i]);
    printf("\n");
    lGraphDestroy(&lg);
    return 0;
}