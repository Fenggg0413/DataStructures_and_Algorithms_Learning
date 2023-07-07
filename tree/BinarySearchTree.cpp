#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int num):val(num),left(nullptr),right(nullptr) {}
};

class BinarySearchTree
{
private:
    TreeNode *root;
    void inOrder(TreeNode *root) // 中序遍历获取升序的数组
    {
        if (root == nullptr)
            return;
        // 访问优先级：左子树 -> 根节点 -> 右子树
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }

public:
    BinarySearchTree(vector<int> &nums);  //用数组来构建一个二叉树
    ~BinarySearchTree();
    TreeNode *buildTree(vector<int> &nums, int beg, int end);
    void freeBinaryTree(TreeNode *root);
    TreeNode *search(int);
    void insert(int);
    void remove(int);
    void printTree()
    {
        inOrder(root);
        cout << endl;
    }
};

BinarySearchTree::BinarySearchTree(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    root = buildTree(nums, 0, nums.size()-1);
}

BinarySearchTree::~BinarySearchTree()
{
    freeBinaryTree(root);
}

/* 构建二叉搜索树 */
TreeNode *BinarySearchTree::buildTree(vector<int> &nums, int beg, int end)  
//传进来的需要是有序数组
{
    if(beg > end)
        return nullptr;
    int mid = (beg + end) / 2;
    TreeNode *root = new TreeNode(nums[mid]);
    root->left = buildTree(nums, beg, mid - 1);
    root->right = buildTree(nums, mid + 1, end);
    return root;
}

void BinarySearchTree::freeBinaryTree(TreeNode *root)
{
    if(root == nullptr)
        return;
    freeBinaryTree(root->left);
    freeBinaryTree(root->right);
    delete root;
}

TreeNode *BinarySearchTree::search(int val)
{
    TreeNode *cur = root;
    while (cur != nullptr)
    {
        if(cur->val < val)
        {
            cur = cur->right;
        }
        else if(cur->val > val)
        {
            cur = cur->left;
        }
        else
            break;
    }
    return cur;
}

void BinarySearchTree::insert(int val)
{
    if(root == nullptr) //如果是空树则直接返回
        return;
    TreeNode *cur = root, *pre = nullptr;
    while(cur != nullptr)
    {
        pre = cur;
        if(cur->val < val)
            cur = cur->right;
        else if(cur->val > val)
            cur = cur->left;
        else// 如果插入的是重复元素则直接返回
            return;
    }
    TreeNode *p = new TreeNode(val);
    if(pre->val < val)
        pre->right = p;
    else
        pre->left = p;
}

void BinarySearchTree::remove(int val)
{
    if(root == nullptr)
        return;
    TreeNode *cur = root, *pre = nullptr;
    while(cur != nullptr)
    {
        if(cur->val == val)
            break;
        pre = cur;
        if (cur->val < val)
            cur = cur->right;
        else
            cur = cur->left;
    }
    if(cur == nullptr)
        return; //如果没有找到要删除的节点则直接返回
    if(cur->left == nullptr || cur->right == nullptr) //当该节点的度为0或1时
    {
        TreeNode *child;
        if(cur->left != nullptr)
            child = cur->left;
        else if(cur->right != nullptr)
            child = cur->right;
        else
            child = nullptr;
        
        if(cur != root)
        {
            if(pre->right == cur)
                pre->right = child;
            else
                pre->left = child;
        }
        else //如果删除的节点为根节点，则重新指定节点
        {
            root = child;
        }
        delete cur;
    }
    else    //度为2时
    {
        TreeNode *temp = cur->right;
        while(temp->left != nullptr)
            temp = temp->left;
        int tmpVal = temp->val;
        cur->val = tmpVal;
        delete temp;
    }
}

int main()
{
    vector<int> v{1, 23, 43, 643, 12, 96, 32, 235, 574, 123, 37};
    BinarySearchTree tree(v);
    tree.printTree();
    tree.insert(2);
    tree.insert(189);
    cout << "After inserting: \n";
    tree.printTree();
    tree.remove(1);
    cout << "After removing: \n";
    tree.printTree();
    return 0;
}
