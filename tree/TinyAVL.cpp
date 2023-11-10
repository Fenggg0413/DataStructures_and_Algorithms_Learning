#include <vector>
#include <iostream>
#include <random>
#include <initializer_list>

struct TreeNode
{
    int val;
    int height;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
    TreeNode() = default;
};

class AVLTree
{
private:
    /*根节点*/
    TreeNode *root;

    /*获取高度*/
    int getHeight(TreeNode *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    /*更新节点的高度, 在对节点进行操作后都应该要执行此函数*/
    void updateHeight(TreeNode *node)
    {
        if (node != nullptr)
        {
            node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
        }
    }

    /*获取节点的平衡因子*/
    int balanceFactor(TreeNode *node)
    {
        if (node != nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    /*左旋, bf<-1*/
    TreeNode *leftRotate(TreeNode *node)
    {
        TreeNode *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    /*右旋, bf>1*/
    TreeNode *rightRotate(TreeNode *node)
    {
        TreeNode *newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        updateHeight(node);
        updateHeight(newRoot);
        return newRoot;
    }

    TreeNode *balance(TreeNode *node)
    {
        updateHeight(node);
        int bf = balanceFactor(node);
        if (bf > 1)
        {
            if (balanceFactor(node->left) < 0)
                node->left = leftRotate(node->left);
            rightRotate(node);
        }
        else if (bf < -1)
        {
            if (balanceFactor(node->right) > 0)
                node->right = rightRotate(node->right);
            leftRotate(node);
        }
        return node;
    }

    TreeNode *insert(TreeNode *node, int x)
    {
        if (node == nullptr)
            return new TreeNode(x);
        if (x < node->val)
            node->left = insert(node->left, x);
        else if (x > node->val)
            node->right = insert(node->right, x);
        else
            return node; /*不允许存在重复的元素*/

        /*从底至顶对每个节点进行平衡调整*/
        return balance(node);
    }

    void inOrder(TreeNode *node)
    {
        if (node == nullptr)
            return;
        inOrder(node->left);
        std::cout << node->val << " ";
        inOrder(node->right);
    }

    TreeNode *remove(TreeNode *node, int x)
    {
        if (node == nullptr)
            return node;
        if (x < node->val)
            node->left = remove(node->left, x);
        else if (x > node->val)
            node->right = remove(node->right, x);
        else /*找到要删除的节点时*/
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                TreeNode *temp = node->left ? node->left : node->right;
                if (temp == nullptr)
                {
                    /*如果该节点没有子节点则删除该节点*/
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    /*如果该节点有一个子节点则将子节点覆盖到该节点上，然后删除子节点*/
                    *node = *temp;
                }
                delete temp;
            }
            /*有两个子节点的情况*/
            else
            {
                TreeNode *temp = node->right;
                /*找到应删除节点的中序后继节点*/
                while (temp->left != nullptr)
                {
                    temp = temp->left;
                }
                /*将后继节点的数据赋值到该节点上, 然后删除后继节点*/
                node->val = temp->val;
                node->right = remove(node->right, temp->val);
            }
        }
        if (node == nullptr)
            return node;

        /*从底至顶对每个节点进行平衡调整*/
        return balance(node);
    }

public:
    AVLTree() : root(nullptr) {}
    AVLTree(std::initializer_list<int> li): root(nullptr)
    {
        for (auto beg = li.begin(); beg != li.end(); ++beg)
        {
            insert(*beg);
        }
    }
    void insert(int x)
    {
        root = insert(root, x);
    }
    void remove(int x)
    {
        root = remove(root, x);
    }
    void printInfo()
    {
        inOrder(root);
        std::cout << std::endl;
    }
};

int main()
{
    // std::random_device seeds;
    // std::mt19937 gen(seeds());
    // std::uniform_int_distribution<unsigned> dis(0, 100);
    AVLTree avl;
    // for (int i = 0; i < dis(gen); ++i)
    // {
    //     avl.insert(dis(gen));
    // }
    avl.insert(10);
    avl.insert(9);
    avl.insert(8);
    avl.insert(7);
    avl.insert(6);
    avl.insert(5);
    avl.printInfo();
    avl.remove(7);
    avl.printInfo();
    AVLTree tr{8, 7, 5, 9, 3, 6, 1};
    tr.printInfo();
    return 0;
}