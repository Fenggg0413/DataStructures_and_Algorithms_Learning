#include <iostream>
#include <string>

using namespace std;

string removeKDigits(string num, int k) {
  int n = num.size();
  std::string result = "";

  for (char digit : num)
  {
    while (k > 0 && !result.empty() && result.back() > digit)
    {
      result.pop_back();
      k--;
    }
    result.push_back(digit);
  }

  // 如果还有未删除的数字，从末尾删除
  while (k > 0)
  {
    result.pop_back();
    k--;
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
