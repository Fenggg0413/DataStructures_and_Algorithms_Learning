#include <iostream>

const int N = 1e+6;
int vec[N];
int tmp[N];

void mergeSort(int left, int right, int vec[]) {
  if (left >= right)
    return;
  int mid = (left + right) / 2;
  mergeSort(left, mid, vec);
  mergeSort(mid + 1, right, vec);

  int k = 0, i = left, j = mid + 1;
  while (i <= mid && j <= right) {
    if (vec[i] <= vec[j])
      tmp[k++] = vec[i++];
    else
      tmp[k++] = vec[j++];
  }
  // 左半部分未完全进入数组
  while (i <= mid) {
    tmp[k++] = vec[i++];
  }
  // 右半部分
  while (j <= right) {
		tmp[k++] = vec[j++];
  }
  // 合并
  for (k = 0, i = left; i <= right; k++, i++) {
    vec[i] = tmp[k];
	}
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++)
    std::cin >> vec[i];
  mergeSort(0, n - 1, vec);
  for (int i = 0; i < n; i++)
    std::cout << vec[i] << " ";
  std::cout << std::endl;
}