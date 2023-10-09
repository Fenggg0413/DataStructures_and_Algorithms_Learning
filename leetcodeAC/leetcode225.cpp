#include<queue>

using namespace std;

class MyStack
{
public:
    MyStack()
    {
    }

    void push(int x)
    {
        q1.push(x);
    }

    int pop()
    {
        while (q1.size() > 1)
        {
            q2.push(q1.front());
            q1.pop();
        }
        int res = q1.front();
        q1.pop();
        while (!q2.empty())
        {
            q1.push(q2.front());
            q2.pop();
        }
        return res;
    }

    int top()
    {
        int res;
        while (!q1.empty())
        {
            res = q1.front();
            q2.push(res);
            q1.pop();
        }
        while (!q2.empty())
        {
            q1.push(q2.front());
            q2.pop();
        }
        return res;
    }

    bool empty()
    {
        return q1.empty() && q2.empty();
    }

private:
    queue<int> q1;
    queue<int> q2;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */