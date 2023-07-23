#include <iostream>
#include <vector>
#include <string>

using namespace std;

//高精度加法模版
vector<int> add(vector<int> &a, vector<int> &b)
{
    vector<int> C;
    int t = 0; // 进位

    for (int i = 0; i < a.size() || i < b.size(); ++i)
    {
        if (i < a.size())
            t += a[i];
        if (i < b.size())
            t += b[i];
        C.push_back(t % 10);
        t /= 10;
    }
    if (t)
        C.push_back(1);
    return C;
}

int main()
{
    string a, b;
    cin >> a >> b;
    vector<int> A, B;
    for (int i = a.size() - 1; i >= 0; --i) //将输入的数字倒序存入数组中，方便计算
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; --i) 
        B.push_back(b[i] - '0');

    auto C = add(A, B);

    for (int i = C.size() - 1; i >= 0; --i)
        cout << C[i];
    cout << endl;
    return 0;
}