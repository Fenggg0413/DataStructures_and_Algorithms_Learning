#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 动态规划法实现求两序列的最长公共子序列
pair<int, string> longestCommonSubsequence(const string &X, const string &Y) {
  int m = X.size();
  int n = Y.size();
  // 创建二维数组保存中间结果
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  // 填充dp数组
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (X[i - 1] == Y[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  // 逆向构建LCS字符串
  int length = dp[m][n];
  string lcs(length, ' ');
  int i = m, j = n;
  while (i > 0 && j > 0) {
    if (X[i - 1] == Y[j - 1]) {
      lcs[--length] = X[i - 1];
      --i;
      --j;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      --i;
    } else {
      --j;
    }
  }
  return {dp[m][n], lcs};
}

int main() {
  string X, Y;
  cout << "输入第一个序列: ";
  cin >> X;
  cout << "输入第二个序列: ";
  cin >> Y;
  pair<int, string> result = longestCommonSubsequence(X, Y);
  cout << "最长公共子序列长度: " << result.first << endl;
  cout << "最长公共子序列: " << result.second << endl;
  return 0;
}
