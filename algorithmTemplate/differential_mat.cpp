#include <iostream>
using namespace std;

const int N = 1010;
int s[N][N], a[N][N];

void insert(int x1, int y1, int x2, int y2, int c)
{
    a[x1][y1] += c;
    a[x2 + 1][y1] -= c;
    a[x1][y2 + 1] -= c;
    a[x2 + 1][y2 + 1] += c;
}

int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", &s[i][j]);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            insert(i, j, i, j, s[i][j]);

    while (q--)
    {
        int x1, y1, x2, y2, c;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &c);
        insert(x1, y1, x2, y2, c);
    }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            printf("%d ", s[i][j]);
        }
        cout << '\n';
    }
    return 0;
}