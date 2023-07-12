#include<vector>

using namespace std;

//查找左边界
int binarySearchLeft(vector<int> &vec, int target)
{
    int left = 0, right = vec.size() - 1;
    while(left <= right)
    {
        int mid = left + (right - left) / 2;
        if(target > vec[mid])
            left = mid + 1;
        else if(target < vec[mid])
            right = mid - 1;
        else
            right = mid - 1;
    }
    if(left == vec.size() || vec[left] != target)
        return -1;
    
    return left;
}

//查找右边界
int binarySearchRight(vector<int> &vec, int target)
{
    int left = 0, right = vec.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if(target > vec[mid])
            left = mid + 1;
        else if(target < vec[mid])
            right = mid - 1;
        else
            left = mid + 1;
    }
    if(right < 0 || vec[right] != target)
        return -1;

    return right;
}