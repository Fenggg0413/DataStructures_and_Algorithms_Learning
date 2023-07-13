#include<vector>
#include<iostream>

using namespace std;

void selectionSort(vector<int> &vec)
{
    for (size_t i = 0; i < vec.size() - 1; ++i)
    {
        int min = i;
        for (size_t j = i + 1; j < vec.size(); ++j)
        {
            if(vec[j] < vec[min])
            {
                min = j;
            }
        }
        swap(vec[i], vec[min]);
    }
}

int main()
{
    vector<int> v{1, 2, 5, 3, 2, 7, 5};
    selectionSort(v);
    for(auto i : v)
        cout << i << " ";
    cout << endl;
    return 0;
}