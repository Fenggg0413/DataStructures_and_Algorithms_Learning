/* 链表节点结构体 */
#include<iostream>
using namespace std;

struct ListNode
{
    int val;                                   // 节点值
    ListNode *next;                            // 指向下一节点的指针（引用）
    ListNode(int x) : val(x), next(nullptr) {} // 构造函数
};

class LinkListQueue
{
private:
    ListNode *front, *rear;
    int queueSize;
public:
    LinkListQueue()
    {
        front = nullptr;
        rear = nullptr;
        queueSize = 0;
    }
    ~LinkListQueue()
    {
        while(!empty())
        {
            pop();
        }
    }
    void push(int val)
    {
        //尾插
        ListNode *p = new ListNode(val);
        //如果队列为空
        if(front == nullptr && rear == nullptr)
        {
            front = p;
            rear = p;
        }
        else
        {
            rear->next = p;
            rear = p;
        }
        ++queueSize;
    }
    void pop()
    {
        //头删
        if(empty())
            throw out_of_range("empty queue");
        ListNode *temp = front;
        front = front->next;
        delete temp;
        --queueSize;
    }
    int size()
    {
        return queueSize;
    }
    bool empty()
    {
        return size() == 0;
    }
    int peek()
    {
        if(empty())
            throw out_of_range("empty queue");
        return front->val;
    }
};