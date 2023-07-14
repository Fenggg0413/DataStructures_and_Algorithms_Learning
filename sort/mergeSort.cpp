#include<vector>
#include<iostream>
#include<limits>
using namespace std;

void merge(vector<int> &vec, int left, int mid, int right)
{
    //初始化辅助数组
    vector<int> leftSubArray(vec.begin() + left, vec.begin() + mid + 1);
    vector<int> rightSubArray(vec.begin() + mid + 1, vec.begin() + right + 1);
    int leftIndex = 0, rightIndex = 0;
    leftSubArray.insert(leftSubArray.end(), INT32_MAX);
    rightSubArray.insert(rightSubArray.end(), INT32_MAX);
    for (int i = left; i <= right; ++i)
    {
        if(leftSubArray[leftIndex] <= rightSubArray[rightIndex])
            vec[i] = leftSubArray[leftIndex++];
        else
            vec[i] = rightSubArray[rightIndex++];
    }
}

void mergeSort(vector<int> &vec, int left, int right)
{
    if(left >= right)
        return;
    int mid = (left + right) / 2;
    mergeSort(vec, left, mid);
    mergeSort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

int main()
{
    vector<int> v{9,8,8,6,7,5,4,3,2,1};
    mergeSort(v, 0, v.size()-1);
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}