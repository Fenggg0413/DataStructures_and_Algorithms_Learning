#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// 定义一个结构体来存储物品的信息
struct Item {
  int weight;
  int value;

  // 用于排序的辅助函数
  bool operator<(const Item &other) const {
    double r1 = (double)value / weight;
    double r2 = (double)other.value / other.weight;
    return r1 > r2; // 按价值密度（value/weight）从大到小排序
  }
};

// 实现贪心算法求解分数背包问题
pair<double, vector<double>> fractionalKnapsack(int W, vector<Item> &items) {
  // 按价值密度排序
  sort(items.begin(), items.end());
  vector<double> solution(items.size(), 0);
  double totalValue = 0.0; // 背包中物品的总价值
  int currentWeight = 0;   // 背包当前的重量

  int idx = 0;
  for (const auto &item : items) {
    if (currentWeight + item.weight <= W) {
      // 如果当前物品可以完全放入背包
      currentWeight += item.weight;
      totalValue += item.value;
      solution[idx++] = 1;
    } else {
      // 如果当前物品不能完全放入背包，按比例放入
      int remain = W - currentWeight;
      totalValue += item.value * ((double)remain / item.weight);
      solution[idx++] = (double)remain / item.weight;
      break;
    }
  }
  return {totalValue, solution};
}

int main() {
  int W; // 背包容量
  int n; // 物品数量
  cout << "输入背包容量: ";
  cin >> W;
  cout << "输入物品数量: ";
  cin >> n;
  vector<Item> items(n);
  cout << "输入物品的重量和价值:" << endl;
  for (int i = 0; i < n; ++i) {
    cin >> items[i].weight >> items[i].value;
  }
  auto [maxValue, solution] = fractionalKnapsack(W, items);
  cout << "最优解: \n";
  for (auto val : solution) {
    cout << val << " ";
  }
  cout << "\n背包能装的最大价值是: " << maxValue << endl;
  return 0;
}
