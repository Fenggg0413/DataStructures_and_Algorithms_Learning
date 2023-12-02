#include <stdio.h>

typedef int ElemType;

typedef struct mGraph
{
    ElemType **a; //邻接矩阵
    int n;  //图的当前顶点数
    int e;  //图的当前边数
    ElemType noEdge; //两顶点间无边时的值
} MGraph;


