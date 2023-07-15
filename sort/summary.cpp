#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <iterator>
#include <random>

using namespace std;

// 选取三个元素的中位数
int median(vector<int> &vec, int left, int mid, int right)
{
    if ((vec[left] < vec[mid]) ^ (vec[left] < vec[right]))
        return left;
    else if ((vec[mid] < vec[left]) ^ (vec[mid] < vec[right]))
        return mid;
    else
        return right;
}

// 哨兵划分
int partition(vector<int> &vec, int left, int right)
{
    int med = median(vec, left, (left + right) / 2, right);
    swap(vec[left], vec[med]); // 将中位数交换值数组最左端

    int i = left, j = right;
    while (i < j)
    {
        // 取left为基准元素
        while (i < j && vec[j] >= vec[left])
            --j; // 从右向左找到第一个比基准元素小的位置
        while (i < j && vec[i] <= vec[left])
            ++i; // 从左向右找到第一个比基准元素大的位置
        swap(vec[i], vec[j]);
    }
    swap(vec[i], vec[left]);
    return i; // 返回基准元素的索引
}

void quickSortHelp(vector<int> &vec, int left, int right)
{
    while (left < right)
    {
        int pivot = partition(vec, left, right);

        if (pivot - left < right - pivot)
        {
            quickSortHelp(vec, left, pivot - 1);
            left = pivot + 1;
            // 剩余未排序区间为[pivot+1, right]
        }
        else
        {
            quickSortHelp(vec, pivot + 1, right);
            right = pivot - 1;
            // 剩余未排序区间为[left, pivot-1]
        }
    }
}

void merge(vector<int> &vec, int left, int mid, int right)
{
    // 初始化辅助数组
    vector<int> leftSubArray(vec.begin() + left, vec.begin() + mid + 1);
    vector<int> rightSubArray(vec.begin() + mid + 1, vec.begin() + right + 1);
    int leftIndex = 0, rightIndex = 0;
    leftSubArray.insert(leftSubArray.end(), INT32_MAX);
    rightSubArray.insert(rightSubArray.end(), INT32_MAX);
    for (int i = left; i <= right; ++i)
    {
        if (leftSubArray[leftIndex] <= rightSubArray[rightIndex])
            vec[i] = leftSubArray[leftIndex++];
        else
            vec[i] = rightSubArray[rightIndex++];
    }
}

