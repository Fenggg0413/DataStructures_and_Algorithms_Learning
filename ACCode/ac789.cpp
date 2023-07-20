/*给定一个按照升序排列的长度为 n的整数数组，以及 q个查询。
对于每个查询，返回一个元素k的起始位置和终止位置（位置从 0开始计数)*/
#include <iostream>
using namespace std;

const int N = 1e+5;
int a[N];

int main()
{
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    while (q--)
    {
        int k;
        cin >> k;
        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (a[mid] >= k)
                r = mid;
            else
                l = mid + 1;
        }
        if (a[l] != k) // 未找到
        {
            cout << "-1 -1" << endl;
        }
        else
        {
            cout << l << " ";
            l = 0, r = n - 1;
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (a[mid] <= k)
                    l = mid;
                else
                    r = mid - 1;
            }
            cout << l << endl;
        }
    }
    return 0;
}