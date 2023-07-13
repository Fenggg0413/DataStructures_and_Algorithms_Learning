#include <vector>
#include <iostream>

using namespace std;

void bubbleSort(vector<int> &vec)
{
    for (int i = vec.size()-1; i > 0; --i)
    {
        bool flag = true;
        for (int j = 0; j < i; ++j)
        {
            if (vec[j] > vec[j + 1])
            {
                swap(vec[j+1], vec[j]);
                flag = false;
            }
        }
        if(flag)
            break;
    }
}

int main()
{
    vector<int> v{9, 8, 5, 3, 2, 7, 1};
    bubbleSort(v);
    for (auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}