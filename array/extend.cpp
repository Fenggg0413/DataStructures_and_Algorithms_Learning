/* 扩展数组长度 */
int *extend(int *arr, int size, int enlarge)
{
    int *newArr = new int[size + enlarge]; //new出来的数组长度为原长度加上要增加的长度
    for (int beg = 0; beg != size; ++beg)
    {
        newArr[beg] = arr[beg];
    }
    delete[] arr;
    return newArr;
}