void mergeSortHelp(vector<int> &vec, int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    mergeSortHelp(vec, left, mid);
    mergeSortHelp(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

void ShifDown(vector<int> &vec, int i, int size)
{
    while (true)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int max = i;
        if (left < size && vec[left] > vec[max])
            max = left;
        if (right < size && vec[right] > vec[max])
            max = right;
        if (max == i)
            break;
        swap(vec[i], vec[max]);
        i = max;
    }
}

// 获取元素 num 的第 k 位
int digit(int val, int exp)
{
    return (val / exp) % 10;
}

void countRadixSort(vector<int> &vec, int exp)
{
    vector<int> countVec(10, 0);
    for (auto val : vec)
    {
        int d = digit(val, exp);
        ++countVec[d];
    }
    // 计算前缀和
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

void selectionSort(vector<int> &vec)
{
    for (size_t i = 0; i < vec.size() - 1; ++i)
    {
        int min = i;
        for (size_t j = i + 1; j < vec.size(); ++j)
        {
            if (vec[j] < vec[min])
            {
                min = j;
            }
        }
        swap(vec[i], vec[min]);
    }
}

void bubbleSort(vector<int> &vec)
{
    for (int i = vec.size() - 1; i > 0; --i)
    {
        bool flag = true;
        for (int j = 0; j < i; ++j)
        {
            if (vec[j] > vec[j + 1])
            {
                swap(vec[j + 1], vec[j]);
                flag = false;
            }
        }
        if (flag)
            break;
    }
}

void insertSort(vector<int> &vec)
{
    // 已完成排序元素数量 1,2, ..., n
    for (size_t i = 1; i < vec.size(); ++i)
    {
        int base = vec[i], j = i - 1;
        while (j >= 0 && vec[j] > base)
        {
            vec[j + 1] = vec[j]; // 将元素前移
            --j;
        }
        vec[j + 1] = base; // 将元素插到正确的位置
    }
}

void bucketSort(vector<int> &vec)
{
    int minValue = vec[0], maxValue = vec[0];
    for (auto val : vec)
    {
        if (val < minValue)
            minValue = val;
        else if (val > maxValue)
            maxValue = val;
    }
    // 计算出桶的数量
    int size = 2; // 平均每个桶装几个元素
    int bucketCount = ((maxValue - minValue) / size) + 1;
    vector<vector<int>> buckets(bucketCount);

    // 将元素分配到每个桶中
    for (int i = 0; i < int(vec.size()); ++i)
    {
        int index = (vec[i] - minValue) / size;
        buckets[index].push_back(vec[i]);
    }

    // 对每个桶进行插入排序
    for (auto &bucket : buckets)
    {
        for (int i = 1; i < int(bucket.size()); ++i)
        {
            int base = bucket[i], j = i - 1;
            while (j >= 0 && bucket[j] > base)
            {
                bucket[j + 1] = bucket[j];
                --j;
            }
            bucket[j + 1] = base;
        }
    }

    // 将桶中元素拼接起来
    int count = 0;
    for (auto &bucket : buckets)
    {
        for (auto &val : bucket)
        {
            vec[count++] = val;
        }
    }
}

void countSort(vector<int> &vec)
{
    int max = vec[0];
    // 找到数组中的最大值
    for (auto val : vec)
    {
        if (val > max)
            max = val;
    }
    // 构建一个大小为最大值+1的数组
    size_t count = max + 1;
    vector<int> countVec(count, 0);

    for (size_t i = 0; i < vec.size(); ++i)
    {
        int tmp = vec[i];
        ++countVec[tmp];
    }
    // 计算前缀和
    for (size_t i = 1; i < count; ++i)
    {
        countVec[i] += countVec[i - 1];
    }
    // 构造辅助数组
    int n = vec.size();
    vector<int> res(n);
    for (int i = n - 1; i >= 0; --i)
    {
        int num = vec[i];
        res[countVec[num] - 1] = num;
        --countVec[num];
    }
    // 将辅助数组覆盖到原数组上
    for (int i = 0; i < n; ++i)
    {
        vec[i] = res[i];
    }
}

void heapSort(vector<int> &vec)
{
    for (int i = vec.size() / 2 - 1; i >= 0; --i)
    {
        ShifDown(vec, i, vec.size());
    }

    for (int sz = vec.size() - 1; sz > 0; --sz)
    {
        swap(vec[0], vec[sz]);
        ShifDown(vec, 0, sz);
    }
}

void mergeSort(vector<int> &vec)
{
    mergeSortHelp(vec, 0, vec.size() - 1);
}

void quickSort(vector<int> &vec)
{
    quickSortHelp(vec, 0, vec.size() - 1);
}

void radixSort(vector<int> &vec)
{
    // 获取数组的最大元素，用于判断最大位数
    int max = *max_element(vec.begin(), vec.end());
    for (int exp = 1; exp <= max; exp *= 10)
    {
        countRadixSort(vec, exp);
    }
}

void testBubbleSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    bubbleSort(v);
}

void testSelectSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    selectionSort(v);
}

void testInsertSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    insertSort(v);
}

void testQuickSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    quickSort(v);
}

void testMergeSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    mergeSort(v);
}

void testHeapSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    heapSort(v);
}

void testBucketSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    bucketSort(v);
}

void testCountSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    countSort(v);
}

void testRadixSort()
{
    vector<int> v;
    v.reserve(10000);
    uniform_int_distribution<unsigned> u(0, 1000);
    default_random_engine e;
    for (int i = 0; i < 100000; ++i)
    {
        v.push_back(u(e));
    }
    radixSort(v);
}

int main()
{
    {
        auto start = std::chrono::steady_clock::now();
        testBubbleSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "bubble sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testBubbleSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "bubble sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    cout << "------------------------------------------------" << endl;
    {
        auto start = std::chrono::steady_clock::now();
        testBubbleSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "bubble sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testSelectSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "select sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testInsertSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "insert sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testQuickSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "quick sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testMergeSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "merge sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testBucketSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "bucket sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testHeapSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "heap sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testCountSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "count sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }

    {
        auto start = std::chrono::steady_clock::now();
        testRadixSort();
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = std::chrono::duration<double>(end - start);
        std::cout << "radix sort elapsed time: " << elapsed_seconds.count() << "s\n";
    }
}