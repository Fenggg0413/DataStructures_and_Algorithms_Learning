#include <utility>
#include <vector>
#include <iostream>

void quickSort(int left, int right, std::vector<int> &vec) {
  if (left >= right)
    return;
  int i = left - 1, j = right + 1, x = vec[left];
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
  std::swap(vec[left], vec[j]);
  quickSort(left, j, vec);
  quickSort(j+1, right, vec);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> v(n);
  for (int i = 0; i < n; i++)
    std::cin >> v[i];
  quickSort(0, n - 1, v);
  for (auto val : v)
    std::cout << val << " ";
  std::cout << std::endl;
}