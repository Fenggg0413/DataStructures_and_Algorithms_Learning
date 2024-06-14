#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// 递归求解LCS并使用备忘录优化
int matrixChainMemoization(const vector<int> &p, int i, int j,
                           vector<vector<int>> &memo, vector<vector<int>> &s) {
  if (i == j)
    return 0;

  if (memo[i][j] != numeric_limits<int>::max()) {
    return memo[i][j];
  }

  for (int k = i; k < j; ++k) {
    int q = matrixChainMemoization(p, i, k, memo, s) +
            matrixChainMemoization(p, k + 1, j, memo, s) +
            p[i] * p[k + 1] * p[j + 1];
    if (q < memo[i][j]) {
      memo[i][j] = q;
      s[i][j] = k;
    }
  }

  return memo[i][j];
}

pair<int, string> matrixChainOrderMemo(const vector<int> &p) {
  int n = p.size() - 1;
  vector<vector<int>> memo(n, vector<int>(n, numeric_limits<int>::max()));
  vector<vector<int>> s(n, vector<int>(n, 0));

  int minMultiplications = matrixChainMemoization(p, 0, n - 1, memo, s);

  // 递归构建最优括号化方案
  function<string(int, int)> constructOptimalOrder = [&](int i, int j) {
    if (i == j)
      return string("A") + to_string(i + 1);
    return "(" + constructOptimalOrder(i, s[i][j]) + " x " +
           constructOptimalOrder(s[i][j] + 1, j) + ")";
  };

  string optimalOrder = constructOptimalOrder(0, n - 1);
  return {minMultiplications, optimalOrder};
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
  pair<int, string> result = matrixChainOrderMemo(p);
  cout << "最少乘法次数: " << result.first << endl;
  cout << "最优乘法次序: " << result.second << endl;
  return 0;
}
