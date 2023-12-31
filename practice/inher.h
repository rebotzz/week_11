#pragma once
#include <iostream>
using namespace std;

class A
{
public:
	A(int a = 1)
		:_a(a)
	{}
protected:
	int _a;
};

class B : public A
{
public:
	B(int a = 1,int b = 1)
		:A(a)	//子类可以显示调用父类构造
		,_b(b)
	{}

	void printf()
	{
		cout << "a:" << _a << " " << "b:" << _b << endl;
	}
protected:
	int _b;
};


template<class T>
T _add(T x, T y)
{
	cout << "函数模板分离编译" << endl;
	cout << x + y << endl;
	return x + y;
}

//函数模板分离编译,需要全特化
template<>
int _add<int>(int x, int y)
{
	cout << "函数模板分离编译" << endl;
	cout << x + y << endl;
	return x + y;
}