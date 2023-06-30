#include<iostream>
using namespace std;

class LinkList
{
public:
    int val;    //链表值
    LinkList *next;
    LinkList(int val): val(val), next(nullptr) {}
};

class ListStack
{
private:
    LinkList *stackTop;
    int stackSize;
public:
    ListStack()
    {
        stackTop = nullptr;
        stackSize = 0;
    }
    ~ListStack()
    {
        std::cout << "----------------" << '\n'
                  << "Begin Destructor" << std::endl;
        while (!empty())
        {
            pop();
            std::cout << "destruct" << '\n';
        }
        std::cout << "Destructor Over" << '\n'
                  << "---------------" << std::endl;
    }
    int size()
    {
        return stackSize;
    }
    bool empty()
    {
        return size() == 0;
    }
    int top()
    {
        if(empty())
            throw out_of_range("empty stack!");
        return stackTop->val;
    }
    void push(int v)
    {
        LinkList *temp = new LinkList(v);
        temp->next = stackTop;
        stackTop = temp;
        ++stackSize;
    }
    void pop()
    {
        int num = top();
        LinkList *p = stackTop;
        stackTop = stackTop->next;
        delete p;
        --stackSize;
    }
};

int main()
{
    ListStack ls;
    ls.push(1);
    ls.push(2);
    ls.push(3);
    ls.push(4);
    ls.push(5);
    std::cout << ls.top() << std::endl;
    ls.pop();
    std::cout << ls.size() << std::endl;
}