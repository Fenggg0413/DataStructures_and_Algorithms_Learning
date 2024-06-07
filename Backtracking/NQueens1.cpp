#include <iostream>

bool Place(int row, int col, int *x)
{
    for (int i = 0; i < row; i++)
    {
        if (x[i] == col || i + x[i] == row + col || i - x[i] == row - col)
            return false;
    }
    return true;
}
bool flag = false; // 标志是否找到第一个可行解
void NQueens(int k, int n, int *x)
{
    for (int i = 0; i < n; i++)
    {
        if (Place(k, i, x))
        {
            x[k] = i;
            if (k == n - 1)
            {
                for (i = 0; i < n; i++)
                    std::cout << x[i] << " "; // 输出可行解
                std::cout << std::endl;
                flag = true; // 找到第一个可行解后，设置标志位
            }
            else
                NQueens(k + 1, n, x);
        }
        if (flag)
            break;
    }
}

void NQueens(int n, int *x)
{
    NQueens(0, n, x);
}
int main()
{
    int x[4]{-1, -1, -1, -1};
    NQueens(4, x);
    return 0;
}