#pragma once
#include <iostream>
using namespace std;

//����������	���ݽṹ
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
		// Ĭ�Ϲ���, ��ʾд�˹���(��������),�������Ͳ�����Ĭ�Ϲ���,������defaultǿ������
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
			//�������b,�����ж�if(&b != this);���Ͳ�ͬ
			//this->_root������ʱ����b,���ý���,��������
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
					// �ҵ���_key,��ʼɾ��
					// 1.cur������������һ��Ϊ��,���ڵ�̳е�������
					// 2.cur������������Ϊ��,��һ������������ڵ������ڵ㸳ֵ���ڵ�,Ȼ��ɾ������ڵ�
					// ����ڵ�: �����������ֵ or ����������Сֵ -- ����ת��Ϊ1.

					// debug: ��Ҫ�ų�cur��root���,���:����root�ڵ�
					// 1.cur������������һ��Ϊ��,���ڵ�̳е�������
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
						// 2.cur������������Ϊ��,��һ������������ڵ������ڵ㸳ֵ���ڵ�,Ȼ��ɾ������ڵ�
						Node* pmaxLeft = cur;
						Node* maxLeft = cur->_left;
						while (maxLeft->_right)
						{
							pmaxLeft = maxLeft;
							maxLeft = maxLeft->_right;
						}
						cur->_key = maxLeft->_key;

						//maxLeft������������
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
			//��Ҫthisָ������ҵ���Ա,����thisָ��Ҳ��Ϊ��������
			//��Ϊthisָ��ԭ��,��Ա������Ϊȱʡ���� -> �Ӻ�������ݹ鴫��
			_InOrder(_root);
			cout << endl;
		}

		//�ݹ�汾
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
		// ע�����ô���
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
			//�������
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
				//�ҵ���,��ʼɾ��,root
				//����Ϊ��,���õ�����
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
					//���඼��Ϊ��, ����������� or ��������С
					Node* maxLeft = root->_left;
					while (maxLeft->_right)
					{
						maxLeft = maxLeft->_right;
					}

					swap(root->_key, maxLeft->_key);
					_EraseR(root->_left, key);	//������root->_key < key; ֻ��ȥ������ɾ��
				}
				delete del;
			}
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

	private:
		Node* _root = nullptr;
	};
}

namespace Key_Value
{
	//����������	���ݽṹ
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

		// Ĭ�Ϲ���, ��ʾд�˹���(��������),�������Ͳ�����Ĭ�Ϲ���,������defaultǿ������
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
			//�������b,�����ж�if(&b != this);���Ͳ�ͬ
			//this->_root������ʱ����b,���ý���,��������
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
					// 1.cur������������һ��Ϊ��
					// debug: ��Ҫ�ų�cur��root���,����root�ڵ�
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
						// 2.cur������������Ϊ��,ѡ��������������С֮���ֵ��Ϊcur�������ڵ�
						// ������ < ���ڵ� < ������
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
						// 2.0
						if (pmaxLeft->_left == maxLeft)	//��pmaxLeft == cur
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

		//�������	�����������������
		void InOrder()
		{
			//��Ҫthisָ������ҵ���Ա,����thisָ��Ҳ��Ϊ��������
			//��Ϊthisָ��ԭ��,��Ա����������Ϊȱʡ���� -> �Ӻ�������ݹ鴫��
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
		// ע�����ô���
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
			//�������
			DestoryTree(cur->_left);
			DestoryTree(cur->_right);
			delete cur;
		}

	private:
		Node* _root = nullptr;
	};

}