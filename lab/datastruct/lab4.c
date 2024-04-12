#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 100000
#define TRUE 1
#define FALSE 0

typedef int KeyType;
typedef int DataType;
typedef int BOOL;

typedef struct entry // 数据元素
{
    KeyType key;   // 排序关键字, 应该可用于比较
    DataType data; // data宝函数数据元素中其他的数据项
} Entry;
typedef struct list
{                     // 顺序表
    int n;            // 待排序数据元素数量
    Entry D[MAXSIZE]; // 静态数组存储数据元素
} List;

Entry tmp[MAXSIZE]; // 用于归并排序的临时数组

void swap(Entry D[], int a, int b)
{
    Entry tmp = D[a];
    D[a] = D[b];
    D[b] = tmp;
}

// 选择排序
void select_sort(List *list)
{
    int minIndex = 0;
    int nsize = list->n;
    for (int i = 0; i < nsize - 1; ++i)
    {
        for (int j = i; j < nsize; ++j)
        {
            if (list->D[j].key < list->D[minIndex].key)
                minIndex = j;
        }
        swap(list->D, i, minIndex);
    }
}

// 直接插入排序
void insert_sort(List *list)
{
    int j;
    Entry insertItem;
    for (int i = 1; i < list->n; ++i)
    {
        insertItem = list->D[i];
        for (j = i - 1; j >= 0; --j)
        {
            if (insertItem.key < list->D[j].key)
                list->D[j + 1] = list->D[j];
            else
                break;
        }
        list->D[j + 1] = insertItem;
    }
}

// 冒泡排序
void bubble_sort(List *list)
{
    int nsize = list->n;
    for (int i = nsize - 1; i > 0; --i)
    {
        BOOL isSwap = FALSE;
        for (int j = 0; j < i; ++j)
        {
            if (list->D[j].key > list->D[j + 1].key)
            {
                swap(list->D, j, j + 1);
                isSwap = TRUE;
            }
        }
        if (!isSwap)
            break; // 如果本趟循环没有进行交换，则说明排序已完成
    }
}

// 快速排序, [l, r]为闭区间
void quick(int l, int r, List *list)
{
    if (l >= r)
        return;
    int i = l - 1, j = r + 1, x = list->D[l].key;
    while (i < j)
    {
        do
        {
            ++i;
        } while (list->D[i].key < x);
        do
        {
            --j;
        } while (list->D[j].key > x);
        if (i < j)
        {
            swap(list->D, i, j);
        }
    }
    quick(l, j, list);
    quick(j + 1, r, list);
}
void quick_sort(List *list)
{
    quick(0, list->n - 1, list);
}

// 两路合并排序, [l,r]为闭区间
void merge(int l, int r, List *list)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    merge(l, mid, list);
    merge(mid + 1, r, list);
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (list->D[i].key <= list->D[j].key)
            tmp[k++] = list->D[i++];
        else
            tmp[k++] = list->D[j++];
    }
    // 将剩余元素添加到数组
    while (i <= mid)
        tmp[k++] = list->D[i++];
    while (j <= r)
        tmp[k++] = list->D[j++];
    // 将tmp数组中排序好的元素赋值到原数组中
    for (i = l, j = 0; i <= r; ++i, ++j)
        list->D[i] = tmp[j];
}
void merge_sort(List *list)
{
    merge(0, list->n - 1, list);
}

// 向下堆化, 用于堆排序
void shif_down(List *list, int i, int size)
{
    while (TRUE)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int max = i;
        if (left < size && list->D[left].key > list->D[max].key)
            max = left;
        if (right < size && list->D[right].key > list->D[max].key)
            max = right;
        if (max == i)
            break; // 如果本身是最大值了就结束
        swap(list->D, i, max);
        i = max;
    }
}
// 堆排序
void heap_sort(List *list)
{
    int nsize = list->n;
    // 将待排序数组堆化
    for (int i = nsize / 2 - 1; i >= 0; --i)
        shif_down(list, i, nsize);
    for (int sz = nsize - 1; sz >= 0; --sz)
    {
        swap(list->D, 0, sz); // 交换堆顶和堆底元素
        shif_down(list, 0, sz);
    }
}

// 生成随机顺序表
void generate_random_list(List *list)
{
    srand(time(NULL));
    list->n = MAXSIZE;
    for (int i = 0; i < MAXSIZE; ++i)
    {
        list->D[i].key = rand() % MAXSIZE;
        list->D[i].data = i; // 赋值data
    }
}

// 将原始顺序表复制到新顺序表的函数
void copy_list(List *src, List *dest)
{
    dest->n = src->n;
    for (int i = 0; i < src->n; ++i)
    {
        dest->D[i] = src->D[i];
    }
}

// 用于测量排序所需时间的函数, 接受一个函数指针和一个顺序表作为参数
void measure_time(void (*sort_function)(List *), List *list)
{
    clock_t start, end;
    start = clock();
    sort_function(list);
    end = clock();
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
    printf("Time: %.3f ms\n", elapsed_time);
}

int main()
{
    List original_list;
    List working_list;
    printf("使用不同的关键字个数测试排序算法:\n");

    printf("关键字个数: %d\n", MAXSIZE);

    // 生成一个随机列表
    generate_random_list(&original_list);

    // 测试选择排序
    copy_list(&original_list, &working_list);
    printf("选择排序: ");
    measure_time(select_sort, &working_list);

    // 测试插入排序
    copy_list(&original_list, &working_list);
    printf("插入排序: ");
    measure_time(insert_sort, &working_list);

    // 测试冒泡排序
    copy_list(&original_list, &working_list);
    printf("冒泡排序: ");
    measure_time(bubble_sort, &working_list);

    // 测试快速排序
    copy_list(&original_list, &working_list);
    printf("快速排序: ");
    measure_time(quick_sort, &working_list);

    // 测试归并排序
    copy_list(&original_list, &working_list);
    printf("两路合并排序: ");
    measure_time(merge_sort, &working_list);

    // 测试堆排序
    copy_list(&original_list, &working_list);
    printf("堆排序: ");
    measure_time(heap_sort, &working_list);

    return 0;
}