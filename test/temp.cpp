#include<vector>

using namespace std;

class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        int i = 0, j = 0;
        vector<int> res;
        while (nums[i] < 0) // 找到第一个非负数的位置
            i++;
        j = i - 1;
        while (i < nums.size() && j >= 0)
        {
            if (nums[i] * nums[i] <= nums[j] * nums[j])
            {
                res.push_back(nums[i] * nums[i]);
                ++i;
            }
            else
            {
                res.push_back(nums[j] * nums[j]);
                --j;
            }
        }
        while (i < nums.size())
        {
            res.push_back(nums[i] * nums[i]);
            ++i;
        }
        while (j >= 0)
        {
            res.push_back(nums[j] * nums[j]);
            --j;
        }
        return res;
    }
};