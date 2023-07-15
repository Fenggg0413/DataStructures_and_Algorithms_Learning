#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void bucketSort(vector<int> &vec)
{
    int minValue = vec[0], maxValue = vec[0];
    for (auto val : vec)
    {
        if (val < minValue)
            minValue = val;
        else if (val > maxValue)
            maxValue = val;
    }
    // 计算出桶的数量
    int size = 2; //平均每个桶装几个元素
    int bucketCount = ((maxValue - minValue) / size) + 1;
    vector<vector<int>> buckets(bucketCount);

    // 将元素分配到每个桶中
    for (int i = 0; i < int(vec.size()); ++i)
    {
        int index = (vec[i] - minValue) / size;
        buckets[index].push_back(vec[i]);
    }

    // 对每个桶进行插入排序
    for (auto &bucket : buckets)
    {
        for (int i = 1; i < int(bucket.size()); ++i)
        {
            int base = bucket[i], j = i - 1;
            while(j>=0 && bucket[j] > base)
            {
                bucket[j + 1] = bucket[j];
                --j;
            }
            bucket[j + 1] = base;
        }
    }

    // 将桶中元素拼接起来
    int count = 0;
    for (auto &bucket : buckets)
    {
        for (auto &val : bucket)
        {
            vec[count++] = val;
        }
    }
}

int main()
{
    vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1};
    bucketSort(v);
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}