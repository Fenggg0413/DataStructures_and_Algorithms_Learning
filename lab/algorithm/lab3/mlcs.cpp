#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 递归求解LCS并使用备忘录优化
int lcsMemoization(const string &X, const string &Y, int m, int n,
                   vector<vector<int>> &memo) {
  // 基本边界条件
  if (m == 0 || n == 0) {
    return 0;
  }

  // 如果已经计算过，直接返回缓存结果
  if (memo[m][n] != -1) {
    return memo[m][n];
  }

  // 递归求解
  if (X[m - 1] == Y[n - 1]) {
    memo[m][n] = 1 + lcsMemoization(X, Y, m - 1, n - 1, memo);
  } else {
    memo[m][n] = max(lcsMemoization(X, Y, m - 1, n, memo),
                     lcsMemoization(X, Y, m, n - 1, memo));
  }

  return memo[m][n];
}

pair<int, string> longestCommonSubsequenceMemo(const string &X,
                                               const string &Y) {
  int m = X.size();
  int n = Y.size();

  // 创建备忘录，初始化为-1
  vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));

  // 计算LCS长度
  int length = lcsMemoization(X, Y, m, n, memo);

  // 逆向构建LCS字符串
  string lcs(length, ' ');
  int i = m, j = n;
  while (i > 0 && j > 0) {
    if (X[i - 1] == Y[j - 1]) {
      lcs[--length] = X[i - 1];
      --i;
      --j;
    } else if (memo[i - 1][j] > memo[i][j - 1]) {
      --i;
    } else {
      --j;
    }
  }

  return {memo[m][n], lcs};
}

int main() {
  string X, Y;
  cout << "输入第一个序列: ";
  cin >> X;
  cout << "输入第二个序列: ";
  cin >> Y;

  pair<int, string> result = longestCommonSubsequenceMemo(X, Y);

  cout << "最长公共子序列长度: " << result.first << endl;
  cout << "最长公共子序列: " << result.second << endl;

  return 0;
}
