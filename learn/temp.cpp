#include<iostream>
#include<vector>

using namespace std;
vector<int> merge(vector<int> v1, vector<int> v2)
{
    vector<int> res;
    int i = 0, j = 0;
    while(i < v1.size() && j < v2.size())
    {
        if(v1[i] <= v2[j])
            res.push_back(v1[i++]);
        else
            res.push_back(v2[j++]);
    }
    while(i < v1.size())
        res.push_back(v1[i++]);
    while(j < v2.size())
        res.push_back(v2[j++]);

    return res;
}

int main()
{
    vector<int> v1{1, 2, 4, 7};
    vector<int> v2{3, 5, 6};
    auto v3 = merge(v1, v2);
    for(auto i : v3)
        cout << i << " ";
    cout << endl;
}
