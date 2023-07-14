#include<vector>
#include<iostream>

using namespace std;

void insertSort(vector<int> &vec)
{
    //已完成排序元素数量 1,2, ..., n
    for (size_t i = 1; i < vec.size(); ++i)
    {
        int base = vec[i], j = i - 1;
        while (j >= 0 && vec[j] > base)
        {
            vec[j + 1] = vec[j]; //将元素前移
            --j;
        }
        vec[j + 1] = base; //将元素插到正确的位置
    }
}

int main()
{
    vector<int> v{1, 2, 5, 3, 2, 7, 5};
    insertSort(v);
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}