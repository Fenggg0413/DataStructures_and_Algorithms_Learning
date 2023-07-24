#include<vector>
#include<string>
#include<iostream>

using namespace std;

//高精度乘低精度，A >> b
vector<int> mul(vector<int> &A, int b)
{
    vector<int> C;
    int t = 0;
    //当t不为0或者i小于A的长度时
    for (int i = 0; i < A.size() || t; ++i)
    {
        if(i < A.size()) 
            t += A[i] * b; 
        C.push_back(t % 10);
        t /= 10;
    }

    //去掉前导0
    while(C.size() > 1 && C.back() == 0)
        C.pop_back();
    return C;
}

int main()
{
    string a;
    int b;
    cin >> a;
    cin >> b;

    vector<int> A;
    for (int i = a.size() - 1; i >= 0; --i)
        A.push_back(a[i] - '0');

    auto C = mul(A, b);
    for (int i = C.size() - 1; i >= 0; --i)
        cout << C[i];
    cout << endl;
    return 0;
}