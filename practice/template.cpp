//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include "inher.h"
//using namespace std;
//
////ģ�������ϰ
//
//template<class T>
//class Test1
//{
//public:
//	void func1()
//	{
//		cout << "template<class T>" << endl;
//	}
//
//	T add(T x, T y)
//	{
//		return x + y;
//	}
//private:
//	T _t;
//};
//
//template<>
//class Test1<int>
//{
//public:
//	void func1()
//	{
//		cout << "class Test1<int>" << endl;
//	}
//
//	int add(int x, int y)
//	{
//		return x + y;
//	}
//private:
//	int _t;
//};
//
//template<class T>
//T add(T x, T y)
//{
//	cout << typeid(T).name() << endl;
//	cout << x + y << endl;
//	return x + y;
//}
//
//
//template<>
//int add<int>(int x, int y)
//{
//	cout << "template<>: " << typeid(int).name() << endl;
//	cout << x + y << endl;
//	return x + y;
//}
//
//int add(int x, int y)
//{
//	cout << "int add(int x, int y): " << typeid(int).name() << endl;
//	cout << x + y << endl;
//	return x + y;
//}
//
////////////////����ģ����ϰ////////////////
////ģ��
//template<class T1, class T2>
//void func(T1 x, T2 y)
//{
//	cout << "origin: func(T1 x, T2 y)" << endl;
//	cout << typeid(T1).name() << " " << typeid(T2).name() << endl;
//	cout << x << " " << y << endl;
//}
//
////����
//template<class T1, class T2>
//void func<size_t,size_t>(T1 x, T2 y);
//
////ȫ�ػ�	�ȼ��ں�������
//template<>
//void func<double,int>(double x, int y)
//{
//	cout << "func<double,int>(double x, int y)" << endl;
//	cout << x << " " << y << endl;
//}
//
//template<>
//void func<int*, double*>(int* x, double* y)
//{
//	cout << "func<int*, double*>(int* x, double* y)" << endl;
//	cout << *x << " " << *y << endl;
//}
//
////ƫ�ػ�	����ģ�岻ͬ,����������������ģ��
//template<class T1>
//void func(T1 x, char y)
//{
//	cout << "func(T1 x, char y)" << endl;
//	cout << x << " " << y << endl;
//}
//
//template<class T1, class T2>
//void func(T1* x, T2* y)
//{
//	cout << "func(T1* x, T2* y)" << endl;
//	cout << typeid(T1).name() << " " << typeid(T2).name() << endl;
//	cout << *x << " " << *y << endl;
//}
//
//void func(int x, char y)
//{
//	cout << "����: func(int x, char y)" << endl;
//	cout << x << " " << y << endl;
//}
//
//////////////////��ģ����ϰ//////////////
//template<class T1, class T2>
//class Date
//{
//public:
//	void print()
//	{
//		cout << "origin: template<class T1, class T2>" << endl;
//	}
//};
//
//template<class T1>
//class Date<T1, int>
//{
//public:
//	void print()
//	{
//		cout << "template<class T1> Date<T1, int>" << endl;
//	}
//};
//
//template<class T1, class T2>
//class Date<T1&, T2&>
//{
//public:
//	void print()
//	{
//		cout << "Date<T1&, T2&>" << endl;
//	}
//};
//
//template<class T1, class T2>
//class Date<T1*, T2*>
//{
//public:
//	void print()
//	{
//		cout << "Date<T1*, T2*>" << endl;
//	}
//};
//
//template<class T2>
//class Date<int, T2>
//{
//public:
//	void print()
//	{
//		cout << "Date<int, T2>" << endl;
//	}
//};
//
//template<>
//class Date<int, int>
//{
//public:
//	Date(int a = 2, int b = 3)
//		:_a(a)
//		,_b(b)
//	{}
//
//	void print()
//	{
//		cout << "Date<int, int>" << endl;
//	}
//private:
//	int _a;
//	int _b;
//};
//
////////////////�º���ģ����ϰ///////////////////
////�º���ģ��
//template<typename T>
//struct Less
//{
//	//bool operator()(T x, T y)
//	//{
//	//	cout << (x < y) << endl;
//	//	return x < y;
//	//}
//
//	bool operator()(const T& x, const T& y) const //ע��Ȩ�޲��ܷŴ�, ��ʱ����-const
//	{
//		cout << (x < y) << endl;
//		return x < y;
//	}
//
//	bool operator()(T* x, T* y)
//	{
//		cout << (*x < *y) << endl;
//		return *x < *y;
//	}
//};
//
//class AA
//{
//public:
//	AA(int aa = 4)
//		:_aa(aa)
//	{}
//	bool operator < (const AA& b) const	//���ﲻ��const, Less������
//	{
//		return _aa < b._aa;
//	}
//
//private:
//	int _aa;
//};
//
////ƫ�ػ�
//template<>
//struct Less<AA*>
//{
//	bool operator()(AA* x, AA* y)
//	{
//		cout << (*x < *y) << endl;
//		return *x < *y;
//	}
//};
//
//int main()
//{
//	//Test1<double> d1;
//	//d1.func1();
//	//cout << d1.add(1, 3) << endl;
//
//	//Test1<int> d2;
//	//d2.func1();
//	//cout << d2.add(1, 3) << endl;
//
//	//add(3, 4);
//	//add(3.5, 4.2);
//	//add('d', 'a');
//	//add(3, 3.5);
//	//_add(3, 2);
//
//	//func(2, 3);
//	//func((size_t)2.3, 3);
//	//int a = 2;
//	//double b = 3;
//	//func(&a, &b);
//	//func(&b, &a);
//	//func(2.3, 3);
//	//func(2.3, 'c');
//	//func(4, 'd');
//	//func((size_t)3, (size_t)4);
//
//
//	//Date<double, double> d1;
//	//d1.print();
//	//Date<double, int>().print();
//	//Date<int, char>().print();
//	//Date<double&, int&>().print();
//	//Date<double*, int*>().print();
//	//Date<int, int>().print();
//	//Date<int, int> d2(3, 5);
//	//d2.print();
//
//	Less<int>()(3, 4);
//	int a1 = 3;
//	int b1 = 5;
//	Less<int> less;
//	less(3, 5);
//	less(&a1, &b1);
//	Less<AA*> less1;
//	AA aa1;
//	AA aa2(5);
//	Less<AA>()(aa1, aa2);
//	less1(&aa1,&aa2);
//
//
//	return 0;
//}