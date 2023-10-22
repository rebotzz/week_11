#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//class A
//{
//public:
//	A(int a = 1)
//		:_a(a)
//	{}
//protected:
//	int _a;
//};
//
//class B : public A
//{
//public:
//	B(int a = 1, int b = 1)
//		:A(a)	//���������ʾ���ø��๹��
//		, _b(b)
//	{}
//
//	void printf()
//	{
//		cout << "a:" << _a << " " << "b:" << _b << endl;
//	}
//protected:
//	int _b;
//};


// B�е�fun��A�е�fun���ǹ������أ���Ϊ������ͬһ������
// B�е�fun��A�е�fun�������أ���Ա�������㺯������ͬ�͹������ء�
class A
{
public:
	void fun()
	{
		cout << "func()" << endl;
	}
};
class B : public A
{
public:
	void fun(int i)
	{
		A::fun();	//ֻҪ��������ͬ--���أ���Ҫָ��������
		cout << "func(int i)->" << i << endl;
	}
};
void Test()
{
	B b;
	b.fun(1);
}


class Person
{
public:
	Person(const char* name = "peter")
		: _name(name)
	{
		cout << "Person()" << endl;
	}

	Person(const Person& p)
		: _name(p._name)
	{
		cout << "Person(const Person& p)" << endl;
	}

	Person& operator=(const Person& p)
	{
		cout << "Person operator=(const Person& p)" << endl;
		if (this != &p)
			_name = p._name;

		return *this;
	}

	~Person()
	{
		cout << "~Person()" << endl;
	}
protected:
	string _name; // ����
};
class Student : public Person
{
public:
	Student(const char* name, int num)
		: Person(name)
		, _num(num)
	{
		cout << "Student()" << endl;
	}

	Student(const Student& s)
		: Person(s)
		, _num(s._num)
	{
		cout << "Student(const Student& s)" << endl;
	}

	Student& operator = (const Student& s)
	{
		cout << "Student& operator= (const Student& s)" << endl;
		if (this != &s)
		{
			Person::operator =(s);
			_num = s._num;
		}
		return *this;
	}

	~Student()
	{
		cout << "~Student()" << endl;
	}
protected:
	int _num; //ѧ��
};
void Test2()
{
	Student s1("jack", 18);
	Student s2(s1);
	Student s3("rose", 17);
	s1 = s3;
}


int main()
{
	Test2();

	return 0;
}