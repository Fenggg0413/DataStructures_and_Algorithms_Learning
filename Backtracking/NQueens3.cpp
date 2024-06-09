#include <iostream>
#include <iomanip>

bool Place(int row, int col, int *x)
{
    for (int i = 0; i < row; i++)
    {
        if (x[i] == col || i + x[i] == row + col || i - x[i] == row - col)
            return false;
    }
    return true;
}
void NQueens(int k, int n, int *x, int M)
{
    // 当k==0时，使x[0]<(N+1)/2
    // 当n为奇数、k==1和x[0]=M-1时，使x[1]<(N+1)/2
    int s = ((k == 0) || (n % 2 == 1 && k == 1 && x[0] == M - 1)) ? M : n; 
    for (int i = 0; i < s; i++)                                         
        if (Place(k, i, x))
        {
            x[k] = i;
            if (k == n - 1)
            {
                for (i = 0; i < n; i++)
                    std::cout << x[i] << " ";
                std::cout << std::endl;
            }
            else
                NQueens(k + 1, n, x, M);
        }
}
void NQueens(int n, int *x)
{
    int M;
    M = (n + 1) / 2; // M确定x[0]的取值范围，即x[0]<M
    NQueens(0, n, x, M);
}

int main()
{
    int x[8]{-1, -1, -1, -1, -1, -1, -1, -1};
    NQueens(8, x);
    return 0;
}