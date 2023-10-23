// 数组模拟链表，静态链表, 在写算法题中静态链表更快
#include <iostream>
using namespace std;

const int N = 100010;

// idx表示目前用到的节点
// head表示头节点的下标
// e[]存储idx下标对应的数据
// ne[]存储节点的next指针
int e[N], en[N], idx, head;

void init()
{
    head = -1;
    idx = 0;
}

// 在链表头插入数据
void add_to_head(int x)
{
    e[idx] = x;
    en[idx] = head;
    head = idx;
    idx++;
}

// 插入x到第k个节点后面
void add_to_k(int k, int x)
{
    e[idx] = x;
    en[idx] = en[k];
    en[k] = idx;
    idx++;
}

// 算法题中静态链表不需要去考虑内存泄漏, 直接跳过要删除的节点即可
// 删除第k个节点
void remove(int k)
{
    en[k] = en[en[k]];
}