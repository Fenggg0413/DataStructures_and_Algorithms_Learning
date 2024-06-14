#include <iostream>
#include <vector>

using namespace std;

void printSolution(const vector<int> &board) {
  int N = board.size();
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      if (board[i] == j) {
        cout << "Q ";
      } else {
        cout << ". ";
      }
    }
    cout << endl;
  }
  cout << endl;
}

bool isValid(const vector<int> &board, int row, int col) {
  for (int i = 0; i < row; ++i) {
    // 检查列冲突和对角线冲突
    if (board[i] == col || abs(board[i] - col) == abs(i - row)) {
      return false;
    }
  }
  return true;
}

void solveNQueensUtil(int n, int row, vector<int> &board,
                      vector<vector<int>> &solutions) {
  if (row == n) {
    solutions.push_back(board);
    return;
  }

  for (int col = 0; col < n; ++col) {
    if (isValid(board, row, col)) {
      board[row] = col;
      solveNQueensUtil(n, row + 1, board, solutions);
      // 回溯
      board[row] = -1;
    }
  }
}

vector<vector<int>> solveNQueens(int n) {
  vector<vector<int>> solutions;
  vector<int> board(n, -1);
  solveNQueensUtil(n, 0, board, solutions);
  return solutions;
}

int main() {
  int n;
  cout << "输入皇后数量: ";
  cin >> n;
  vector<vector<int>> solutions = solveNQueens(n);
  cout << "一共有 " << solutions.size() << " 种解法" << endl;
  for (const auto &solution : solutions) {
    printSolution(solution);
  }
  return 0;
}
