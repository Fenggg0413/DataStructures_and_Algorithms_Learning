#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define Overflow 2   // 上溢
#define Underflow 3  // 下溢
#define NotPresent 4 // 元素不存在
#define Duplicate 5  // 有重复元素

typedef int Status;   // 状态
typedef int ElemType; // 自定义类型

// 顺序表的定义
typedef struct
{
    int n;
    int maxLength;
    ElemType *element;
} SeqList;

// 顺序表的初始化
Status init(SeqList *L, int mSize)
{
    L->maxLength = mSize;
    L->n = 0;
    L->element = (ElemType *)malloc(sizeof(ElemType) * mSize);
    if (!L->element)
        return ERROR;
    return OK;
}

// 顺序表的查找
Status find(SeqList L, int i, ElemType *x)
{
    if (i < 0 || i > L.n - 1)
        return ERROR;
    *x = L.element[i];
    return OK;
}

// 顺序表的元素插入
Status insert(SeqList *L, int i, ElemType x)
{
    if (i < -1 || i > L->n - 1)
        return ERROR;
    if (L->n == L->maxLength)
        return ERROR;
    for (int j = L->n - 1; j > i; j--)
    {
        L->element[j + 1] = L->element[j];
    }
    L->element[i + 1] = x;
    L->n++;
    return OK;
}

// 顺序表的元素删除
Status delete(SeqList *L, int i)
{
    if (i < -1 || i > L->n - 1)
        return ERROR;
    if (!L->n)
        return ERROR;
    for (int j = i + 1; j < L->n; j++)
    {
        L->element[j - 1] = L->element[j];
    }
    L->n--;
    return OK;
}

// 顺序表的输出
Status output(SeqList *L)
{
    if (!L->n)
        return ERROR;
    for (int i = 0; i < L->n; i++)
    {
        printf("%d ", L->element[i]);
    }
    printf("\n");
    return OK;
}

// 顺序表的撤销
Status destroy(SeqList *L)
{
    L->n = 0;
    L->maxLength = 0;
    free(L->element);
    return OK;
}

// 链表节点定义
typedef struct node
{
    ElemType element;
    struct node *next;
} Node;

// 链表定义
typedef struct LinkList
{
    Node *dummyhead; // 虚拟头节点
    int n;
} LinkList;

// 链表初始化
Status LinkListInit(LinkList *L)
{
    L->n = 0;
    L->dummyhead = (Node *)malloc(sizeof(Node));
    L->dummyhead->next = NULL;
    L->dummyhead->element = 0;
    return OK;
}

// 链表元素的查找
Status LinkListFind(LinkList *L, int i, ElemType *x)
{
    if (i < 0 || i > L->n - 1)
        return ERROR;
    Node *cur = L->dummyhead->next;
    while (i--)
        cur = cur->next;
    *x = cur->element;
    return OK;
}

// 链表元素的插入
Status LinkListInsert(LinkList *L, int i, ElemType x)
{
    if (i > L->n)
        return ERROR;
    if (i < 0) // i<0相当于头插
        i = 0;
    Node *cur = L->dummyhead;
    while (i--)
        cur = cur->next;
    Node *q = (Node *)malloc(sizeof(Node));
    q->element = x;
    q->next = cur->next;
    cur->next = q;
    L->n++;
    return OK;
}

// 链表元素的删除
Status LinkListDelete(LinkList *L, int i)
{
    if (i < 0 || i > L->n - 1)
        return ERROR;
    Node *cur = L->dummyhead;
    while (i--)
    {
        cur = cur->next;
    }
    Node *temp = cur->next;
    cur->next = cur->next->next;
    free(temp);
    temp = NULL;
    L->n--;
    return OK;
}

// 链表的输出
Status LinkListOutput(LinkList *L)
{
    if (!L->n)
        return ERROR;
    Node *cur = L->dummyhead->next;
    while (cur)
    {
        printf("%d ", cur->element);
        cur = cur->next;
    }
    printf("\n");
    return OK;
}

// 链表的撤销
Status LinkListDestroy(LinkList *L)
{
    L->n = 0;
    Node *cur;
    while (cur)
    {
        cur = L->dummyhead->next;
        free(L->dummyhead);
        L->dummyhead = cur;
    }
    return OK;
}

// 链表的逆置
Status reverse(LinkList *L)
{
    if (!L->n)
        return ERROR;
    Node *cur = L->dummyhead->next;
    Node *tmp = cur;
    Node *head = L->dummyhead;
    head = NULL;
    while (cur)
    {
        cur = cur->next;
        tmp->next = head;
        head = tmp;
        tmp = cur;
    }
    L->dummyhead->next = head;
    return OK;
}

// 链表的排序
Status sort(LinkList *L)
{
    if (!L->n)
        return ERROR;
    Node *min, *cur, *tmp;
    tmp = L->dummyhead;
    for (int i = 0; i < L->n - 1; i++)
    {
        tmp = tmp->next;
        min = tmp;
        cur = tmp;
        for (int j = i; j < L->n; j++)
        {
            if (cur->element < min->element)
                min = cur;
            cur = cur->next;
        }
        // 将每次找到的最小值交换到暂存节点处
        ElemType val = min->element;
        min->element = tmp->element;
        tmp->element = val;
    }
    return OK;
}

// 多项式计算
typedef struct pNode
{
    int coef;
    int exp;
    struct pNode *next;
} PNode;

typedef struct polynominal
{
    PNode *head;
} Polynominal;

