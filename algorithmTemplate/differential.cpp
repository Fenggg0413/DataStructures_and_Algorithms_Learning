#include <iostream>
using namespace std;

const int N = 100010;
int s[N], a[N];
// 差分

void insert(int l, int r, int c)
{
    a[l] += c;
    a[r + 1] -= c;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        scanf("%d", &s[i]);
    //初始化差分数组
    for (int i = 1; i <= n; ++i)
        insert(i, i, s[i]);
    
    while(m--)
    {
        int l, r, c;
        scanf("%d%d%d", &l, &r, &c);
        insert(l, r, c);
    }

    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + a[i];

    for (int i = 1; i <= n; ++i)
        printf("%d ", s[i]);
    return 0;
}