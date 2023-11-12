//#define _CRT_SECURE_NO_WARNINGS
//
////OJ��ϰ
//
///**
// * Definition for a binary tree node.
// * struct TreeNode {
// *     int val;
// *     TreeNode *left;
// *     TreeNode *right;
// *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
// *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
// *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
// * };
// */
//
////���ݶ����������ַ���
//class Solution {
//public:
//    string tree2str(TreeNode* root) {
//        if (root == nullptr)
//            return "";
//
//        string str = to_string(root->val);
//        if (root->left || root->right)
//        {
//            str += "(";
//            str += tree2str(root->left);
//            str += ")";
//        }
//
//        if (root->right)
//        {
//            str += "(";
//            str += tree2str(root->right);
//            str += ")";
//        }
//
//        return str;
//    }
//};
//
//// �������Ĳ������
//class Solution {
//public:
//    vector<vector<int>> levelOrder(TreeNode* root) {
//        if (root == nullptr)
//        {
//            return vector<vector<int>>();
//        }
//        //�������
//        vector<vector<int>> v;
//        v.resize(1);
//        int level = 1;
//        _LevelOrder(v, root, level);
//        return v;
//    }
//
//    void _LevelOrder(vector<vector<int>>& v, TreeNode* root, int level)
//    {
//        if (root == nullptr)
//        {
//            return;
//        }
//        if (v.size() < level)
//        {
//            v.resize(level);
//        }
//        // cout<<level<<" ";
//        v[level - 1].push_back(root->val);
//
//        //�ݹ�
//        _LevelOrder(v, root->left, level + 1);
//        _LevelOrder(v, root->right, level + 1);
//    }
//};
//
////�������Ĳ������ II
//class Solution {
//public:
//    vector<vector<int>> levelOrderBottom(TreeNode* root) {
//        if (root == nullptr)
//        {
//            return vector<vector<int>>();
//        }
//        //�������
//        vector<vector<int>> v;
//        v.resize(1);
//        int level = 1;
//        _levelOrderBottom(v, root, level);
//        reverse(v.begin(), v.end());
//        return v;
//    }
//
//    void _levelOrderBottom(vector<vector<int>>& v, TreeNode* root, int level)
//    {
//        if (root == nullptr)
//        {
//            return;
//        }
//        //ע������resize,����reverse,����ֻ����,����Ԫ�ظ���
//        if (v.size() < level)
//        {
//            v.resize(level);
//        }
//
//        v[level - 1].push_back(root->val);
//
//        //�ݹ�
//        _levelOrderBottom(v, root->left, level + 1);
//        _levelOrderBottom(v, root->right, level + 1);
//    }
//};
//
////�������������������
//class Solution {
//public:
//    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//        TreeNode* ance = root;
//        _lowestCommonAncestor(root, p, q, ance);
//        return ance;
//    }
//
//    void _lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& ance)
//    {
//        if (nullptr == root)
//            return;
//
//        //����һ�㹫������,����
//        if (find(root, p) && find(root, q))
//            ance = root;
//
//        _lowestCommonAncestor(root->left, p, q, ance);
//        _lowestCommonAncestor(root->right, p, q, ance);
//    }
//
//    //��ĳ��Ԫ��
//    bool find(TreeNode* root, TreeNode* key)
//    {
//        if (nullptr == root)
//            return false;
//
//        if (root == key)
//            return true;
//
//        return find(root->left, key) || find(root->right, key);
//    }
//};
//
////��ǰ��������������й��������
//class Solution {
//public:
//    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
//
//        TreeNode* root;
//        _buildTree(preorder, inorder, root);
//        return root;
//    }
//
//    void _buildTree(vector<int>& preorder, vector<int>& inorder, TreeNode*& root)
//    {
//        if (inorder.size() <= 1 && preorder.size() <= 1)
//        {
//            if (inorder.size() == 0)
//                return;
//
//            //����,�����ʼ���ҽڵ�Ϊ������
//            TreeNode* node = new TreeNode(preorder[0]);
//            root = node;
//            return;
//        }
//
//        //�������ڵ㴦��
//        int rootVal = preorder[0];
//        TreeNode* _root = new TreeNode(rootVal);
//
//        //�������,������Ԫ�� �� ������Ԫ��
//        int left_size = 1;
//        vector<int> in_left, in_right, pre_left, pre_right;
//        if (inorder.size() > 1)
//        {
//            //��������,���õ����������ʼ������
//            auto in_left_end = find(inorder.begin(), inorder.end(), rootVal);
//            in_left = vector<int>(inorder.begin(), in_left_end);
//            in_right = vector<int>(++in_left_end, inorder.end());
//
//            int left_size = in_left.size();
//            pre_left = vector<int>(++preorder.begin(), ++preorder.begin() + left_size);
//            pre_right = vector<int>(++preorder.begin() + left_size, preorder.end());
//        }
//
//        _buildTree(pre_left, in_left, _root->left);
//        _buildTree(pre_right, in_right, _root->right);
//        root = _root;
//        return;
//    }
//
//};
//
//
////�����������������й��������
//class Solution {
//public:
//    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
//        TreeNode* root;
//        _buildTree(inorder, postorder, root);
//        return root;
//    }
//
//    void _buildTree(vector<int>& inorder, vector<int>& postorder, TreeNode*& root)
//    {
//        //�ݹ��������
//        if (inorder.size() <= 1)
//        {
//            if (inorder.size() == 0)
//                return;
//
//            root = new TreeNode(inorder[0]);
//            return;
//        }
//
//        //��������,�������ڵ㴦��
//        int rootVal = postorder[postorder.size() - 1];
//        TreeNode* _root = new TreeNode(rootVal);
//        vector<int> inLeft, inRight, postLeft, postRight;
//        if (inorder.size() > 1)
//        {   //����������,����ҿ�
//            auto midRoot = find(inorder.begin(), inorder.end(), rootVal);
//            inLeft = vector<int>(inorder.begin(), midRoot);
//            inRight = vector<int>(midRoot + 1, inorder.end());
//
//            int leftSize = inLeft.size();
//            postLeft = vector<int>(postorder.begin(), postorder.begin() + leftSize);
//            postRight = vector<int>(postorder.begin() + leftSize, postorder.end() - 1);
//        }
//
//        //�ݹ�
//        _buildTree(inLeft, postLeft, _root->left);
//        _buildTree(inRight, postRight, _root->right);
//        //���Ӹ��ڵ�!
//        root = _root;
//        return;
//    }
//};
//
////�ǵݹ����
////��������ǰ�����
//class Solution {
//public:
//    vector<int> preorderTraversal(TreeNode* root) {
//        if (root == nullptr)
//            return vector<int>();
//
//        //�ǵݹ�, �������ݽṹջLIFO
//        stack<TreeNode*> st;
//        st.push(root);
//        vector<int> v;
//
//        while (!st.empty())
//        {
//            TreeNode* top = st.top();
//            st.pop();
//            v.push_back(top->val);
//            //ע��˳��
//            if (top->right)
//                st.push(top->right);
//            if (top->left)
//                st.push(top->left);
//        }
//        return v;
//    }
//};
//
////���������������
//class Solution {
//public:
//    vector<int> inorderTraversal(TreeNode* root) {
//        if (root == nullptr)
//            return vector<int>();
//
//        //�ǵݹ�, �������ݽṹջLIFO
//        //��������ջ,һ���ڵ�,һ������
//        stack<int> stVal;
//        stack<TreeNode*> stNode;
//        stNode.push(root);
//        vector<int> v;
//
//        while (!stNode.empty())
//        {
//            //ע�����ջΪ�յ��� .top()
//            while (!stNode.empty() && stNode.top() == nullptr)
//            {
//                // cout<<"��ַ:"<<stNode.top()<<" ";
//                if (!stVal.empty())
//                {
//                    // cout<<"val:"<<stVal.top()<<" ";
//                    v.push_back(stVal.top());
//                    stVal.pop();
//                }
//                stNode.pop();
//            }
//            // cout<<endl;
//            if (stNode.empty())
//            {
//                break;
//            }
//
//            TreeNode* top = stNode.top();
//            stNode.pop();
//            if (top)
//            {
//                // cout<<top->val<<" ";
//                stVal.push(top->val);
//                //�����ָ��,Ϊ���ж�˳��
//                stNode.push(top->right);
//                stNode.push(top->left);
//            }
//        }
//
//        return v;
//    }
//};
//
//
////�������ĺ������
//class Solution {
//public:
//    vector<int> postorderTraversal(TreeNode* root) {
//        //�ǵݹ�
//        if (nullptr == root)
//            return vector<int>();
//
//        stack<int> stVal;
//        stack<TreeNode*> stNode;
//        vector<int> v;
//        stNode.push(root);
//        //����,ֻ������,��;��������
//        while (!stNode.empty())
//        {
//            TreeNode* top = stNode.top();
//            stNode.pop();
//            stVal.push(top->val);
//
//            //˳�����
//            if (top->left)
//                stNode.push(top->left);
//            if (top->right)
//                stNode.push(top->right);
//        }
//        //�����ȫ������
//        while (!stVal.empty())
//        {
//            v.push_back(stVal.top());
//            stVal.pop();
//        }
//        return v;
//    }
//};
//
////������������˫������ | ����������ת��˫����
////�ݹ�ʵ��
//class Solution {
//public:
//    TreeNode* Convert(TreeNode* root)
//    {
//        //�ο����Լ�д
//        if (root == nullptr)
//            return nullptr;
//        //1.����ʼ�ڵ�
//        TreeNode* begin = root;
//        while (begin->left)
//        {
//            begin = begin->left;
//        }
//        //�޸�ָ��ָ��
//        _Convert(root);
//        return begin;
//    }
//
//    void _Convert(TreeNode* root)
//    {
//        if (root == nullptr)
//            return;
//        //����
//        _Convert(root->left);
//        //��ǰ�ڵ�leftָ��ǰһ���ڵ�
//        root->left = prev;
//        //��һ���ڵ�rightָ��ǰ�ڵ�
//        if (prev)
//            prev->right = root;
//        //������һ���ڵ�:��ǰ�ڵ��Ϊ��һ���ڵ����һ���ڵ�
//        prev = root;
//        _Convert(root->right);
//    }
//
//private:
//    //����֮��,��������,��¼��һ���ڵ�
//    TreeNode* prev = nullptr;
//};
//
//
////��������ʵ��
//class Solution {
//public:
//    TreeNode* Convert(TreeNode* root) {
//        if (root == nullptr)
//            return nullptr;
//
//        //���������洢������
//        vector<TreeNode*> v;
//        _Convert(root, v);
//
//        //��������ǰ��Ԫ��ָ��
//        TreeNode* prev = nullptr;
//        TreeNode* cur = v[0];
//        TreeNode* next = nullptr;
//        for (int i = 0; i < v.size(); i++)
//        {
//            //��ʼ����
//            if (i != 0)
//                prev = cur;
//            //
//            cur = v[i];
//            //ĩβ����
//            if (i + 1 < v.size())
//                next = v[i + 1];
//            else
//                next = nullptr; //debug:����д��Ϊcur
//
//            //����
//            cur->left = prev;
//            cur->right = next;
//        }
//
//        return v[0];
//    }
//
//    void _Convert(TreeNode* root, vector<TreeNode*>& v)
//    {
//        if (root == nullptr)
//            return;
//
//        _Convert(root->left, v);
//        v.push_back(root);
//        _Convert(root->right, v);
//    }
//
//    void print(vector<TreeNode*> v)
//    {
//        //���������,����������->    debug
//        for (auto e : v)
//        {
//            cout << e->val << " ";
//        }
//        cout << endl;
//    }
//
//};
