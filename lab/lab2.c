#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

/*二叉树节点*/
typedef struct btnode
{
    ElemType element;
    struct btonde *lChild;
    struct btnode *rChild;
} BTNode;
/*二叉树*/
typedef struct binaryTree
{
    BTNode *root;
} BinaryTree;

/*哈夫曼树节点*/
typedef struct hfmTNode
{
    ElemType element; // 节点的数据
    int w;            // 节点的权值
    struct hfmTNode *lChild;
    struct hfmTNode *rChild;
} HFMTNode;
/*哈夫曼树*/
typedef struct hfmTree
{
    HFMTNode *root;
} HFMTree;

BTNode *preCreateBT(BTNode *t);
void init(BinaryTree *bt);
void preMakeTree(BinaryTree *bt);
void freeNode(BTNode *node);
void freeTree(BinaryTree *bt);
void preOrder(BTNode *node);
void inOrder(BTNode *node);
void postOrder(BTNode *node);
int nodeNumber(BTNode *node);
int calcBTNode(BinaryTree *bt);
int leafNode(BTNode *node);
int calcBTLeaf(BinaryTree *bt);
int BTheight(BTNode *node);
int calcBTheight(BinaryTree *bt);
BTNode *swapBinary(BTNode *node);
void initHFM(HFMTree *ht);
HFMTNode *createHFMTNode(ElemType e, int w);
HFMTree *createHFMTree(ElemType element[], int w[], int n);
void quick_sort(HFMTNode *nodes[], int l, int r);
void freeHFMTree(HFMTree *ht);
void freeHFMTNode(HFMTNode *node);


