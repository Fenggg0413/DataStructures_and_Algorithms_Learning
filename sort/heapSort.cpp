#include<vector>
#include<iostream>

using namespace std;

void ShifDown(vector<int> &vec, int i, int size)
{
    while(true)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int max = i;
        if(left < size && vec[left] > vec[max])
            max = left;
        if(right < size && vec[right] > vec[max])
            max = right;
        if(max == i)
            break;
        swap(vec[i], vec[max]);
        i = max;
    }
}

void heapSort(vector<int> &vec)
{
    for (int i = vec.size()/2 -1; i >= 0; --i)
    {
        ShifDown(vec, i, vec.size());
    }

    for (int sz = vec.size() - 1; sz > 0; --sz)
    {
        swap(vec[0], vec[sz]);
        ShifDown(vec, 0, sz);
    }
}

int main()
{
    vector<int> v{9, 8, 8, 6, 7, 5, 4, 3, 2, 1};
    heapSort(v);
    for(auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}