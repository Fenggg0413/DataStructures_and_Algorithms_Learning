#include <algorithm>
#include <iostream>
#include <vector>

struct Item {
  float weight;
  float value;
};

class Knapsack {
public:
  Knapsack() = default;
  Knapsack(float cap, std::vector<Item> &its) : m(cap), items(its) {
    bestValue = 0;
    x.resize(items.size(), 0); // 初始化x数组，全部设为0
  };
  void greedyKnapsack();
  std::vector<Item> getItem() { return items; }
  std::vector<float> getBestItem() { return x; }
  float getBestValue() { return bestValue; }

private:
  float m;                 // 背包载重
  std::vector<Item> items; // 要选择装进背包的物品序列
  float bestValue;         // 最优解值
  std::vector<float> x;    // 解集数组
};

bool compare(Item a, Item b) {
  return (double)a.value / a.weight > (double)b.value / b.weight;
}
void Knapsack::greedyKnapsack() {
  // 按单位价值（价值与重量的比值）从高到低排序
  std::sort(items.begin(), items.end(), compare);
  int u = m; // 背包剩余载重
  int i = 0;
  for (i = 0; i < items.size(); ++i) {
    if (items[i].weight > u)
      break;
    // 若剩余空间充足, 则将该物品全部装进背包
    x[i] = 1.0;
    u -= items[i].weight;
    bestValue += items[i].value;
  }
  if (i < items.size()) {
    x[i] = u / items[i].weight;
    bestValue += x[i] * items[i].value;
  }
}

int main() {
  std::vector<Item> items{{18, 25}, {15, 24}, {10, 15}};
  Knapsack ks{20, items};
  ks.greedyKnapsack();
  auto its = ks.getItem();
  int count = 1;
  for (auto it : its) {
    std::cout << "物品" << count++ << ": 价值(" << it.value << ")  重量("
              << it.weight << ")\n";
  }
  std::cout << "最优解: ";
  auto x = ks.getBestItem();
  for (auto iter = x.begin(); iter != x.end(); ++iter) {
    if (iter + 1 == x.end()) {
      std::cout << *iter << "\n";
    }
    else
      std::cout << *iter << ", ";
  }
  std::cout << "最优解值: " << ks.getBestValue() << std::endl;
  return 0;
}