int main()
{
    BinaryTree bt;
    init(&bt);
    preMakeTree(&bt);
    preOrder(bt.root);
    printf("\n");
    inOrder(bt.root);
    printf("\n");
    postOrder(bt.root);
    printf("\n");
    printf("number of node: %d\n", calcBTNode(&bt));
    printf("number of leaf node: %d\n", calcBTLeaf(&bt));
    printf("height of Binary Tree: %d\n", calcBTheight(&bt));
    bt.root = swapBinary(bt.root);
    preOrder(bt.root);
    freeTree(&bt);

    printf("-----------------------------------\n");
    ElemType e[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    int w[] = {29, 9, 26, 27, 2, 23, 8, 24};
    int n = sizeof(e) / sizeof(e[0]);
    HFMTree *ht = createHFMTree(e, w, n);
    freeHFMTree(ht);
    return 0;
}

/*二叉树的前序创建*/
BTNode *preCreateBT(BTNode *t)
{
    ElemType ch;
    ch = getchar();
    if (ch == '#')
    {
        t = NULL;
    }
    else
    {
        t = (BTNode *)malloc(sizeof(BTNode));
        t->element = ch;
        t->lChild = preCreateBT(t->lChild);
        t->rChild = preCreateBT(t->rChild);
    }
    return t;
}
void preMakeTree(BinaryTree *bt)
{
    bt->root = preCreateBT(bt->root);
}

/*初始化*/
void init(BinaryTree *bt)
{
    bt->root = NULL;
}

/*清除整颗树*/
void freeNode(BTNode *node)
{
    if (node == NULL)
        return;
    freeNode(node->lChild);
    freeNode(node->rChild);
    free(node);
}
void freeTree(BinaryTree *bt)
{
    freeNode(bt->root);
}

/*前序遍历*/
void preOrder(BTNode *node)
{
    if (node == NULL)
        return;
    printf("%c ", node->element);
    preOrder(node->lChild);
    preOrder(node->rChild);
}

/*中序遍历*/
void inOrder(BTNode *node)
{
    if (node == NULL)
        return;
    inOrder(node->lChild);
    printf("%c ", node->element);
    inOrder(node->rChild);
}

/*后续遍历*/
void postOrder(BTNode *node)
{
    if (node == NULL)
        return;
    postOrder(node->lChild);
    postOrder(node->rChild);
    printf("%c ", node->element);
}

/*计算二叉树节点*/
int nodeNumber(BTNode *node)
{
    if (node == NULL)
        return 0;
    int lcount = nodeNumber(node->lChild);
    int rcount = nodeNumber(node->rChild);
    return lcount + rcount + 1;
}
int calcBTNode(BinaryTree *bt)
{
    return nodeNumber(bt->root);
}

/*计算叶节点个数*/
int leafNode(BTNode *node)
{
    if (node == NULL)
        return 0;
    else if (node->lChild == NULL && node->rChild == NULL)
        return 1;
    int lcount = leafNode(node->lChild);
    int rcount = leafNode(node->rChild);
    return lcount + rcount;
}
int calcBTLeaf(BinaryTree *bt)
{
    return leafNode(bt->root);
}

/*计算二叉树高度*/
int BTheight(BTNode *node)
{
    if (node == NULL)
        return 0;
    int leftHeight = BTheight(node->lChild);
    int rightHeight = BTheight(node->rChild);
    int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
    return ++maxHeight;
}
int calcBTheight(BinaryTree *bt)
{
    return BTheight(bt->root) - 1;
}

/*交换二叉树所有左右子树*/
BTNode *swapBinary(BTNode *node)
{
    if (node == NULL)
        return NULL;
    node->lChild = swapBinary(node->lChild);
    node->rChild = swapBinary(node->rChild);
    BTNode *tmp = node->lChild;
    node->lChild = node->rChild;
    node->rChild = tmp;
    return node;
}

/*初始化哈夫曼树*/
void initHFM(HFMTree *ht)
{
    ht->root = NULL;
}

/*创建哈夫曼树节点*/
HFMTNode *createHFMTNode(ElemType e, int w)
{
    HFMTNode *node = (HFMTNode *)malloc(sizeof(HFMTNode));
    node->element = e;
    node->w = w;
    node->lChild = NULL;
    node->rChild = NULL;
}

/*创建哈夫曼树*/
HFMTree *createHFMTree(ElemType element[], int w[], int n)
{
    // 确保有足够的数据才能建树
    if (n <= 0)
        return NULL;

    // 创建一个哈夫曼树节点数组;
    HFMTNode *nodes[n];
    for (int i = 0; i < n; ++i)
    {
        nodes[i] = createHFMTNode(element[i], w[i]);
    }

    while (n > 1)
    {
        // 每次先对哈夫曼树节点数组按照权值由小到大进行排序
        quick_sort(nodes, 0, n - 1);

        // 选出权值最小的两个节点构建新的哈夫曼树节点
        int min1 = 0, min2 = 1;
        HFMTNode *newNode = createHFMTNode(-1, nodes[min1]->w + nodes[min2]->w);
        newNode->lChild = nodes[min1];
        newNode->rChild = nodes[min2];

        // 删除用过的节点并添加新节点到节点数组
        nodes[min1] = newNode;
        nodes[min2] = nodes[n - 1];
        --n;
    }
    HFMTree *ht = (HFMTree *)malloc(sizeof(HFMTree));
    initHFM(ht);
    ht->root = nodes[0];
    return ht;
}

/*根据权值来排序*/
void quick_sort(HFMTNode *nodes[], int l, int r)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1;
    int x = nodes[(l + r) >> 1]->w;
    while (i < j)
    {
        do
        {
            ++i;
        } while (nodes[i]->w < x);
        do
        {
            --j;
        } while (nodes[j]->w > x);
        if (i < j)
        {
            HFMTNode *tmp = nodes[i];
            nodes[i] = nodes[j];
            nodes[j] = tmp;
        }
    }
    quick_sort(nodes, l, j);
    quick_sort(nodes, j + 1, r);
}

/*清除哈夫曼树*/
void freeHFMTNode(HFMTNode *node)
{
    if(node == NULL)
        return;
    freeHFMTNode(node->lChild);
    freeHFMTNode(node->rChild);
    free(node);
}
void freeHFMTree(HFMTree *ht)
{
    freeHFMTNode(ht->root);
}