#include<vector>
#include<iostream>
#include<iterator>
#include<algorithm>

using namespace std;

// 获取元素 num 的第 k 位
int digit(int val, int exp)
{
    return (val / exp) % 10;
}

void countRadixSort(vector<int> &vec, int exp)
{
    vector<int> countVec(10, 0);
    for(auto val : vec)
    {
        int d = digit(val, exp);
        ++countVec[d];
    }
    //计算前缀和
    for (int i = 1; i < 10; ++i)
    {
        countVec[i] += countVec[i - 1];
    }
    int n = vec.size();
    vector<int> res(n);
    for (int i = n - 1; i >= 0; --i)
    {
        int val = vec[i];
        int d = digit(val, exp);
        res[countVec[d] - 1] = val;
        --countVec[d];
    }
    for (int i = 0; i != n; ++i)
    {
        vec[i] = res[i];
    }
}

void radixSort(vector<int> &vec)
{
    // 获取数组的最大元素，用于判断最大位数
    int max = *max_element(vec.begin(), vec.end());
    for (int exp = 1; exp <= max; exp*=10)
    {
        countRadixSort(vec, exp);
    }
}

int main()
{
    vector<int> v{9, 8, 8, 6, 7, 5, 4, 3, 2, 1};
    radixSort(v);
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}

