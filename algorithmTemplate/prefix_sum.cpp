//计算前缀和
#include<iostream>
using namespace std;

const int N = 100010;
int a[N], s[N];
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    
    //初始化前缀和数组, s[0] = 0
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + a[i];
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        printf("%d", s[r] - s[l - 1]); 
    }

    return 0;
}