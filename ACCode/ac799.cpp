// 给定一个长度为n的整数序列，请找出最长的不包含重复的数的连续区间，输出它的长度。
#include <iostream>

using namespace std;

#define N 100010
int a[N], s[N];

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0, j = 0; i < n; ++i)
    {
        s[a[i]]++;
        while (s[a[i]] > 1 && j < i) // 使用频率标记数组标记重复的元素
        {
            s[a[j]]--;
            ++j;
        }
        ans = max(ans, i - j + 1);
    }
    cout << ans;
    return 0;
}