#include <iostream>

int Place(int row, int col, int *x, int n)
{
    for (int i = col; i < n; i++)
    {
        bool valid = true;
        for (int j = 0; j < row; j++)
        {
            if (x[j] == i || j + x[j] == row + i || j - x[j] == row - i)
            {
                valid = false; // 一旦发现任何冲突，我们就知道当前列 i 对于放置皇后是无效的
                break;
            }
        }
        if (valid)
            return i;
    }
    return -1;
}
void NQueens(int k, int n, int *x)
{
    int col = 0;
    while (col != -1)
    {
        col = Place(k, col, x, n);
        if (col != -1)
        {
            x[k] = col;
            if (k == n - 1)
            {
                for (int i = 0; i < n; i++)
                    std::cout << x[i] << " "; // 输出可行解
                std::cout << std::endl;
            }
            else
            {
                NQueens(k + 1, n, x);
            }
            col++; // 尝试下一个列位置
        }
    }
}

void NQueens(int n, int *x)
{
    NQueens(0, n, x);
}

int main()
{
    int x[8]{-1, -1, -1, -1};
    NQueens(4, x);
    return 0;
}
