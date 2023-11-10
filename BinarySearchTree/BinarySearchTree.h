#pragma once
#include <iostream>
#include <queue>
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

		//��ʱ�ṩroot
		Node* GetRoot()
		{
			return _root;
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

		//�������
		void LevelOrder()
		{
			if (_root == nullptr)
				return;

			queue<Node*> qNode;
			qNode.push(_root);	
			while (!qNode.empty())
			{
				cout << qNode.front()->_key << " ";
				if (qNode.front()->_left)
				{
					qNode.push(qNode.front()->_left);

				}
				if (qNode.front()->_right)
				{
					qNode.push(qNode.front()->_right);
				}
				qNode.pop();
			}

			cout << endl;
		}

		//�ݹ�д��
		//if (root == nullptr)
		//{
		//	return;
		//}

		//while (qNode.front() == nullptr)
		//{
		//	qNode.pop();
		//}
		//
		//qNode.push(qNode.front()->_left);
		//qNode.push(qNode.front()->_right);
		//qNode.pop();

		////�ݹ�
		//_LevelOrder(root->_left,qNode, level + 1);
		//_LevelOrder(root->_right,qNode, level + 1);

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
		typedef BSTreeNode<K, V> Node;
	public:
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

	private:
		Node* _root = nullptr;
	};

}