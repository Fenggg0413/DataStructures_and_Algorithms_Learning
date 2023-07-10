#include<vector>
#include<iostream>

using namespace std;

class MaxHeap
{
private:
    // 使用动态数组，这样无需考虑扩容问题
    vector<int> maxHeap;

    //从节点i开始，从低向顶堆化
    void siftUp(int i)
    {
        while(true)
        {
            int p = getParent(i); //获取父节点的值
            //当越过根节点或者父节点比子节点大时停止
            if(p < 0 || maxHeap[p] >= maxHeap[i]) 
                break;
            swap(maxHeap[i], maxHeap[p]); //交换两节点值
            i = p; 
        }
    }

    void SiftDown(int i)
    {
        while (true)
        {
            int left = getleft(i), right = getRight(i), max = i;
            if(left < size() && maxHeap[left] > maxHeap[max])
                max = left;
            if(right < size() && maxHeap[right] > maxHeap[max])
                max = right;
            if(max == i)
                break;
            swap(maxHeap[max], maxHeap[i]);
            i = max;
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
    MaxHeap(vector<int> &vec)
    {
        maxHeap = vec;
        //从除去叶节点开始的父节点开始自顶向下堆化
        for (int i = getParent(size() - 1); i >= 0; --i)
        {
            SiftDown(i);
        }
    }

    MaxHeap():maxHeap(0) {}

    ~MaxHeap() {}

    //返回堆顶元素
    int peek()
    {
        return maxHeap[0];
    }

    void push(int val)
    {
        maxHeap.push_back(val);
        siftUp(maxHeap.size() - 1);
    }

    void pop()
    {
        if(empty())
            throw out_of_range("empty heap!");
        swap(maxHeap[0], maxHeap[size() - 1]);
        maxHeap.pop_back();
        SiftDown(0);
    }

    int size()
    {
        return maxHeap.size();
    }

    bool empty()
    {
        return maxHeap.empty();
    }
};

int main()
{
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    MaxHeap mh(v);
    cout << mh.peek() << endl;
    mh.pop();
    cout << mh.peek() << endl;
    return 0;
}