// 多项式的创建
void create(Polynominal *p)
{
    PNode *pn, *pre, *cur;
    p->head = (PNode *)malloc(sizeof(PNode));
    p->head->exp = -1;
    p->head->next = p->head;
    for (;;)
    {
        pn = (PNode *)malloc(sizeof(PNode));
        printf("系数: ");
        scanf("%d", &pn->coef);
        printf("指数: ");
        scanf("%d", &pn->exp);
        if (pn->exp < 0) // 当出现输入指数为负数时，多项式创建结束
            break;
        pre = p->head;
        cur = p->head->next;
        while (cur && cur->exp > pn->exp)
        {
            pre = cur;
            cur = cur->next;
        }
        pn->next = cur;
        pre->next = pn;
    }
}

// 多项式的输出
void printInfo(Polynominal *p)
{
    PNode *cur = p->head->next;
    while (cur != p->head)
    {
        if (cur->coef != 0)
        {
            if (cur->exp != 0)
            {
                // 系数为1或-1时省略
                if (cur->coef == 1) 
                {
                    // 指数为1时省略
                    if(cur->exp == 1)
                        printf("X");
                    else
                        printf("X^%d", cur->exp);
                }
                else if (cur->coef == -1)
                {
                    // 指数为1时省略
                    if(cur->exp == 1)
                        printf("X");
                    else
                        printf("-X^%d", cur->exp);
                }
                else
                {
                    // 指数为1时省略
                    if(cur->exp == 1)
                        printf("%dX", cur->coef);
                    else
                        printf("%dX^%d", cur->coef, cur->exp);
                }
            }
            else
                printf("%d", cur->coef);
            PNode *flag = cur->next;
            if (flag != p->head)
            {
                if (flag->coef > 0)
                    printf("+");
            }
        }
        cur = cur->next;
    }
    printf("\n");
}

// 多项式的撤销
void destroyPoly(Polynominal *p)
{
    PNode *cur = p->head->next;
    while (cur != p->head)
    {
        PNode *tmp = cur;
        cur = cur->next;
        free(tmp);
        tmp = NULL;
    }
    free(p->head);
    p->head = NULL;
}

// 多项式加法
void addPoly(Polynominal *px, Polynominal *qx)
{
    PNode *p, *q1, *q;
    p = px->head->next;
    q1 = qx->head;
    q = qx->head->next;
    while (p && p != px->head)
    {
        while (p->exp < q->exp)
        {
            q1 = q;
            q = q->next;
        }
        if (p->exp == q->exp)
        {
            q->coef = q->coef + p->coef;
            if (q->coef == 0)
            {
                q1->next = q->next;
                free(q);
                q = q1->next;
                p = p->next;
            }
            else
            {
                q1 = q;
                q = q->next;
                p = p->next;
            }
        }
        else
        {
            PNode *temp = (PNode *)malloc(sizeof(PNode));
            temp->coef = p->coef;
            temp->exp = p->exp;
            temp->next = q1->next;
            q1->next = temp;
            q1 = q1->next;
            p = p->next;
        }
    }
}

// 在多项式中插入节点
void insertPoly(Polynominal *p, int c, int e)
{
    PNode *cur = p->head->next;
    while (cur != p->head)
    {
        if (cur->exp == e)
        {
            // 如果插入的是指数相同的节点则系数相加
            cur->coef += c;
            return;
        }
        cur = cur->next;
    }

    // 如果没有指数相同的节点，则按照指数降序的顺序插入一个新节点
    PNode *pn = (PNode *)malloc(sizeof(PNode));
    pn->coef = c;
    pn->exp = e;
    PNode *pre = p->head;
    cur = p->head->next;
    while (cur && cur->exp > pn->exp)
    {
        pre = cur;
        cur = cur->next;
    }
    pn->next = cur;
    pre->next = pn;
}

// 多项式乘法
Polynominal multiplyPoly(Polynominal *px, Polynominal *qx)
{
    PNode *p, *q;
    p = px->head->next;
    q = qx->head->next;
    // 初始化一个用于保存结果的多项式
    Polynominal res;
    res.head = (PNode *)malloc(sizeof(PNode));
    res.head->exp = -1;
    res.head->next = res.head;
    while (p && p != px->head)
    {
        while (q && q != qx->head)
        {
            int newCoef = 0, newExp = 0;
            newCoef = p->coef * q->coef;
            newExp = p->exp + q->exp;
            insertPoly(&res, newCoef, newExp);
            q = q->next;
        }
        q = qx->head->next;
        p = p->next;
    }
    return res;
}

int main()
{
    SeqList list;
    init(&list, 10);
    for (int i = 0; i < 10; i++)
        insert(&list, i - 1, i);
    printf("对顺序表操作\n");
    output(&list);
    printf("删除顺序表中第1个元素后: \n");
    delete (&list, 0);
    output(&list);
    destroy(&list);
    printf("---------------------------------------\n");
    LinkList ll;
    LinkListInit(&ll);
    for (int i = 0; i < 10; i++)
        LinkListInsert(&ll, i, i);
    printf("对链表操作\n");
    LinkListOutput(&ll);
    printf("删除链表中第1个元素后:\n");
    LinkListDelete(&ll, 0);
    LinkListOutput(&ll);
    printf("链表逆置后: \n");
    reverse(&ll);
    LinkListOutput(&ll);
    printf("链表排序后: \n");
    sort(&ll);
    LinkListOutput(&ll);
    LinkListDestroy(&ll);
    printf("---------------------------------------\n");
    Polynominal p1;
    Polynominal p2;
    printf("第一个多项式: \n");
    create(&p1);
    printInfo(&p1);
    printf("第二个多项式: \n");
    create(&p2);
    printInfo(&p2);
    printf("两个多项式相乘: \n");
    Polynominal p3 = multiplyPoly(&p1, &p2);
    printInfo(&p3);
    printf("两个多项式相加: \n");
    addPoly(&p1, &p2);
    printInfo(&p2);
    destroyPoly(&p1);
    destroyPoly(&p2);
    destroyPoly(&p3);
    return 0;
}