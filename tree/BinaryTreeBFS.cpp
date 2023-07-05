#include<vector>
#include<string>
#include<queue>
using namespace std;

/* 二叉树节点结构体 */
struct TreeNode
{
    int val;         // 节点值
    TreeNode *left;  // 左子节点指针
    TreeNode *right; // 右子节点指针
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* 层序遍历 */
vector<int> levelOrder(TreeNode *root)
{
    // 初始化队列，加入根节点
    queue<TreeNode *> queue;
    queue.push(root);
    // 初始化一个列表，用于保存遍历序列
    vector<int> vec;
    while (!queue.empty())
    {
        TreeNode *node = queue.front();
        queue.pop();              // 队列出队
        vec.push_back(node->val); // 保存节点值
        if (node->left != nullptr)
            queue.push(node->left); // 左子节点入队
        if (node->right != nullptr)
            queue.push(node->right); // 右子节点入队
    }
    return vec;
}
