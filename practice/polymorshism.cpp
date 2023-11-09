#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

//继承，多态练习

class Base
{
public: 
	virtual void func1()
	{
		cout << "Base: func1()" << endl;
	}
	virtual void func2()
	{
		cout << "Base: func2()" << endl;
	}

	Base(int base = 1)
		:_base(base)
	{
		cout << "Base()" << endl;
	}

	Base(Base& b)
		:_base(b._base)
	{
		cout << "Base(Base& b)" << endl;
	}

	Base& operator=(Base& b)
	{
		cout << "Base& operator=(Base& b)" << endl;
		if (this != &b)
		{
			_base = b._base;
		}
		return *this;
	}

	virtual ~Base()
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

	virtual void func3()
	{
		cout << "func3()" << endl;
	}

	//先构造父类，再构造子类；先构造核心，再外层
	Derive(int base = 1, int derive = 2)
		:Base(base)
		,_derive(derive)
	{
		cout << "Derive(int base = 1, int derive = 2)" << endl;
	}

	//调用父类的拷贝构造函数
	Derive(Derive& d)
		:Base(d)
		,_derive(d._derive)
	{
		cout << "Derive(Derive& d)" << endl;
	}

	//调用父类的赋值重载函数
	Derive& operator = (Derive& d)
	{
		cout << "Derive& operator = (Derive& d)" << endl;
		if (this != &d)
		{
			Base::operator=(d);
			_derive = d._derive;
		}
		return *this;
	}

	//先析构子类，再析构父类；先析构外层，自动调用核心析构
	//加了virtual后,析构函数名处理为destructor
	virtual ~Derive()
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

void callFunc(Base* p)
{
	p->func1();
}

//int main()
//{
//	//Base b;
//	//Derive d;
//
//	////父类指针/引用调用
//	//callFunc(b);
//	//callFunc(d);
//	////切片
//	//Base* p = &b;
//	//p->func1();
//	//p = &d;
//	//p->func1();
//	//cout << endl;
//
//	//b.func1();
//	//b.func2();
//
//	//d.func1();
//	//d.func2();
//	//d.func3();
//	//d.Base::func2();
//
//	//cout << "---------" << endl;
//	//Derive d1(10, 23);
//	//d1.print();
//	//cout << endl;
//	//cout << "---------" << endl;
//
//	//cout << "---------" << endl;
//	//Base b2;
//	//Derive d2;
//	//Base* pb = &d2;
//	//callFunc(b2);
//	//callFunc(d2);
//	//pb->func2();
//	//pb->Base::func2();
//	//d2.func3();
//	//cout << "---------" << endl;
//
//	////析构函数destructor()构成多态,调用各自析构; 作用未知
//	//pb = &b2;
//	//pb->~Base();
//	//pb = &d2;
//	//pb->~Base();
//	//cout << "---------" << endl;
//
//
//	Base b3(8);
//	Derive d3(34, 12);
//	Base b4(d3);
//	b4 = b3;
//	Derive d4(d3);
//	d4 = d3;
//
//	return 0;
//}



//////////////////人,学生,老师,类练习///////////
//人
class Person
{
public:
	Person(const string name = "peter", const int id = 123)
		:_name(name)
		,_id(id)
	{}

protected:
	string _name;
	int _id;
};

//学生
//class Student : public Person
class Student : virtual public Person
{
public:
	Student(const string name = "tom", const int id = 123, const int stuid = 002)
		:Person(name, id)
		,_stuid(stuid)
	{
		cout << "name: " << _name << " id: " << _id << " _stuid: " << _stuid << endl;
	}
protected:
	int _stuid;
};

//老师
//class Teacher : public Person
class Teacher : virtual public Person
{
public:
	Teacher(const string name = "jack", const int id = 123, const int tchid = 102)
		:Person(name, id)
		, _tchid(tchid)
	{
		cout << "name: " << _name << " id: " << _id << " _tchid: " << _tchid << endl;
	}
protected:
	int _tchid;
};

//助教	菱形继承--最好避免
//数据冗余和二义性问题  数据冗余--域作用限定符; 二义性--虚继承
//虚基表指针,虚基表
class Assisstant : public Student, public Teacher
{
public:
	Assisstant(const string name = "jack", const int id = 123, const int stuid = 002, const int tchid = 102)
		:Student(name, id,stuid)
		, Teacher(name, id, tchid)
	{
		//cout << "name: " << Student::_name << " id: " << Student::_id << " _stuid: " 
		//	<< _stuid <<" _tchid: " << _tchid << endl;
		cout << "name: " << _name << " id: " << _id << " _stuid: "
			<< _stuid << " _tchid: " << _tchid << endl;
	}

	void print()
	{
		cout << &_name << " " << &_id << " " << &_stuid << " " << &_tchid << endl;
		//cout << &(Student::_name) << " " << &(Student::_id) << " " << 
		//&(Student::_stuid) << " " << &(Teacher::_tchid) << endl;

	}
};

//int main()
//{
//	Person peter;
//	Student tom;
//	Teacher jack;
//	Assisstant dack("da",333,222,111);
//	dack.print();
//
//	return 0;
//}


//抽象类 = 0   override 和 final

//class ablity
//{
//public:
//	virtual void ablity1() = 0		//纯虚函数,强制重写
//	{
//		cout << "virtual void ablity1() = 0" << endl;
//	}
//
//	virtual void ablity2() 
//	{
//		cout << "virtual void ablity2() " << endl;
//	}
//
//	virtual void recovery() final	//final,不让重写
//	{
//		cout << "recovery" << endl;
//	}
//};
//
//class actor : public ablity
//{
//public:
//	virtual void ablity1() override		//override,检查是否重写
//	{
//		cout << "物理攻击+2" << endl;
//	}
//
//	virtual void ablity2() override
//	{
//		cout << "防御+1 " << endl;
//	}
//
//
//};
//
//int main()
//{
//	actor jack;
//	jack.ablity1();
//	jack.ablity2();
//	jack.recovery();
//
//	return 0;
//}

class TestA
{
	virtual TestA& operator=(TestA& a)
	{
		return *this;
	}
};

int main()
{

	return 0;
}