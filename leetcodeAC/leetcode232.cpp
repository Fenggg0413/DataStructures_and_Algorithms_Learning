#include<stack>
#include<iostream>

using namespace std;

class MyQueue
{
public:
    MyQueue()
    {
    }

    void push(int x)
    {
        stIn.push(x);
    }

    int pop()
    {
        int res = peek();
        stOut.pop();
        return res;
    }

    int peek()
    {
        if (stOut.empty())
        {
            while (!stIn.empty())
            {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        return stOut.top();
    }

    bool empty()
    {
        if(stIn.empty() && stOut.empty())
            return true;
        return false;
    }

private:
    stack<int> stIn;
    stack<int> stOut;
};

int main()
{
    int x = 10;
    MyQueue *obj = new MyQueue();
    obj->push(1);
    obj->push(2);
    int param_2 = obj->pop(); //1
    int param_3 = obj->peek(); //2
    bool param_4 = obj->empty();
    cout << param_2 << " " << param_3 << " " << param_4 << endl;
    return 0;
}
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */