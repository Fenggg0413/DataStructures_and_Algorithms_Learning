//逆波兰求值
#include <vector>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        stack<int> s;
        for (auto element : tokens)
        {
            if(element != "+" && element != "-" && element != "*" && element != "/")
            {
                s.push(stoi(element));
            }
            else
            {
                int val1 = s.top();
                s.pop();
                int val2 = s.top();
                s.pop();
                if(element == "+")
                {
                    s.push(val2 + val1);
                }
                else if(element == "-")
                {
                    s.push(val2 - val1);
                }
                else if(element == "*")
                {
                    s.push(val2 * val1);
                }
                else
                {
                    s.push(val2 / val1);
                }
            }
        }
        return s.top();
    }
};