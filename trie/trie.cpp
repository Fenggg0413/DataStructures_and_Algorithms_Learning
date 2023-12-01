#include "trie.h"
#include <string_view>

namespace bustub
{

    template <class T>
    auto Trie::Get(std::string_view key) const -> const T *
    {
        std::shared_ptr<const TrieNode> cur{root_};
        for (const auto &ch : key)
        {
            if (cur->children_.find(ch) == cur->children_.end())
            {
                // 不存在该节点
                return nullptr;
            }
            cur = cur->children_.at(ch);
        }
        // Check if the last node is a value node and has the correct type.
        if (cur->is_value_node_)
        {
            auto value_node = dynamic_cast<const TrieNodeWithValue<T> *>(cur.get());
            if (value_node)
            {
                return value_node->value_.get();
            }
            // The type of the value is mismatched.
            return nullptr;
        }
        // The node corresponding to the key doesn't represent a value node.
        return nullptr;
    }

    template <class T>
    auto Trie::Put(std::string_view key, T value) const -> Trie
    {
        // Note that `T` might be a non-copyable type. Always use `std::move` when creating `shared_ptr` on that value.
        auto size = key.size();
        auto dfs = [&](auto self, size_t idx, std::shared_ptr<const TrieNode> cur) -> std::shared_ptr<const TrieNode>
        {
            if (idx == size)
            { // 递归边界条件:到达key的最后一个字符,返回值节点更改过的值节点
                auto value_ptr = std::make_shared<T>(std::move(value));
                if (cur)
                {
                    // 修改节点,需返回原有节点的children节点进行复用
                    return std::make_shared<TrieNodeWithValue<T>>(cur->children_, value_ptr);
                }
                // 插入一个新节点而不是修改原有的节点,只需返回一个带值的TrieWithValue节点即可
                return std::make_shared<TrieNodeWithValue<T>>(value_ptr);
            }
            auto ch = key[idx];
            auto pre = cur;
            if (cur && cur->children_.find(ch) != cur->children_.end())
            {
                cur = cur->children_.at(ch);
            }
            else
            {
                cur = nullptr;
            }
            auto next = self(self, idx + 1, cur);
            std::shared_ptr<TrieNode> ret;
            if (pre)
            {
                ret = pre->Clone();
            }
            else
            {
                ret = std::make_shared<TrieNode>();
            }
            ret->children_[ch] = next;
            return ret;
        };
        auto new_root = dfs(dfs, 0, this->root_);
        return Trie(new_root);
    }

    auto Trie::Remove(std::string_view key) const -> Trie
    {
        auto size = key.size();
        auto dfs = [&](auto self, size_t idx, std::shared_ptr<const TrieNode> cur) -> std::shared_ptr<const TrieNode>
        {
            if (idx == size)
            {
                return std::make_shared<const TrieNode>(cur->children_);
            }
            auto ch = key[idx];
            auto ret = cur->Clone();
            if (cur && cur->children_.find(ch) != cur->children_.end())
            {
                cur = cur->children_.at(ch);
            }
            else
            {
                return nullptr; // 不存在该key的路径,直接返回nullptr
            }
            std::shared_ptr<const TrieNode> next = self(self, idx + 1, cur);
            if (next == nullptr)
            {
                return nullptr;
            }
            if (next->children_.empty() && !(next->is_value_node_))
            {
                ret->children_.erase(ch); // 如果next节点没有children节点也没有值,那么该next节点不应该存在
            }
            else
            {
                ret->children_[ch] = next;
            }
            return ret;
        };
        auto ret = dfs(dfs, 0, this->root_);
        if (ret == nullptr)
        {
            return Trie(this->root_); // 如果ret为空指针则说明要删除的key不存在,返回这棵树本身
        }
        if (ret && ret->children_.empty() && !(ret->is_value_node_))
        {
            return Trie(nullptr);
        }
        return Trie(ret);
    }


    template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const uint32_t *;

    template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const uint64_t *;

    template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const std::string *;

    // If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.

    using Integer = std::unique_ptr<uint32_t>;

    template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const Integer *;

    template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
    template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;

} // namespace bustub
