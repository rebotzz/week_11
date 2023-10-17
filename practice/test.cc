#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "inher.h"
using namespace std;



int main()
{
	A aa;
	aa.~A();	//可以显示调用析构
	//aa.A();	//不可以显示调用构造

	B bb(12,3);
	bb.printf();

	return 0;
}
