#include <iostream>
#include <thread>

#include "trie_store.h"
#include "trie.h"

bustub::TrieStore trie;

auto read22() -> void
{
    auto ret = trie.Get<int>("222");
    std::cout << **ret << "\n";
}

auto write(std::string_view key) -> void
{
    int a = 1;
    trie.Put(key, a);
    std::cout << "put!\n";
}

auto remove_(std::string_view key) -> void
{
    trie.Remove(key);
    std::cout << "remove!\n";
}

int main()
{
    std::thread t1{read22};
    std::thread t2{write, "22"};
    std::thread t3{read22};
    std::thread t4{read22};
    std::thread t5{remove_, "22"};

    return 0;
}
