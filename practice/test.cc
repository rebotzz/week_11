#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "inher.h"
using namespace std;



int main()
{
	A aa;
	aa.~A();	//������ʾ��������
	//aa.A();	//��������ʾ���ù���

	B bb(12,3);
	bb.printf();

	return 0;
}
