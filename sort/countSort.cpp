#include<vector>
#include<iostream>

using namespace std;

void countSort(vector<int> &vec)
{
    int max = vec[0];
    //找到数组中的最大值
    for(auto val : vec)
    {
        if(val > max)
            max = val;
    }
    //构建一个大小为最大值+1的数组
    size_t count = max + 1;
    vector<int> countVec(count,0);

    for (size_t i = 0; i < vec.size(); ++i)
    {
        int tmp = vec[i];
        ++countVec[tmp];
    }
    //计算前缀和
    for (size_t i = 1; i < count; ++i)
    {
        countVec[i] += countVec[i-1];
    }
    //构造辅助数组
    int n = vec.size();
    vector<int> res(n);
    for (int i = n-1; i >= 0; --i)
    {
        int num = vec[i];
        res[countVec[num] - 1] = num;
        --countVec[num];
    }
    //将辅助数组覆盖到原数组上
    for (int i = 0; i < n; ++i)
    {
        vec[i] = res[i];
    }
}

int main()
{
    vector<int> v{9, 8, 8, 6, 7, 5, 4, 3, 2, 1};
    countSort(v);
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}