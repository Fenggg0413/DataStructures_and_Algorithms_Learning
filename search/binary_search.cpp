#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;
using namespace chrono;

int binarySearch(vector<int> &vec, int target)
{
    int beg = 0, end = vec.size() - 1;
    while (beg <= end)
    {
        int mid = beg + (end - beg) / 2;
        if (target > vec[mid])
        {
            beg = mid + 1;
        }
        else if (target < vec[mid])
        {
            end = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return -1;
}

int normalSearch(vector<int> &vec, int target)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == target)
            return i;
    }
    return -1;
}

int main()
{
    uniform_int_distribution<unsigned> u(0,10000);
    default_random_engine e;
    vector<int> v;
    v.reserve(100000000);
    for (int i = 0; i != 100000000; ++i)
    {
        v.push_back(u(e));
    }

    {
        auto start = system_clock::now();
        int i = normalSearch(v, 86);
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        if (i > -1)
            cout << "Successfully found value: " << v[i] << endl;
        else
            cout << "The value does not exist." << endl;
        cout << "Normal search has cost: "
             << double(duration.count()) * microseconds::period::num / microseconds::period::den
             << "seconds" << endl;
    }

    {
        auto start = system_clock::now();
        sort(v.begin(), v.end());
        int i = binarySearch(v, 54);
        auto end = system_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        if (i > -1)
            cout << "Successfully found value: " << v[i] << endl;
        else
            cout << "The value does not exist." << endl;
        cout << "Binary search has cost: "
             << double(duration.count()) * microseconds::period::num / microseconds::period::den
             << "seconds" << endl;
    }
}