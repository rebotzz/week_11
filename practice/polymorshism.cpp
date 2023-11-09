#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

//�̳У���̬��ϰ

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

	virtual void func3()
	{
		cout << "func3()" << endl;
	}

	//�ȹ��츸�࣬�ٹ������ࣻ�ȹ�����ģ������
	Derive(int base = 1, int derive = 2)
		:Base(base)
		,_derive(derive)
	{
		cout << "Derive(int base = 1, int derive = 2)" << endl;
	}

	//���ø���Ŀ������캯��
	Derive(Derive& d)
		:Base(d)
		,_derive(d._derive)
	{
		cout << "Derive(Derive& d)" << endl;
	}

	//���ø���ĸ�ֵ���غ���
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

	//���������࣬���������ࣻ��������㣬�Զ����ú�������
	//����virtual��,��������������Ϊdestructor
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
//	////����ָ��/���õ���
//	//callFunc(b);
//	//callFunc(d);
//	////��Ƭ
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
//	////��������destructor()���ɶ�̬,���ø�������; ����δ֪
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



//////////////////��,ѧ��,��ʦ,����ϰ///////////
//��
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

//ѧ��
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

//��ʦ
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

//����	���μ̳�--��ñ���
//��������Ͷ���������  ��������--�������޶���; ������--��̳�
//�����ָ��,�����
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


//������ = 0   override �� final

//class ablity
//{
//public:
//	virtual void ablity1() = 0		//���麯��,ǿ����д
//	{
//		cout << "virtual void ablity1() = 0" << endl;
//	}
//
//	virtual void ablity2() 
//	{
//		cout << "virtual void ablity2() " << endl;
//	}
//
//	virtual void recovery() final	//final,������д
//	{
//		cout << "recovery" << endl;
//	}
//};
//
//class actor : public ablity
//{
//public:
//	virtual void ablity1() override		//override,����Ƿ���д
//	{
//		cout << "������+2" << endl;
//	}
//
//	virtual void ablity2() override
//	{
//		cout << "����+1 " << endl;
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