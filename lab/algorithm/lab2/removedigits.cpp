#include <iostream>
#include <stack>
#include <string>

using namespace std;

string removeKDigits(string num, int k) {
  int len = num.size();
  if (k == len)
    return "0"; // 如果需要删除的数量等于数字长度，直接返回0
  stack<char> s;
  for (int i = 0; i < len; ++i) {
    // 如果当前字符小于栈顶元素且删除次数未达到k，则弹出栈顶元素
    while (!s.empty() && s.top() > num[i] && k > 0) {
      s.pop();
      k--;
    }
    s.push(num[i]);
  }
  // 如果删除次数不足k，则继续从栈顶删除元素
  while (k > 0) {
    s.pop();
    k--;
  }
  // 构造结果字符串
  string result = "";
  while (!s.empty()) {
    result = s.top() + result;
    s.pop();
  }
  // 移除前导零
  while (result.size() > 1 && result[0] == '0') {
    result.erase(result.begin());
  }
  return result;
}

int main() {
  string num;
  int k;
  cout << "输入数字序列: ";
  cin >> num;
  cout << "输入需要删除的数字个数: ";
  cin >> k;
  string smallestNum = removeKDigits(num, k);
  cout << "删除后最小的数字序列是: " << smallestNum << endl;
  return 0;
}
