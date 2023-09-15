#include<iostream>
using namespace std;

class MyLinkedList {
public:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x = 0): val(x), next(nullptr) {}
    };
    MyLinkedList()
    {
        size = 0;
        dummyhead = new ListNode(0);
    }

    int get(int index) 
    {

    }
    
    void addAtHead(int val) 
    {
        ListNode *newHead;
        newHead->val = val;
        ListNode *oldHead = dummyhead->next;
        dummyhead->next = newHead;
        newHead->next = oldHead;
        ++size;
    }

    void addAtTail(int val) {
        ListNode *cur = dummyhead->next;
        while (cur->next)
            cur = cur->next;
        cur->next = new ListNode(val);
        ++size;
    }

    void addAtIndex(int index, int val) {
        
    }
    
    void deleteAtIndex(int index) {
        if(index > size)
            cout << "Out of range!" << endl;
        else
        {
            ListNode *cur = dummyhead->next;
            for (int i = 0; i < index; ++i)
                cur = cur->next;
            
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