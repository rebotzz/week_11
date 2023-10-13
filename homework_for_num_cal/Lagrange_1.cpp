#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Lagrange_1.h"
using namespace std;

void test()
{
	// Command Window  ‰»Î
	vector<double> xi = {11,12,13};
	vector<double> yi = { 2.3979,2.4849,2.5649};
	auto p = newton(1.0, xi, yi);

}

int main()
{
	cout << "Lagrange:" << endl;
	question1_1();
	cout << endl;
	cout << "Newton:" << endl;
	test_newton();

	//test();

	return 0;
}