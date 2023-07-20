//查找逆序对
#include <iostream>
using namespace std;

typedef long long LL;
const int N = 1e+6;
int a[N];
int tmp[N];

LL merge_sort(int a[], int l, int r)
{
    if (l >= r)
        return 0;
    int mid = (l + r) >> 1;
    LL res = merge_sort(a, l, mid) + merge_sort(a, mid + 1, r);

    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else
        {
            tmp[k++] = a[j++];
            res += mid - i + 1;
        }
    }
    while (i <= mid)
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];
    for (i = l, j = 0; i <= r; ++i, ++j)
        a[i] = tmp[j];
    return res;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cout << merge_sort(a, 0, n - 1);
}