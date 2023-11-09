#pragma once
#include <iostream>
using namespace std;

//二叉搜索树	数据结构
template<class K>
struct BSTreeNode
{
	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;

	BSTreeNode(const K& key)
		:_left(nullptr)
		,_right(nullptr)
		,_key(key)
	{}
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	bool Insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			return true;
		}
		else
		{
			//找到插入位置
			Node* parent = _root;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else if (cur->_key < key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else
				{
					//相等,插入失败
					return false;
				}
			}

			cur = new Node(key);
			if (parent->_key > key)
			{
				parent->_left = cur;
			}
			else
			{
				parent->_right = cur;
			}
			return true;
		}
	}

	bool Find(const K& key)
	{
		if (_root == nullptr)
		{
			return false;
		}

		Node* cur = _root;
		while (cur)
		{
			if (cur->_key > key)
			{
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else
			{
				return true;
			}
		}

		return false;
	}

	//递归版本
	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	bool _InsertR(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			//root为父节点_left 或 _right的引用,可直接赋值
			root = new Node(key);
			return true;
		}

		if (root->_key > key)
		{
			return _InsertR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _InsertR(root->_right, key);
		}
		else
		{
			return false;
		}
	}

	bool FindR(const K& key)
	{
		return _FindR(_root, key);
	}

	bool _FindR(Node* root, const K& key)
	{
		if (root == nullptr)
			return false;
		
		if (root->_key > key)
		{
			return _FindR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _FindR(root->_right, key);
		}
		else
		{
			return true;
		}
	}


	bool EraseR(const K& key)
	{
		return _EraseR(_root, key);
	}

	bool _EraseR(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			return false;
		}

		if (root->_key > key)
		{
			return _EraseR(root->_left, key);
		}
		else if (root->_key < key)
		{
			return _EraseR(root->_right, key);
		}
		else
		{
			//找到了,开始删除,root
			//单侧为空,引用的妙用
			if (root->_left == nullptr)
			{
				Node* tmp = root;
				root = root->_right;
				delete tmp;
			}
			else if (root->_right == nullptr)
			{
				Node* tmp = root;
				root = root->_left;
				delete tmp;
			}
			else
			{
				//两侧都不为空, 找左子树最大 or 右子树最小
				Node* pmaxLeft = root;
				Node* maxLeft = root->_left;
				while (maxLeft->_right)
				{
					pmaxLeft = maxLeft;
					maxLeft = maxLeft->_right;
				}

				root->_key = maxLeft->_key;
				if (pmaxLeft->_left == maxLeft)
				{
					pmaxLeft->_left = maxLeft->_left;
				}
				else
				{
					pmaxLeft->_right = maxLeft->_left;
				}
				delete maxLeft;
			}

		}
	}

	bool Erase(const K& key)
	{
		if (_root == nullptr)
		{
			cout << "empty!" << endl;
			return false;
		}

		Node* cur = _root;
		Node* parent = _root;
		while (cur)
		{
			//找到key
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else	
			{	
				//debug: 需要排除cur是root情况
				//cur左右子树其中一个为空,父节点继承单个就行
				if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_key > cur->_key)
						{
							parent->_left = cur->_right;
						}
						else
						{
							parent->_right = cur->_right;
						}
					}

					delete cur;
				}
				else if (cur->_right == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_key > cur->_key)
						{
							parent->_left = cur->_left;
						}
						else
						{
							parent->_right = cur->_left;
						}
					}

					delete cur;
				}
				else
				{
					//cur两个子树都不为空,选介于左右子树大小之间的值作为cur子树根节点
					// 左子树 < 左子树最大值 or 右子树最小值 < 右子树
					Node* pmaxLeft = cur;
					Node* maxLeft = cur->_left;
					while (maxLeft->_right)
					{
						pmaxLeft = maxLeft;
						maxLeft = maxLeft->_right;
					}
					cur->_key = maxLeft->_key;

					//maxLeft可能有左子树
					// 1.0
					//if (cur == pmaxLeft)
					//{
					//	pmaxLeft->_left = maxLeft->_left;
					//}
					// 2.0
					if (pmaxLeft->_left == maxLeft)
					{
						pmaxLeft->_left = maxLeft->_left;
					}
					else
					{
						pmaxLeft->_right = maxLeft->_left;
					}
					delete maxLeft;
				}
				return true;
			}
		}

		return false;
	}

	void InOrder()
	{
		//需要this指针才能找到成员,但是this指针也做为函数参数
		//因为this指针原因,成员遍历不能作为缺省参数 -> 子函数解决递归传参
		_InOrder(_root);
		cout << endl;
	}

	//中序遍历
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	//void PreOrder()
	//{
	//	//需要this指针才能找到成员,但是this指针也做为函数参数
	//	//因为this指针原因,成员遍历不能作为缺省参数 -> 子函数解决递归传参
	//	_InOrder(_root);
	//	cout << endl;
	//}

	////中序遍历
	//void _PreOrder(Node* root)
	//{
	//	if (root == nullptr)
	//	{
	//		return;
	//	}

	//	cout << root->_key << " ";
	//	_PreOrder(root->_left);
	//	_PreOrder(root->_right);
	//}

private:
	Node* _root = nullptr;
};
