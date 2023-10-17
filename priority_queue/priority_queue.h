#pragma once
#include <iostream>
#include <vector>
#include <deque>
#include "Date.h"
using namespace std;

namespace kozen
{
	//�º���(��������)
	template<class T>
	struct Less
	{
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<class T>
	struct Greater
	{
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};

	//Ĭ�ϴ��
	template<class T, class Container = vector<T>, class Compare = Less<T>>
	class priority_queue
	{
	public:
		Compare cmp;

		//ע��,�����ڲ������Լ��ĳ�Ա�������Բ���_con.size()
		void adjust_down(int root = 0)
		{
			int parent = root;
			int child = parent * 2 + 1;	//����
			while (child < size())
			{
				//if (child + 1 < size() && _con[child] < _con[child + 1]) //ע��Խ������
				if (child + 1 < size() && cmp(_con[child], _con[child + 1])) 
				{
					child++;
				}
				//if (_con[parent] < _con[child])
				if (cmp(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}

		}

		//���Ϻ����µ����㷨ʱ�临�Ӷ�O(logN)
		void adjust_up(int root = 0)
		{
			int child = size() - 1;
			int parent = (child - 1) / 2;
			while (child > root)
			{
				//if (_con[child] > _con[parent])
				if (cmp(_con[parent], _con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}

		//���ѵ�ʱ�临�Ӷȿ�����Ϊ��O(N)
		void push(const T& val)	
		{
			_con.push_back(val);
			adjust_up();
		}

		void pop()
		{
			swap(_con[0], _con[size() - 1]);
			_con.pop_back();
			adjust_down();
		}

		const T& top()
		{
			return _con[0];
		}

		size_t size()
		{
			return _con.size();
		}

		bool empty()
		{
			return _con.empty();
		}

	private:
		Container _con;
	};

}


namespace kozen
{
	void test_priority_queue()
	{
		//Ĭ���Ǵ��,�º�����less
		//priority_queue<int> pq;
		//С��
		priority_queue<int,vector<int>,Greater<int>> pq;
		pq.push(2);
		pq.push(3);
		pq.push(5);
		pq.push(4);
		pq.push(0);

		while (!pq.empty())
		{
			cout << pq.top() << " ";
			pq.pop();
		}
		cout << endl;
	}


	class pDateLess
	{
	public:
		bool operator()(const Date* d1, const Date* d2)
		{
			return *d1 < *d2;
		}
	};

	class pDateGreater
	{
	public:
		bool operator()(const Date* d1, const Date* d2)
		{
			return *d1 > *d2;
		}
	};

	void test_priority_queue2()
	{
		//priority_queue<Date> pq;
		priority_queue<Date,vector<Date>, Greater<Date>> pq;
		//priority_queue<Date*, vector<Date*>, pDateGreater> pq;

		pq.push(Date(2023, 5, 7));
		pq.push(Date(2023, 10, 7));
		pq.push(Date(2023, 10, 9));

		//pq.push(new Date(2023, 5, 7));
		//pq.push(new Date(2023, 10, 7));
		//pq.push(new Date(2023, 10, 9));

		while (!pq.empty())
		{
			//cout << *(pq.top()) << " ";
			cout << pq.top() << " ";
			pq.pop();
		}
		cout << endl;
	}


	void test_priority_queue3()
	{
		//֧��operator[]�ĵײ���������
		priority_queue<int, deque<int>, Greater<int>> pq;
		pq.push(2);
		pq.push(3);
		pq.push(5);
		pq.push(4);
		pq.push(0);


		while (!pq.empty())
		{
			cout << pq.top() << " ";
			pq.pop();
		}
		cout << endl;
	}
}