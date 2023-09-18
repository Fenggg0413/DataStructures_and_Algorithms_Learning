// 设计自己的链表
// 注意检查边界!!!
#include <iostream>
using namespace std;

class MyLinkedList
{
public:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(nullptr) {}
    };
    MyLinkedList()
    {
        size = 0;
        dummyhead = new ListNode(0);
    }

    int get(int index)
    {
        if (index >= size || index < 0)
        {
            return -1;
        }
        ListNode *cur = dummyhead->next;
        while (index--)
        {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val)
    {
        ListNode *newHead = new ListNode(val);
        newHead->next = dummyhead->next;
        dummyhead->next = newHead;
        ++size;
    }

    void addAtTail(int val)
    {
        ListNode *cur = dummyhead;
        while (cur->next)
            cur = cur->next;
        cur->next = new ListNode(val);
        ++size;
    }

    void addAtIndex(int index, int val)
    {
        if (index > size) //index = size时相当于尾插
            return;
        if (index < 0)
            index = 0;
        ListNode *cur = dummyhead;
        while (index--)
        {
            cur = cur->next;
        }
        ListNode *p = new ListNode(val);
        p->next = cur->next;
        cur->next = p;
        ++size;
    }

    void deleteAtIndex(int index)
    {
        if (index >= size || index < 0)
            return;
        else
        {
            ListNode *cur = dummyhead;
            while (index--)
            {
                cur = cur->next;
            }
            ListNode *tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
            // delete命令指示释放了tmp指针原本所指的那部分内存，
            // 被delete后的指针tmp的值（地址）并非就是NULL，而是随机值。也就是被delete后，
            // 如果不再加上一句tmp=nullptr,tmp会成为乱指的野指针
            // 如果之后的程序不小心使用了tmp，会指向难以预想的内存空间
            tmp = nullptr;
            --size;
        }
    }

private:
    ListNode *dummyhead;
    int size;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */