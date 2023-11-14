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

//����������
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
		v.resize(level);	//debug,ʹ��resize()����,Ԫ��Ϊvector<int>,����û��Ԫ��
	}

	v[level - 1].push_back(root->_key);

	//�ݹ�
	_LevelOrder(v, root->_left, level + 1);
	_LevelOrder(v, root->_right, level + 1);
}

vector<vector<int>> levelOrder(TreeNode* root)
{
	//�������
	if (nullptr == root)
		return vector<vector<int>>();

	vector<vector<int>> v;
	int level = 1;
	v.resize(level);
	_LevelOrder(v, root, level);

	return v;
}



void testVector()
{
	vector<vector<int>> v;
	//v.reserve(3);					//����,����û������,����size����
	//v.resize(3, vector<int>());	//��,��ȻҪ����
	v.resize(3);					//�ȼ�
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

		//���������洢������
		vector<TreeNode*> v;
		_Convert(root, v);

		print(v);
		cout << v.size() << endl;

		for (auto e : v)
		{
			cout << e->_key << " ";
		}
		cout << endl;


		//��������ǰ��Ԫ��ָ��
		TreeNode* prev = nullptr;
		TreeNode* cur = v[0];
		TreeNode* next = nullptr;
		cout << "-----" << endl;
		//���������    debug
		//std::vector<TreeNode*>::iterator it = v.begin();
		// auto it = v.begin();
		// cout<<v[0]->_key;
		// cout<<(it->_key)<<endl;   

		for (int i = 0; i < v.size(); i++)
		{
			//cout<<"i:"<<i<<" ";
			cout << v[i]->_key << " ";

			//��ʼ����
			if (i != 0)
				prev = cur;
			//
			cur = v[i];
			//ĩβ����
			if (i + 1 < v.size())
				next = v[i + 1];
			else
				next = nullptr;

			//����
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


void testBStree5()
{
	Key_Value::BSTree<string, int> cTree;
	//ͳ��ˮ�����ִ���
	string arr[] = { "ƻ��", "����", "ƻ��", "����", "ƻ��", "ƻ��", "����",
   "ƻ��", "�㽶", "ƻ��", "�㽶" };

	for (auto str : arr)
	{
		//����û��д������,��������ԭ��ָ��
		Key_Value::BSTree<string, int>::Node* ret = cTree.Find(str);
		//auto ret = cTree.Find(str);
		if (ret == nullptr)
		{
			cTree.Insert(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}
	cTree.InOrder();
	Key_Value::BSTree<string, int> cp(cTree);
	cout << "copy:" << endl;
	cp.InOrder();


	// �ֵ�
	Key_Value::BSTree<string, string> dict;
	dict.Insert("string", "�ַ���");
	dict.Insert("tree", "��");
	dict.Insert("left", "��ߡ�ʣ��");
	dict.Insert("right", "�ұ�");
	dict.Insert("sort", "����");
	dict.Insert("tensor", "����");
	dict.Insert("alpha", "������");

	dict.InOrder();

	string input;
	//�˳�: ctrl+c(����kill�ź�)  or ctrl+z(����EOF,�ļ���������)
	while (cin >> input)
	{
		auto ret = dict.Find(input);
		if(ret)
			cout << ret->_value << endl;
		else
		{
			cout << "not find." << endl;
		}
	}

}

void testBStree6()
{
	Key::BSTree<int> b;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };

	for (auto arr : a)
	{
		b.InsertR(arr);
	}
	b.InOrder();

	Key::BSTree<int> copy(b);
	copy.InOrder();

	Key::BSTree<int> b2;
	int arr2[] = { 6, 4, 7, 14, 13 };
	for (auto arr : arr2)
	{
		b2.InsertR(arr);
	}
	b2.InOrder();

	b2 = b;
	b2.InOrder();
}


int main()
{
	//testBSTree4();
	//testVector();
	testBStree5();

	return 0;
}
