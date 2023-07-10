#include<queue>

using namespace std;

priority_queue<int, vector<int>, greater<int>>
topKHeap(vector<int> &vec, int k)
{
    priority_queue<int, vector<int>, greater<int>> heap;
    //先将k个元素入堆
    for (int i = 0; i != k; ++i)
    {
        heap.push(vec[i]);
    }
    for (int i = k; i < vec.size() - 1; ++i)
    {
        if(vec[i] > heap.top())
        {
            heap.pop();
            heap.push(vec[i]);
        }
    }
    return heap;
}