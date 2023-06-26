/* 在数组的索引 index 处插入元素 num */
void insert(int *nums, int size, int num, int index)
{
    // 把索引 index 以及之后的所有元素向后移动一位
    for (int i = size - 1; i > index; i--)
    {
        nums[i] = nums[i - 1];
    }
    // 将 num 赋给 index 处元素
    nums[index] = num;
}
