﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "inher.h"
using namespace std;



//int main()
//{
//	A aa;
//	aa.~A();	//可以显示调用析构
//	//aa.A();	//不可以显示调用构造
//
//	B bb(12,3);
//	bb.printf();
//
//	//char* pch = new char[10];
//	//delete pch;
//
//	
//	string a = "hello world";
//
//	string b = a;			//这里有写实拷贝吗？？？
//	cout << (void*)(a.c_str()) << endl;
//	cout << (void*)(b.c_str()) << endl;
//
//	if (a.c_str() == b.c_str())
//
//	{
//
//		cout << "true" << endl;
//
//	}
//
//	else cout << "false" << endl;
//
//	string c = b;
//
//	c = "";
//
//	if (a.c_str() == b.c_str())
//
//	{
//
//		cout << "true" << endl;
//
//	}
//
//	else cout << "false" << endl;
//
//	a = "";
//
//	if (a.c_str() == b.c_str())
//
//	{
//
//		cout << "true" << endl;
//
//	}
//
//	else cout << "false" << endl;
//
//
//	return 0;
//}

int main()
{
	string s1 = "hello world";

	string s2 = "change world";

	string::iterator it = s1.begin();

	swap(s1, s2);

	while (it != s1.end())

		cout << *it;

	cout << endl;


	return 0;
}