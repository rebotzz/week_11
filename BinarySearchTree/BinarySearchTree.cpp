#define _CRT_SECURE_NO_WARNINGS
#include "BinarySearchTree.h"
#include <vector>

void testBSTree1()
{
	//int a[] = { 8, 3, 1 };
	//int a[] = { 8, 3, 1, 10 };
	//int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 0, 2, 11, 9 };
	Key::BSTree<int> b;

	for (auto e : a)
	{
		b.Insert(e);
	}

	b.InOrder();
	//b.Erase(0);
	//b.InOrder();
	//b.Erase(13);
	//b.InOrder();
	//b.Erase(3);
	//b.InOrder();
	//b.Erase(17);
	//b.InOrder();

	for (auto e : a)
	{
		cout << e << ": ";
		b.InOrder();
		b.Erase(e);
	}
	b.InOrder();

	//for (int i = 3; i < sizeof(a) / sizeof(a[0]); i++)
	//{
	//	cout << a[i] << ": ";
	//	b.InOrder();
	//	b.Erase(a[i]);
	//}
	//b.InOrder();

}

void testBSTree2()
{
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	Key::BSTree<int> b;

	for (auto e : a)
	{
		b.InsertR(e);
	}
	b.InOrder();

	//cout << b.FindR(14) << endl;
	//cout << b.FindR(15) << endl;
	//cout << b.FindR(1) << endl;
	//cout << b.FindR(7) << endl;


	//b.EraseR(8);
	//b.InOrder();

	//for (auto e : a)
	//{
	//	cout << e << ": ";
	//	b.InOrder();
	//	b.EraseR(e);
	//}
	//b.InOrder();
}

typedef Key::BSTreeNode<int> TreeNode;

//求二叉树深度
int treeDeep(TreeNode* root)
{
	if (nullptr == root)
	{
		return 0;
	}

	int left = treeDeep(root->_left) + 1;
	int right = treeDeep(root->_right) + 1;
	return left > right ? left : right;
}

void _LevelOrder(vector<vector<int>>& v, TreeNode* root, int level)
{
	if (root == nullptr)
	{
		return;
	}
	if (v.size() < level)
	{
		v.resize(level);	//debug,使用resize()扩容,元素为vector<int>,否则没有元素
	}

	v[level - 1].push_back(root->_key);

	//递归
	_LevelOrder(v, root->_left, level + 1);
	_LevelOrder(v, root->_right, level + 1);
}

vector<vector<int>> levelOrder(TreeNode* root)
{
	//层序遍历
	if (nullptr == root)
		return vector<vector<int>>();

	vector<vector<int>> v;
	int level = 1;
	v.resize(level);
	_LevelOrder(v, root, level);

	return v;
}



void testBSTree3()
{
	//int a[] = { 8, 3, 1 };
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	Key::BSTree<int> b;

	for (auto e : a)
	{
		b.InsertR(e);
	}
	b.InOrder();

	b.LevelOrder();
	cout << "deep:" << treeDeep(b.GetRoot()) << endl;

	vector<vector<int>> v = levelOrder(b.GetRoot());

	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v[i].size(); ++j)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}

}

void testVector()
{
	vector<vector<int>> v;
	//v.reserve(3);					//扩容,但是没有数据,所以size不变
	//v.resize(3, vector<int>());	//靠,尽然要这样
	v.resize(3);					//等价
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			v[i].push_back(i + j);
		}
	}

	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v[i].size(); ++j)
		{
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
}





/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
	TreeNode* Convert(TreeNode* root) {
		if (root == nullptr)
			return nullptr;

		//将中序结果存储再数组
		vector<TreeNode*> v;
		_Convert(root, v);

		print(v);
		cout << v.size() << endl;

		for (auto e : v)
		{
			cout << e->_key << " ";
		}
		cout << endl;


		//调整数组前后元素指针
		TreeNode* prev = nullptr;
		TreeNode* cur = v[0];
		TreeNode* next = nullptr;
		cout << "-----" << endl;
		//运算符重载    debug
		//std::vector<TreeNode*>::iterator it = v.begin();
		// auto it = v.begin();
		// cout<<v[0]->_key;
		// cout<<(it->_key)<<endl;   

		 for(int i = 0; i < v.size(); i++)
		 {
		     //cout<<"i:"<<i<<" ";
		     cout<<v[i]->_key<<" ";

		     //初始处理
		     if(i != 0)
		         prev = cur;
		     //
		     cur = v[i];
		     //末尾处理
		     if(i + 1 < v.size())
		         next = v[i + 1];
		     else
		         next = nullptr;

		     //链接
		     cur->_left = prev;
		     cur->_right = next;
		 }

		return v[0];
	}

	void _Convert(TreeNode* root, vector<TreeNode*>& v)
	{
		if (root == nullptr)
			return;

		_Convert(root->_left, v);
		v.push_back(root);
		_Convert(root->_right, v);
	}

	void print(vector<TreeNode*> v)
	{
		for (auto e : v)
		{
			cout << e->_key << " ";
		}
		cout << endl;
	}

};


void testBSTree4()
{
	//int a[] = { 8, 3, 1 };
	int a[] = { 10,6,14,4,8,12,16 };
	Key::BSTree<int> b;

	for (auto e : a)
	{
		b.Insert(e);
	}
	b.InOrder();

	Solution().Convert(b.GetRoot());

}

int main()
{
	testBSTree4();
	//testVector();


	return 0;
}
