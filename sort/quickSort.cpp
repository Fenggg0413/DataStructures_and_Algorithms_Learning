#include<vector>
#include<iostream>

using namespace std;

//选取三个元素的中位数
int median(vector<int> &vec, int left, int mid, int right)
{
    if((vec[left] < vec[mid]) ^ (vec[left] < vec[right]))
        return left;
    else if((vec[mid] < vec[left]) ^ (vec[mid] < vec[right]))
        return mid;
    else
        return right;
}

//哨兵划分
int partition(vector<int> &vec, int left, int right)
{
    int med = median(vec, left, (left + right) / 2, right);
    swap(vec[left], vec[med]); //将中位数交换值数组最左端

    int i = left, j = right;
    while(i < j)
    {
        //取left为基准元素
        while(i < j && vec[j] >= vec[left])
            --j;  //从右向左找到第一个比基准元素小的位置
        while(i < j && vec[i] <= vec[left])
            ++i;  //从左向右找到第一个比基准元素大的位置
        swap(vec[i], vec[j]);
    }
    swap(vec[i], vec[left]);
    return i;        //返回基准元素的索引
}

void quickSortBad(vector<int> &vec, int left, int right)
{
    //当子数组长度为1时终止递归
    if(left >= right)
        return;
    //哨兵划分
    int pivot = partition(vec, left, right);
    //递归的对左右数组进行哨兵划分
    quickSortBad(vec, left, pivot - 1);
    quickSortBad(vec, pivot + 1, right);
}

//尾递归优化版
void quickSort(vector<int> &vec, int left, int right)
{
    while (left < right)
    {
        int pivot = partition(vec, left, right);
        
        if(pivot - left < right - pivot)
        {
            quickSort(vec, left, pivot - 1);
            left = pivot + 1; 
            //剩余未排序区间为[pivot+1, right]
        }
        else
        {
            quickSort(vec, pivot + 1, right);
            right = pivot - 1; 
            //剩余未排序区间为[left, pivot-1]
        }
    }
}

int main()
{
    vector<int> v{9,8,7,6,5,4,3,2,1};
    quickSort(v, 0, int(v.size()-1));
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    vector<int> vec{9,8,7,6,5,4,3,2,1};
    quickSortBad(vec, 0, int(vec.size()-1));
    return 0;
}
