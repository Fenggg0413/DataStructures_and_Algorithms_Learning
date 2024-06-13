#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 定义一个结构体来存储作业的信息
struct Job {
  int profit;   // 收益
  int deadline; // 最后完成时间
};

// 比较函数：按收益从高到低排序
bool compareJobs(const Job &a, const Job &b) { return a.profit > b.profit; }

// 贪心算法实现带时限的作业排序问题
int jobScheduling(vector<Job> &jobs) {
  // 按收益从高到低排序
  sort(jobs.begin(), jobs.end(), compareJobs);

  int n = jobs.size();
  int maxDeadline = 0;

  // 找到最大截止时间
  for (const auto &job : jobs) {
    if (job.deadline > maxDeadline) {
      maxDeadline = job.deadline;
    }
  }

  // 创建一个时间槽数组来记录每个时间点是否已经被占用
  vector<int> timeSlot(maxDeadline + 1, -1); // 初始化为-1，表示空闲

  int totalProfit = 0;

  // 遍历所有作业
  for (const auto &job : jobs) {
    // 找到最靠近其截止时间的可用时间点
    for (int t = job.deadline; t > 0; --t) {
      if (timeSlot[t] == -1) {     // 如果时间点t是空闲的
        timeSlot[t] = job.profit;  // 占用这个时间点
        totalProfit += job.profit; // 增加总收益
        break;
      }
    }
  }

  return totalProfit;
}

int main() {
  int n; // 作业数量
  cout << "输入作业数量: ";
  cin >> n;

  vector<Job> jobs(n);
  cout << "输入每个作业的收益和最后完成时间:" << endl;
  for (int i = 0; i < n; ++i) {
    cin >> jobs[i].profit >> jobs[i].deadline;
  }

  int maxProfit = jobScheduling(jobs);

  cout << "作业按序完成的最大收益是: " << maxProfit << endl;

  return 0;
}
