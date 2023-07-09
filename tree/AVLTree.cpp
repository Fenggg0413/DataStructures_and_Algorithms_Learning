#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct TreeNode
{
    int val;
    int height; //节点高度
    TreeNode *left, *right;
    TreeNode(int x) : val(x), height(0), left(nullptr), right(nullptr) {}
    TreeNode() = default;
};

class AVLTree
{
private:
    TreeNode *root;

    void inOrder(TreeNode *node)
    {
        if(node == nullptr)
            return;
        inOrder(node->left);
        cout << node->val << " ";
        inOrder(node->right);
    }

    TreeNode *insertHelper(TreeNode *node, int val)
    {
        // 递归终止条件
        if (node == nullptr)
            return new TreeNode(val);

        // 查找插入位置
        if (val < node->val)
        {
            node->left = insertHelper(node->left, val);
        }
        else if (val > node->val)
        {
            node->right = insertHelper(node->right, val);
        }
        else // 不允许插入相同的值
        {
            return node;
        }
        updateHeight(node);
        node = rotate(node); // 至下而上的对每个失衡节点进行旋转
        return node;
    }

    TreeNode *removeHelper(TreeNode *node, int val)
    {
        //如果没有找到要删除的节点，则返回nullptr
        if(node == nullptr)
            return nullptr;
        
        if(val < node->val)
        {
            node->left = removeHelper(node->left, val);
        }
        else if(val > node->val)
        {
            node->right = removeHelper(node->right, val);
        }
        else //找到节点
        {
            if(node->left == nullptr || node->right == nullptr)
            {
                TreeNode *child = node->left != nullptr ? node->left : node->right;
                if(child == nullptr)
                { 
                    // 子节点数量 = 0 ，直接删除 node 并返回
                    delete node;
                    return nullptr;
                }
                else
                {
                    // 子节点数量 = 1 ，直接删除 node
                    delete node;
                    node = child;
                }
            }
            else
            {
                // 子节点数量 = 2 ，则将中序遍历的下个节点删除，并用该节点替换当前节点
                TreeNode *temp = node->right;
                while(temp->left != nullptr)
                    temp = temp->left;
                int tempVal = temp->val;
                node->right = removeHelper(node->right, temp->val);
                node->val = tempVal;
            }
        }
        updateHeight(node);
        node = rotate(node);
        return node;
    }

    //右旋
    TreeNode *rightRotate(TreeNode *node)
    {
        TreeNode *child = node->left;
        TreeNode *grandChild = child->right;
        child->right = node;
        node->left = grandChild;
        updateHeight(node);
        updateHeight(child);
        return child;
    }

    //左旋
    TreeNode *leftRotate(TreeNode *node)
    {
        TreeNode *child = node->right;
        TreeNode *grandChild = child->left;
        child->left = node;
        node->right = grandChild;
        updateHeight(node);
        updateHeight(child);
        return child;
    }

    //旋转
    TreeNode *rotate(TreeNode *node)
    {
        int _balanceFactor = balanceFactor(node); // 获取平衡因子
        if (_balanceFactor > 1)                   // 平衡因子大于一, 则为左偏树
        {
            if (balanceFactor(node->left) >= 0)
            {
                // 子节点平蘅因子>=0, 直接右旋
                return rightRotate(node);
            }
            else
            {
                // 子节点平蘅因子<0, 先将子节点左旋，后右旋
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        if (_balanceFactor < -1) // 右偏树
        {
            if (balanceFactor(node->right) <= 0)
            {
                // 子节点平蘅因子<=0, 直接左旋
                return leftRotate(node);
            }
            else
            {
                // 子节点平蘅因子>0, 先将子节点右旋, 后左旋
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node; // 平衡树，无须旋转，直接返回
    }

    //构建AVL树
    TreeNode *buildTree(vector<int> &nums, int beg, int end)
    //传进来的需要是有序数组
    {
        if (beg > end)
            return nullptr;
        int mid = (beg + end) / 2;
        TreeNode *node = new TreeNode(nums[mid]);
        node->left = buildTree(nums, beg, mid - 1);
        node->right = buildTree(nums, mid + 1, end);
        updateHeight(node);
        rotate(node);
        return node;
    }

    //递归删除整个树
    void freeBinaryTree(TreeNode *node)
    {
        if (node == nullptr)
            return;
        freeBinaryTree(node->left);
        freeBinaryTree(node->right);
        delete node;
    }

public:
    AVLTree(vector<int> &vec)
    {
        sort(vec.begin(), vec.end());
        root = buildTree(vec, 0, vec.size() - 1);
    }

    ~AVLTree()
    {
        freeBinaryTree(root);
    }
    
    //获取高度
    int getHeight(TreeNode *node)
    {
        return node == nullptr ? -1 : node->height;
    }

    //更新高度
    void updateHeight(TreeNode *node)
    {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    //获取节点的平衡因子
    int balanceFactor(TreeNode *node)
    {
        if(node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    //插入节点
    void insert(int val)
    {
        root = insertHelper(root, val);
    }

    //删除节点
    void remove(int val)
    {
        root = removeHelper(root, val);
    }

    //查找节点
    TreeNode *search(int val)
    {
        TreeNode *node = root;
        while (node != nullptr)
        {
            if(val < node->val)
                node = node->left;
            else if(val > node->val)
                node = node->right;
            else
                break;
        }
        return node;
    }

    //打印树的内容
    void printInfo()
    {
        TreeNode *node = root;
        inOrder(node);
        cout << endl;
    }

    TreeNode* getRoot()
    {
        return root;
    }
};

int main()
{
    vector<int> v{0, 1, 2, 3, 4, 5, 6, 78, 65, 39};
    AVLTree tree(v);
    tree.printInfo();
    TreeNode *node = tree.getRoot();
    tree.remove(39);
    tree.printInfo();
    cout << "node's height: " << node->height << ", node's val: " << node->val
         << ", node's balanceFactor: " << tree.balanceFactor(node) << endl;
    node = node->right;
    cout << "node's height: " << node->height << ", node's val: " << node->val
         << ", node's balanceFactor: " << tree.balanceFactor(node) << endl;
}