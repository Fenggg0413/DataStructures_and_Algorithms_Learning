#include<iostream>
using namespace std;

class ArrayQueue
{
private:
    int *num;
    int front, qsize, qcapacity;
public:
    ArrayQueue(int capacity)
    {
        num = new int[capacity];
        qcapacity = capacity;
        qsize = front = 0;
    }
    int capacity()
    {
        return qcapacity;
    }
    int size()
    {
        return qsize;
    }
    bool empty()
    {
        return size() == 0;
    }
    void push(int val)
    {
        if(capacity() == size())
        {
            cout << "full queue" << endl;
            return;
        }
        int rear = (front + qsize) % qcapacity;
        num[rear] = val;
        ++qsize;
    }
    void pop()
    {
        front = (++front) % qcapacity;
        --qsize;
    }
    int peek()
    {
        if(empty())
            throw out_of_range("empty queue");
        return num[front];
    }
};