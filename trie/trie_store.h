#pragma once

#include <optional>
#include <shared_mutex>
#include <utility>
#include "trie.h"

namespace bustub
{
    template <class T>
    class ValueGuard
    {
    public:
        ValueGuard(Trie root, const T &value) : root_(std::move(root)), value_(value) {}
        auto operator*() const -> const T & { return value_; }

    private:
        Trie root_;
        const T &value_;
    };

    class TrieStore
    {
    public:
        
        template <class T>
        auto Get(std::string_view key) -> std::optional<ValueGuard<T>>;

        template <class T>
        void Put(std::string_view key, T value);
        void Remove(std::string_view key);

    private:
        std::mutex root_lock_;
        std::mutex write_lock_;
        Trie root_;
    };

} // namespace bustub
