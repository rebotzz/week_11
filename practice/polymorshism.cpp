#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//继承，多态练习

class Base
{
public: 
	virtual void func1()
	{
		cout << "Base: func1()" << endl;
	}
	void func2()
	{
		cout << "Base: func2()" << endl;
	}

	Base(int base = 1)
		:_base(base)
	{
		cout << "Base()" << endl;
	}

	~Base()
	{
		cout << "~Base()" << endl;
	}

protected:
	int _base;
};


class Derive : public Base
{
public:
	//接口继承	虚函数重写
	virtual void func1()
	{
		cout << "Derive: func1()" << endl;
	}

	//隐藏
	void func2()
	{
		cout << "Derive: func2()" << endl;
	}

	void func3()
	{
		cout << "func3()" << endl;
	}

	//先构造父类，在构造子类；先构造核心，再外层
	Derive(int base = 1, int derive = 2)
		:Base(base)
		,_derive(derive)
	{
		cout << "Derive(int base = 1, int derive = 2)" << endl;
	}

	//先析构子类，再析构父类；先析构外层，自动调用核心析构
	~Derive()
	{
		cout << "~Derive()" << endl;
	}

	void print()
	{
		cout << _base << " " << _derive << endl;
	}

protected:
	int _derive;
};

void callFunc(Base& ref)
{
	ref.func1();
}

int main()
{
	//Base b;
	//Derive d;

	////父类指针/引用调用
	//callFunc(b);
	//callFunc(d);
	////切片
	//Base* p = &b;
	//p->func1();
	//p = &d;
	//p->func1();
	//cout << endl;

	//b.func1();
	//b.func2();

	//d.func1();
	//d.func2();
	//d.func3();
	//d.Base::func2();

	cout << "---------" << endl;
	Derive d1(10, 23);
	d1.print();

	return 0;
}
