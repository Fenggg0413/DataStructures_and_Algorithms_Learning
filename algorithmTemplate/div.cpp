#include <vector>
#include <string>
#include <iostream>
#include<algorithm>

using namespace std;

// 高精度除以低精度，A >> b，求出商和余数
vector<int> mul(vector<int> &A, int b, int &r)
{
    vector<int> C;
    r = 0;
    //除法从高位开始算
    for (int i = A.size() - 1; i >= 0; --i)
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());
    // 去掉前导0
    while (C.size() > 1 && C.back() == 0)
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

    int r = 0;
    auto C = mul(A, b, r);
    for (int i = C.size() - 1; i >= 0; --i)
        cout << C[i];   //输出商
    cout << endl << r << endl; //输出余数
    return 0;
}