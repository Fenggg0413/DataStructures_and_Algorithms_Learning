#include<unordered_map>
#include<vector>
#include<iostream>

using namespace std;

pair<int,int> searchSum(vector<int> &vec, int target)
{
    unordered_map<int, int> mps;
    for (size_t i = 0; i != vec.size(); ++i)
    {
        if(mps.count(target - vec[i]))
            return {i, mps[target - vec[i]]};
        mps.emplace(vec[i], i);
    }
    return {-1, -1};
}

int main()
{
    vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto tmp = searchSum(vec, 11);
    cout << tmp.first << " " << tmp.second << endl;
    return 0;
}