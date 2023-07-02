#include<iostream>
using namespace std;

/* 双向链表节点 */
struct DoublyListNode
{
    int val;              // 节点值
    DoublyListNode *next; // 后继节点指针
    DoublyListNode *prev; // 前驱节点指针
    DoublyListNode(int val) : val(val), prev(nullptr), next(nullptr) {}
};

class linkedlist_deque
{
private:
    DoublyListNode *front, *rear;
    int dsize;
    void push(int val, bool isFront)
    {
        DoublyListNode *p = new DoublyListNode(val);
        if (empty())
        {
            front = rear = p;
            ++dsize;
            return;
        }
        if (isFront) // 前插
        {
            p->next = front;
            front->prev = p;
            front = p;
        }
        else // 后插
        {
            p->prev = rear;
            rear->next = p;
            rear = p;
        }
        ++dsize;
    }
    int pop(bool isFront)
    {
        // 若队列为空，直接返回 -1
        if (empty())
            return -1;
        int val;
        // 队首出队操作
        if (isFront)
        {
            val = front->val; // 暂存头节点值
            // 删除头节点
            DoublyListNode *fNext = front->next;
            if (fNext != nullptr)
            {
                fNext->prev = nullptr;
                front->next = nullptr;
                delete front;
            }
            front = fNext; // 更新头节点
            // 队尾出队操作
        }
        else
        {
            val = rear->val; // 暂存尾节点值
            // 删除尾节点
            DoublyListNode *rPrev = rear->prev;
            if (rPrev != nullptr)
            {
                rPrev->next = nullptr;
                rear->prev = nullptr;
                delete rear;
            }
            rear = rPrev; // 更新尾节点
        }
        dsize--; // 更新队列长度
        return val;
    }

public:
    linkedlist_deque():front(nullptr), rear(nullptr),dsize(0) {}
    ~linkedlist_deque()
    {
        while (!empty())
        {
            cout << "desconstruct" << endl;
            popFront();
        }
    }
    int size()
    {
        return dsize;
    }
    bool empty()
    {
        return size() == 0;
    }
    void pushFront(int val)
    {
        push(val, true);
    }
    void pushBack(int val)
    {
        push(val, false);
    }
    int popFront()
    {
        return pop(true);
    }
    int popBack()
    {
        return pop(false);
    }
    int peekFront()
    {
        return empty() ? -1 : front->val;
    }
    int peekBack()
    {
        return empty() ? -1 : rear->val;
    }
};

int main()
{
    linkedlist_deque lsq;
    lsq.pushBack(1);
    lsq.pushBack(2);
    lsq.pushBack(3);
    lsq.pushBack(4);
    lsq.pushBack(5);
    cout << lsq.peekBack() << endl;
    lsq.popBack();
    return 0;
}