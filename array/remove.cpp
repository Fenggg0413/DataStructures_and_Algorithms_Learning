/* 删除索引 index 处元素 */
void remove(int *nums, int size, int index)
{
    // 把索引 index 之后的所有元素向前移动一位
    for (int i = index; i < size - 1; i++)
    {
        nums[i] = nums[i + 1];
    }
}
