#define _CRT_SECURE_NO_WARNINGS

//OJ练习

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

//根据二叉树创建字符串
class Solution {
public:
    string tree2str(TreeNode* root) {
        if (root == nullptr)
            return "";

        string str = to_string(root->val);
        if (root->left || root->right)
        {
            str += "(";
            str += tree2str(root->left);
            str += ")";
        }

        if (root->right)
        {
            str += "(";
            str += tree2str(root->right);
            str += ")";
        }

        return str;
    }
};

// 二叉树的层序遍历
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr)
        {
            return vector<vector<int>>();
        }
        //层序遍历
        vector<vector<int>> v;
        v.resize(1);
        int level = 1;
        _LevelOrder(v, root, level);
        return v;
    }

    void _LevelOrder(vector<vector<int>>& v, TreeNode* root, int level)
    {
        if (root == nullptr)
        {
            return;
        }
        if (v.size() < level)
        {
            v.resize(level);
        }
        // cout<<level<<" ";
        v[level - 1].push_back(root->val);

        //递归
        _LevelOrder(v, root->left, level + 1);
        _LevelOrder(v, root->right, level + 1);
    }
};

//二叉树的层序遍历 II
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if (root == nullptr)
        {
            return vector<vector<int>>();
        }
        //层序遍历
        vector<vector<int>> v;
        v.resize(1);
        int level = 1;
        _levelOrderBottom(v, root, level);
        reverse(v.begin(), v.end());
        return v;
    }

    void _levelOrderBottom(vector<vector<int>>& v, TreeNode* root, int level)
    {
        if (root == nullptr)
        {
            return;
        }
        //注意是用resize,不是reverse,后者只扩容,不改元素个数
        if (v.size() < level)
        {
            v.resize(level);
        }

        v[level - 1].push_back(root->val);

        //递归
        _levelOrderBottom(v, root->left, level + 1);
        _levelOrderBottom(v, root->right, level + 1);
    }
};

//二叉树的最近公共祖先
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* ance = root;
        _lowestCommonAncestor(root, p, q, ance);
        return ance;
    }

    void _lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& ance)
    {
        if (nullptr == root)
            return;

        //是下一层公共祖先,更新
        if (find(root, p) && find(root, q))
            ance = root;

        _lowestCommonAncestor(root->left, p, q, ance);
        _lowestCommonAncestor(root->right, p, q, ance);
    }

    //找某个元素
    bool find(TreeNode* root, TreeNode* key)
    {
        if (nullptr == root)
            return false;

        if (root == key)
            return true;

        return find(root->left, key) || find(root->right, key);
    }
};

//从前序与中序遍历序列构造二叉树
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

        TreeNode* root;
        _buildTree(preorder, inorder, root);
        return root;
    }

    void _buildTree(vector<int>& preorder, vector<int>& inorder, TreeNode*& root)
    {
        if (inorder.size() <= 1 && preorder.size() <= 1)
        {
            if (inorder.size() == 0)
                return;

            //引用,解决初始左右节点为空问题
            TreeNode* node = new TreeNode(preorder[0]);
            root = node;
            return;
        }

        //子树根节点处理
        int rootVal = preorder[0];
        TreeNode* _root = new TreeNode(rootVal);

        //拆分区间,左子树元素 根 右子树元素
        int left_size = 1;
        vector<int> in_left, in_right, pre_left, pre_right;
        if (inorder.size() > 1)
        {
            //匿名对象,利用迭代器区间初始化构造
            auto in_left_end = find(inorder.begin(), inorder.end(), rootVal);
            in_left = vector<int>(inorder.begin(), in_left_end);
            in_right = vector<int>(++in_left_end, inorder.end());

            int left_size = in_left.size();
            pre_left = vector<int>(++preorder.begin(), ++preorder.begin() + left_size);
            pre_right = vector<int>(++preorder.begin() + left_size, preorder.end());
        }

        _buildTree(pre_left, in_left, _root->left);
        _buildTree(pre_right, in_right, _root->right);
        root = _root;
        return;
    }

};


//从中序与后序遍历序列构造二叉树
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        TreeNode* root;
        _buildTree(inorder, postorder, root);
        return root;
    }

    void _buildTree(vector<int>& inorder, vector<int>& postorder, TreeNode*& root)
    {
        //递归结束条件
        if (inorder.size() <= 1)
        {
            if (inorder.size() == 0)
                return;

            root = new TreeNode(inorder[0]);
            return;
        }

        //划分区间,子树根节点处理
        int rootVal = postorder[postorder.size() - 1];
        TreeNode* _root = new TreeNode(rootVal);
        vector<int> inLeft, inRight, postLeft, postRight;
        if (inorder.size() > 1)
        {   //迭代器区间,左闭右开
            auto midRoot = find(inorder.begin(), inorder.end(), rootVal);
            inLeft = vector<int>(inorder.begin(), midRoot);
            inRight = vector<int>(midRoot + 1, inorder.end());

            int leftSize = inLeft.size();
            postLeft = vector<int>(postorder.begin(), postorder.begin() + leftSize);
            postRight = vector<int>(postorder.begin() + leftSize, postorder.end() - 1);
        }

        //递归
        _buildTree(inLeft, postLeft, _root->left);
        _buildTree(inRight, postRight, _root->right);
        //链接根节点!
        root = _root;
        return;
    }
};

//非递归遍历
//二叉树的前序遍历
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();

        //非递归, 利用数据结构栈LIFO
        stack<TreeNode*> st;
        st.push(root);
        vector<int> v;

        while (!st.empty())
        {
            TreeNode* top = st.top();
            st.pop();
            v.push_back(top->val);
            //注意顺序
            if (top->right)
                st.push(top->right);
            if (top->left)
                st.push(top->left);
        }
        return v;
    }
};

//二叉树的中序遍历
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();

        //非递归, 利用数据结构栈LIFO
        //利用两个栈,一个节点,一个数据
        stack<int> stVal;
        stack<TreeNode*> stNode;
        stNode.push(root);
        vector<int> v;

        while (!stNode.empty())
        {
            //注意避免栈为空调用 .top()
            while (!stNode.empty() && stNode.top() == nullptr)
            {
                // cout<<"地址:"<<stNode.top()<<" ";
                if (!stVal.empty())
                {
                    // cout<<"val:"<<stVal.top()<<" ";
                    v.push_back(stVal.top());
                    stVal.pop();
                }
                stNode.pop();
            }
            // cout<<endl;
            if (stNode.empty())
            {
                break;
            }

            TreeNode* top = stNode.top();
            stNode.pop();
            if (top)
            {
                // cout<<top->val<<" ";
                stVal.push(top->val);
                //存入空指针,为了判断顺序
                stNode.push(top->right);
                stNode.push(top->left);
            }
        }

        return v;
    }
};