#pragma once
#include <iostream>
using namespace std;

//����������	���ݽṹ
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
			//�ҵ�����λ��
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
					//���,����ʧ��
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

	//�ݹ�汾
	bool InsertR(const K& key)
	{
		return _InsertR(_root, key);
	}

	bool _InsertR(Node*& root, const K& key)
	{
		if (root == nullptr)
		{
			//rootΪ���ڵ�_left �� _right������,��ֱ�Ӹ�ֵ
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
			//�ҵ���,��ʼɾ��,root
			//����Ϊ��,���õ�����
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
				//���඼��Ϊ��, ����������� or ��������С
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
			//�ҵ�key
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
				//debug: ��Ҫ�ų�cur��root���
				//cur������������һ��Ϊ��,���ڵ�̳е�������
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
					//cur������������Ϊ��,ѡ��������������С֮���ֵ��Ϊcur�������ڵ�
					// ������ < ���������ֵ or ��������Сֵ < ������
					Node* pmaxLeft = cur;
					Node* maxLeft = cur->_left;
					while (maxLeft->_right)
					{
						pmaxLeft = maxLeft;
						maxLeft = maxLeft->_right;
					}
					cur->_key = maxLeft->_key;

					//maxLeft������������
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
		//��Ҫthisָ������ҵ���Ա,����thisָ��Ҳ��Ϊ��������
		//��Ϊthisָ��ԭ��,��Ա����������Ϊȱʡ���� -> �Ӻ�������ݹ鴫��
		_InOrder(_root);
		cout << endl;
	}

	//�������
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
	//	//��Ҫthisָ������ҵ���Ա,����thisָ��Ҳ��Ϊ��������
	//	//��Ϊthisָ��ԭ��,��Ա����������Ϊȱʡ���� -> �Ӻ�������ݹ鴫��
	//	_InOrder(_root);
	//	cout << endl;
	//}

	////�������
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
