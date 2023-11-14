#pragma once
#include <iostream>
using namespace std;

//二叉搜索树	数据结构
namespace Key
{
	template<class K>
	struct BSTreeNode
	{
		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}
	};

	template<class K>
	class BSTree
	{
		typedef BSTreeNode<K> Node;
	public:
		// 默认构造, 显示写了构造(拷贝构造),编译器就不生成默认构造,可以用default强制生成
		BSTree() = default; 

		BSTree(const BSTree<K>& b)
		{
			CopyTree(_root, b._root);
		}

		~BSTree()
		{
			//cout << "~BSTree()" << endl;
			DestoryTree(_root);
		}

		BSTree<K>& operator=(BSTree<K> b)
		{
			//拷贝后的b,不用判断if(&b != this);本就不同
			//this->_root换到临时对象b,调用结束,被析构了
			std::swap(_root, b._root);
			return *this;
		}

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
					// 找到了_key,开始删除
					// 1.cur左右子树其中一个为空,父节点继承单个就行
					// 2.cur左右子树都不为空,找一个可以替代父节点的替代节点赋值父节点,然后删除替代节点
					// 替代节点: 左子树的最大值 or 右子树的最小值 -- 问题转化为1.

					// debug: 需要排除cur是root情况,解决:更换root节点
					// 1.cur左右子树其中一个为空,父节点继承单个就行
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
						// 2.cur左右子树都不为空,找一个可以替代父节点的替代节点赋值父节点,然后删除替代节点
						Node* pmaxLeft = cur;
						Node* maxLeft = cur->_left;
						while (maxLeft->_right)
						{
							pmaxLeft = maxLeft;
							maxLeft = maxLeft->_right;
						}
						cur->_key = maxLeft->_key;

						//maxLeft可能有左子树
						// 2.0
						if (pmaxLeft->_left == maxLeft)	//cur == pmaxLeft
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
			//因为this指针原因,成员不能作为缺省参数 -> 子函数解决递归传参
			_InOrder(_root);
			cout << endl;
		}

		//递归版本
		bool InsertR(const K& key)
		{
			return _InsertR(_root, key);
		}

		bool EraseR(const K& key)
		{
			return _EraseR(_root, key);
		}

		bool FindR(const K& key)
		{
			return _FindR(_root, key);
		}

	protected:
		// 注意引用传参
		void CopyTree(Node*& copy, Node* cur)
		{
			if (cur == nullptr)
				return;

			copy = new Node(cur->_key);
			CopyTree(copy->_left, cur->_left);
			CopyTree(copy->_right, cur->_right);
		}

		void DestoryTree(Node* cur)
		{
			if (cur == nullptr)
				return;
			//后序遍历
			DestoryTree(cur->_left);
			DestoryTree(cur->_right);
			//cout << cur->_key << endl;
			delete cur;
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
				Node* del = root;
				if (root->_left == nullptr)
				{
					root = root->_right;
				}
				else if (root->_right == nullptr)
				{
					root = root->_left;
				}
				else
				{
					//两侧都不为空, 找左子树最大 or 右子树最小
					Node* maxLeft = root->_left;
					while (maxLeft->_right)
					{
						maxLeft = maxLeft->_right;
					}

					swap(root->_key, maxLeft->_key);
					_EraseR(root->_left, key);	//交换后root->_key < key; 只能去左子树删除
				}
				delete del;
			}
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

	private:
		Node* _root = nullptr;
	};
}

namespace Key_Value
{
	//搜索二叉树	数据结构
	template<class K, class V>
	struct BSTreeNode
	{
		BSTreeNode<K, V>* _left;
		BSTreeNode<K, V>* _right;
		K _key;
		V _value;

		BSTreeNode(const K& key, const V& value)
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{}
	};

	template<class K, class V>
	class BSTree
	{
	public:
		typedef BSTreeNode<K, V> Node;

		// 默认构造, 显示写了构造(拷贝构造),编译器就不生成默认构造,可以用default强制生成
		BSTree() = default;

		BSTree(const BSTree<K, V>& b)
		{
			CopyTree(_root, b._root);
		}

		~BSTree()
		{
			DestoryTree(_root);
		}

		BSTree<K, V>& operator=(BSTree<K, V> b)
		{
			//拷贝后的b,不用判断if(&b != this);本就不同
			//this->_root换到临时对象b,调用结束,被析构了
			std::swap(_root, b._root);
			return *this;
		}

		bool Insert(const K& key, const V& value)
		{
			if (_root == nullptr)
			{
				_root = new Node(key, value);
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

				cur = new Node(key, value);
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

		Node* Find(const K& key)
		{
			if (_root == nullptr)
			{
				return nullptr;
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
					return cur;
				}
			}

			return nullptr;
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
					// 1.cur左右子树其中一个为空
					// debug: 需要排除cur是root情况,更换root节点
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
						// 2.cur左右子树都不为空,选介于左右子树大小之间的值作为cur子树根节点
						// 左子树 < 父节点 < 右子树
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
						// 2.0
						if (pmaxLeft->_left == maxLeft)	//当pmaxLeft == cur
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

		//中序遍历	遍历结果正好是升序
		void InOrder()
		{
			//需要this指针才能找到成员,但是this指针也做为函数参数
			//因为this指针原因,成员遍历不能作为缺省参数 -> 子函数解决递归传参
			_InOrder(_root);
			cout << endl;
		}

		void _InOrder(Node* root)
		{
			if (root == nullptr)
			{
				return;
			}

			_InOrder(root->_left);
			cout << root->_key << ": " << root->_value << endl;
			_InOrder(root->_right);
		}

	protected:
		// 注意引用传参
		void CopyTree(Node*& copy, Node* cur)
		{
			if (cur == nullptr)
				return;

			copy = new Node(cur->_key, cur->_value);
			CopyTree(copy->_left, cur->_left);
			CopyTree(copy->_right, cur->_right);
		}

		void DestoryTree(Node* cur)
		{
			if (cur == nullptr)
				return;
			//后序遍历
			DestoryTree(cur->_left);
			DestoryTree(cur->_right);
			delete cur;
		}

	private:
		Node* _root = nullptr;
	};

}