#include<iostream>
#include<vector>

class VectorStack
{
private:
    std::vector<int> stackTop;

public:
    int size()
    {
        return stackTop.size();
    }
    bool empty()
    {
        return stackTop.empty();
    }
    int top()
    {
        if(empty())
            throw std::out_of_range("stack empty!");
        return stackTop.back();
    }
    void push(int val)
    {
        stackTop.push_back(val);
    }
    void pop()
    {
        int val = top();
        stackTop.pop_back();
    }
};