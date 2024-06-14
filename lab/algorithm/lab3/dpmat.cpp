#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// 动态规划法求解矩阵链乘法问题
pair<int, string> matrixChainOrder(const vector<int> &p) {
  int n = p.size() - 1;
  vector<vector<int>> dp(n, vector<int>(n, 0));
  vector<vector<int>> s(n, vector<int>(n, 0));

  // 填充dp和s表
  for (int l = 2; l <= n; ++l) { // l是链的长度
    for (int i = 0; i < n - l + 1; ++i) {
      int j = i + l - 1;
      dp[i][j] = numeric_limits<int>::max();
      for (int k = i; k < j; ++k) {
        int q = dp[i][k] + dp[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
        if (q < dp[i][j]) {
          dp[i][j] = q;
          s[i][j] = k;
        }
      }
    }
  }

  // 递归构建最优括号化方案
  function<string(int, int)> constructOptimalOrder = [&](int i, int j) {
    if (i == j)
      return string("A") + to_string(i + 1);
    return "(" + constructOptimalOrder(i, s[i][j]) + " x " +
           constructOptimalOrder(s[i][j] + 1, j) + ")";
  };

  string optimalOrder = constructOptimalOrder(0, n - 1);
  return {dp[0][n - 1], optimalOrder};
}

int main() {
  int n;
  cout << "输入矩阵数量: ";
  cin >> n;
  vector<int> p(n + 1);
  cout << "输入矩阵的维度: ";
  for (int i = 0; i <= n; ++i) {
    cin >> p[i];
  }
  pair<int, string> result = matrixChainOrder(p);
  cout << "最少乘法次数: " << result.first << endl;
  cout << "最优乘法次序: " << result.second << endl;
  return 0;
}
