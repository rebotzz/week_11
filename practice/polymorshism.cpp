#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//�̳У���̬��ϰ

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
	//�ӿڼ̳�	�麯����д
	virtual void func1()
	{
		cout << "Derive: func1()" << endl;
	}

	//����
	void func2()
	{
		cout << "Derive: func2()" << endl;
	}

	void func3()
	{
		cout << "func3()" << endl;
	}

	//�ȹ��츸�࣬�ڹ������ࣻ�ȹ�����ģ������
	Derive(int base = 1, int derive = 2)
		:Base(base)
		,_derive(derive)
	{
		cout << "Derive(int base = 1, int derive = 2)" << endl;
	}

	//���������࣬���������ࣻ��������㣬�Զ����ú�������
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

	////����ָ��/���õ���
	//callFunc(b);
	//callFunc(d);
	////��Ƭ
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
