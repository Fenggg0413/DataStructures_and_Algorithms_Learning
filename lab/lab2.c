#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct btnode
{
    ElemType element;
    struct btonde *lChild;
    struct btnode *rChild;
} BTNode;

typedef struct binaryTree
{
    BTNode *root;
} BinaryTree;

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
    if(node == NULL)
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
int nodeNumber(BTNode *node, int count)
{
    if(node == NULL)
        return count;
    count = nodeNumber(node->lChild, count);
    count = nodeNumber(node->rChild, count);
    return ++count;
}
int calcBTNode(BinaryTree *bt)
{
    return nodeNumber(bt->root, 0);
}

/*计算叶节点个数*/
int leafNode(BTNode *node, int count)
{
    if(node == NULL)
        return count;
    else if (node->lChild == NULL && node->rChild == NULL)
        return ++count;
    count = leafNode(node->lChild, count);
    count = leafNode(node->rChild, count);
    return count;
}
int calcBTLeaf(BinaryTree *bt)
{
    return leafNode(bt->root, 0);
}

/*计算二叉树高度*/
int BTheight(BTNode *node)
{
    if(node == NULL)
        return 0;
    int leftHeight = BTheight(node->lChild);
    int rightHeight = BTheight(node->rChild);
    int maxHeight = leftHeight > rightHeight ? leftHeight : rightHeight;
    return ++maxHeight;
}
int calcBTheight(BinaryTree *bt)
{
    return BTheight(bt->root);
}

/*交换二叉树所有左右子树*/
BTNode *swapBinary(BTNode *node)
{
    if(node == NULL)
        return NULL;
    node->lChild = swapBinary(node->lChild);
    node->rChild = swapBinary(node->rChild);
    BTNode *tmp = node->lChild;
    node->lChild = node->rChild;
    node->rChild = tmp;
    return node;
}

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
    return 0;
}