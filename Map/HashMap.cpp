#include<string>
#include<vector>
#include<iostream>
using namespace std;

/* 键值对 */
struct Pair
{
    int key;
    string val;
    Pair(int key, string val)
    {
        this->key = key;
        this->val = val;
    }
};

class HashMap
{
private:
    vector<Pair *> buckets;
public:
    HashMap()
    {
        // 初始化数组，包含 100 个桶
        buckets = vector<Pair *>(100);
    }
    ~HashMap()
    {
        for(const auto bucket : buckets)
        {
            delete bucket;
        }
        buckets.clear();
    }
    int HashFunc(int key)
    {
        int index= key % 100;
        return index;
    }
    string get(int key)
    {
        int index = HashFunc(key);
        Pair *pair = buckets[index];
        if(pair == nullptr)
            return nullptr;
        return pair->val;
    }
    void put(int key, string val)
    {
        int index = HashFunc(key);
        Pair *p = new Pair(key, val);
        buckets[index] = p;
    }
    void remove(int key)
    {
        int index = HashFunc(key);
        delete buckets[index];
        buckets[index] = nullptr;
    }
    /* 获取所有键值对 */
    decltype(buckets) 
    getMap()
    {
        vector<Pair *> p;
        for(const auto &pair : buckets)
        {
            if(pair != nullptr)
            {
                p.push_back(pair);
            }
        }
        return p;
    }
    /* 获取所有键 */
    vector<int> getKey()
    {
        vector<int> temp;
        for(const auto &pair : buckets)
        {
            if(pair != nullptr)
            {
                temp.push_back(pair->key);
            }
        }
        return temp;
    }
    /* 获取所有值 */
    vector<string> getVal()
    {
        vector<string> temp;
        for(const auto &pair : buckets)
        {
            if (pair != nullptr)
            {
                temp.push_back(pair->val);
            }
        }
        return temp;
    }
    /* 打印哈希表 */
    void print()
    {
        for(auto pair : buckets)
        {
            cout << pair->key << "->" << pair->val << '\n';
        }
        cout << endl;
    }
};