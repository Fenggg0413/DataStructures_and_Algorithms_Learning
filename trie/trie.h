#pragma once

#include <algorithm>
#include <cstddef>
#include <future> // NOLINT
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace bustub
{

    class MoveBlocked
    {
    public:
        explicit MoveBlocked(std::future<int> wait) : wait_(std::move(wait)) {}

        MoveBlocked(const MoveBlocked &) = delete;
        MoveBlocked(MoveBlocked &&that) noexcept
        {
            if (!that.waited_)
            {
                that.wait_.get();
            }
            that.waited_ = waited_ = true;
        }

        auto operator=(const MoveBlocked &) -> MoveBlocked & = delete;
        auto operator=(MoveBlocked &&that) noexcept -> MoveBlocked &
        {
            if (!that.waited_)
            {
                that.wait_.get();
            }
            that.waited_ = waited_ = true;
            return *this;
        }

        bool waited_{false};
        std::future<int> wait_;
    };

    // A TrieNode is a node in a Trie.
    class TrieNode
    {
    public:
        // Create a TrieNode with no children.
        TrieNode() = default;

        // Create a TrieNode with some children.
        explicit TrieNode(std::map<char, std::shared_ptr<const TrieNode>> children) : children_(std::move(children)) {}

        virtual ~TrieNode() = default;
        virtual auto Clone() const -> std::unique_ptr<TrieNode> { return std::make_unique<TrieNode>(children_); }
        std::map<char, std::shared_ptr<const TrieNode>> children_;
        bool is_value_node_{false};
    };

    // A TrieNodeWithValue is a TrieNode that also has a value of type T associated with it.
    template <class T>
    class TrieNodeWithValue : public TrieNode
    {
    public:
        // Create a trie node with no children and a value.
        explicit TrieNodeWithValue(std::shared_ptr<T> value) : value_(std::move(value)) { this->is_value_node_ = true; }

        // Create a trie node with children and a value.
        TrieNodeWithValue(std::map<char, std::shared_ptr<const TrieNode>> children, std::shared_ptr<T> value)
            : TrieNode(std::move(children)), value_(std::move(value))
        {
            this->is_value_node_ = true;
        }

        auto Clone() const -> std::unique_ptr<TrieNode> override
        {
            return std::make_unique<TrieNodeWithValue<T>>(children_, value_);
        }

        // The value associated with this trie node.
        std::shared_ptr<T> value_;
    };

    class Trie
    {
    private:
        // The root of the trie.
        std::shared_ptr<const TrieNode> root_{nullptr};

        // Create a new trie with the given root.
        explicit Trie(std::shared_ptr<const TrieNode> root) : root_(std::move(root)) {}

    public:
        // Create an empty trie.
        Trie() = default;
        template <class T>
        auto Get(std::string_view key) const -> const T *;
        template <class T>
        auto Put(std::string_view key, T value) const -> Trie;
        auto Remove(std::string_view key) const -> Trie;
        auto GetRoot() const -> std::shared_ptr<const TrieNode> { return root_; }
    };

} // namespace bustub
