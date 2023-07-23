#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 判断A >= B
bool cmp(vector<int> &A, vector<int> &B)
{
    if (A.size() != B.size())
        return A.size() > B.size();
    for (int i = A.size() - 1; i >= 0; --i)
    {
        if (A[i] != B[i])
            return A[i] > B[i];
    }
    return true;
}

// 高精度减法模版
vector<int> sub(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    for (int i = 0, t = 0; i < A.size(); ++i)
    {
        t = A[i] - t;
        if (i < B.size())   //确保不会越界访问B数组
            t -= B[i];
        // 如果t为正数，则t+10%10为t本身，如果t为负数则t+10%10得答案
        // 此写法使代码简洁
        C.push_back((t + 10) % 10);
        if (t < 0) // 如果t < 0, 则说明已经要求进位，将t置为1
            t = 1;
        else       // 反之，则说明没有进位，将t置为0
            t = 0;
    }
    while (C.size() > 1 && C.back() == 0) //去掉前导0，防止输出形如009，这样的数字
        C.pop_back();
    return C;
}

int main()
{
    string a, b;
    vector<int> A, B;
    cin >> a >> b;
    for (int i = a.size() - 1; i >= 0; --i)
        A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; --i)
        B.push_back(b[i] - '0');

    // 进行判断的目的是使 减法的第一个数(被减数)永远大于第二个数(减数)
    if (cmp(A, B))
    {
        // A >= B
        auto C = sub(A, B);
        for (int i = C.size() - 1; i >= 0; --i)
            cout << C[i];
    }
    else
    {
        // A < B
        auto C = sub(B, A);
        cout << '-'; //如果 A < B, 则输出为负数，要添加负号
        for (int i = C.size() - 1; i >= 0; --i)
            cout << C[i];
    }
    return 0;
}