#include<string>
#include<iostream>
using namespace std;

/* 加法哈希 */
int addHash(string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key)
    {
        hash = (hash + (int)c) % MODULUS;
    }
    return (int)hash;
}

/* 乘法哈希 */
int mulHash(string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key)
    {
        hash = (31 * hash + (int)c) % MODULUS;
    }
    return (int)hash;
}

/* 异或哈希 */
int xorHash(string key)
{
    int hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key)
    {
        cout << (int)c << endl;
        hash ^= (int)c;
    }
    return hash & MODULUS;
}

/* 旋转哈希 */
int rotHash(string key)
{
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key)
    {
        hash = ((hash << 4) ^ (hash >> 28) ^ (int)c) % MODULUS;
    }
    return (int)hash;
}
