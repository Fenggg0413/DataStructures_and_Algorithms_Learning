#include <vector>
#include <iostream>

using namespace std;

class MinHeap
{
private:
    // 使用动态数组，这样无需考虑扩容问题
    vector<int> minHeap;

    // 从节点i开始，从低向顶堆化
    void siftUp(int i)
    {
        while (true)
        {
            int p = getParent(i); // 获取父节点的值
            // 当越过根节点或者父节点比子节点大时停止
            if (p < 0 || minHeap[p] <= minHeap[i])
                break;
            swap(minHeap[i], minHeap[p]); // 交换两节点值
            i = p;
        }
    }

    void SiftDown(int i)
    {
        while (true)
        {
            int left = getleft(i), right = getRight(i), min = i;
            if (left < size() && minHeap[left] < minHeap[min])
                min = left;
            if (right < size() && minHeap[right] < minHeap[min])
                min = right;
            if (min == i)
                break;
            swap(minHeap[min], minHeap[i]);
            i = min;
        }
    }

    // 返回左节点索引
    int getleft(int i)
    {
        return 2 * i + 1;
    }

    // 返回右节点索引
    int getRight(int i)
    {
        return 2 * i + 2;
    }

    // 返回父节点索引
    int getParent(int i)
    {
        return (i - 1) / 2;
    }

public:
    MinHeap(vector<int> &vec)
    {
        minHeap = vec;
        // 从除去叶节点开始的父节点开始自顶向下堆化
        for (int i = getParent(size() - 1); i >= 0; --i)
        {
            SiftDown(i);
        }
    }

    MinHeap() : minHeap(0) {}

    ~MinHeap() {}

    void push(int val)
    {
        minHeap.push_back(val);
        siftUp(minHeap.size() - 1);
    }

    void pop()
    {
        if (empty())
            throw out_of_range("empty heap!");
        swap(minHeap[0], minHeap[size() - 1]);
        minHeap.pop_back();
        SiftDown(0);
    }

    int size()
    {
        return minHeap.size();
    }

    bool empty()
    {
        return minHeap.empty();
    }

    int peek()
    {
        return minHeap[0];
    }
};

int main()
{
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    MinHeap mh(v);
    cout << mh.peek() << endl;
    mh.pop();
    cout << mh.peek() << endl;
    return 0;
}