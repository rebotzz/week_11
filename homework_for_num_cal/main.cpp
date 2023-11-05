#define _CRT_SECURE_NO_WARNINGS
#include "question.h"

void question_test()
{
	//函数定义 仿函数
	struct f1
	{
		typedef long double Type;

		Type operator()(Type x, Type y)
		{
			return (y * y + y) / x;
		}
	};

	Rouge_Kuta<f1, long double> r1(1,-2, 2.5, 0.5);
	double ret = r1.result();
	r1.printTable();
	cout << endl;
	cout << "result:" << endl;
	cout << ret << endl;
}

int main()
{
	//cout << endl << "------------question_1:-------------" << endl << endl;
	//question1_1();

	//cout << endl << "------------question_2:-------------" << endl << endl;
	//question2_1();

	//cout << endl << "------------question_3:-------------" << endl << endl;
	//question3_1();

	//cout << endl << "------------question_4:-------------" << endl << endl;
	//question4_1();

	//cout << endl << "------------question_5:-------------" << endl << endl;
	//question5_1();

	question_test();

	system("pause");

	return 0;
}
