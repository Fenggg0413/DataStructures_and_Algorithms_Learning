#include<vector>

using namespace std;

class Solution
{
public:
    //双指针写法
    vector<int> sortedSquares(vector<int> &nums)
    {
        vector<int> res(nums.size());
        int i = 0, j = nums.size() - 1, k = res.size() - 1;
        while (i <= j)
        {
            if (nums[i] * nums[i] < nums[j] * nums[j])
            {
                res[k--] = nums[j] * nums[j];
                j--;
            }
            else
            {
                res[k--] = nums[i] * nums[i];
                i++;
            }
        }
        return res;
    }
};