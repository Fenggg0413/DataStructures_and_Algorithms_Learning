#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

// 划分
int Partition(int left, int right, std::vector<int> &vec) {
  int i = left, j = right + 1, x = vec[left];
  while (i < j) {
    do {
      i++;
    } while (vec[i] < x);
    do {
      j--;
    } while (vec[j] > x);
    if (i < j)
      std::swap(vec[i], vec[j]);
  }
  // 交换划分元素到正确位置
  std::swap(vec[left], vec[j]);
  return j;
}

// 返回a/b向上取整的值
int Ceil(int a, int b){
    return (a + b - 1)/b;
}

// 插入排序
void insertSort(std::vector<int> &vec, int left, int right) {
  for (size_t i = left; i <= right; ++i) {
    int base = vec[i], j = i - 1;
    while (j >= 0 && vec[j] > base) {
      vec[j + 1] = vec[j]; // 将元素前移
      --j;
    }
    vec[j + 1] = base; // 将元素插到正确的位置
  }
}

// 参数k指示查找的第k小的元素，参数r为分为多少组
int select(int k, int left, int right, int r, std::vector<int> &vec) {
  int n = right - left + 1;
  if (n <= r) {
    // 问题足够小，则直接用插入排序，取第k小的元素
    insertSort(vec, left, right);
    return left + k - 1;
  }
  for (int i = 1; i <= n / r; i++) {
    // 对每组进行插入排序
    insertSort(vec, left + (i - 1) * r, left + i * r - 1);
    // 将每组的中间值放到数组前面
    std::swap(vec[left + i - 1], vec[left + (i - 1) * r + Ceil(r,2) - 1]);
  }
  // 二次取中值
  int j = select(Ceil((n / r), 2), left, left + (n / r) - 1, r, vec);
  // 交换中值到表头，作为划分主元
  std::swap(vec[left], vec[j]);
  j = Partition(left, right, vec);
  int length = j - left + 1; // 划分左子表的长度
  if (k == length)
    return j;
  else if (k < length)   // 在左子表查找第k小的元素
    return select(k, left, j - 1, r, vec);
  else  // 在右子表查找第k-length小的元素
    return select(k - length, j + 1, right, r, vec);
}

int select(int k, int n, std::vector<int> &vec) {
  if (n <= 0 || k > n || k <= 0) {
    std::cout << "Error: out of bounds!\n";
    exit(-1);
  }
  int j = select(k, 0, vec.size() - 1, 5, vec);
  return vec[j];
}

int main() {
  std::vector<int> vec{9, 1, 0, 4, 7, 2, 5, 3, 8, 6};
  int val = select(5, vec.size(), vec);
  std::cout << val << std::endl;
  return 0;
}