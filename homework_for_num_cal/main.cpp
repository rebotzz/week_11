#define _CRT_SECURE_NO_WARNINGS
#include "question.h"


void test2()
{
	// 设置是几次拟合
	const int N = 1;

	// 创建两个vector
	vector<float> x, y;
	y = { 18.9,18.9,18.3,17.8,17.2,17.2,16.7,16.7,15.6,15.6,15,14.4,
		14.4,14.4,14.4,14.4,13.9,13.9,13.9,14.4,15.6,17.8,19.4,20 };
	x.reserve(y.size());
	for (size_t i = 0; i < y.size(); ++i)
	{
		x.push_back(i + 1);
	}

	//A*W = B
	// 创建A矩阵
	Eigen::MatrixXd A(x.size(), N + 1);

	for (unsigned int i = 0; i < x.size(); ++i) {  // 遍历所有点

		for (int n = N, dex = 0; n >= 1; --n, ++dex) {  // 遍历N到1阶
			A(i, dex) = pow(x[i], n);
		}

		A(i, N) = 1;  //
	}

	// 创建B矩阵
	Eigen::MatrixXd B(y.size(), 1);

	for (unsigned int i = 0; i < y.size(); ++i) {
		B(i, 0) = y[i];
	}

	// 创建矩阵W
	Eigen::MatrixXd W;
	W = (A.transpose() * A).inverse() * A.transpose() * B;

	// 打印W结果
	cout << W << endl;
}


void test3()
{
	MatrixXd b(3, 3);
	int arr[][3] = { 0,0,1,-1,0,0,0,1,0 };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			b(i, j) = arr[i][j];
		}
	}
	cout << b << endl << endl;

	MatrixXd a(3, 3);
	int arr1[][3] = { 0,-1,3,1,0,2,-3,-2,0 };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			a(i, j) = arr1[i][j];
		}
	}
	cout << a << endl << endl;
	cout << "a':" << endl;
	cout << a.transpose() << endl << endl;

	MatrixXd tmp(3, 3);
	tmp = b * a.transpose();
	cout << "tmp:" << endl << tmp << endl << endl;
	cout << "test:" << endl << b.transpose() * a << endl << endl;

	cout << b * tmp.transpose() << endl << endl;
}

void func()
{
	MatrixXd a(3, 3);
	int arr1[][3] = { 2,0,1,-1,2,0,0,2,-1};
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			a(i, j) = arr1[i][j];
		}
	}
	cout << "a:" << endl;
	cout << a << endl << endl;

	MatrixXd b(3, 3);
	int arr2[][3] = { 3,-1,-1,-1,3,-1,-1,-1,3 };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			b(i, j) = arr2[i][j];
		}
	}
	cout << "b:" << endl;
	cout << b << endl << endl;

	cout << "out:" << endl;
	cout << a*b.transpose() << endl << endl;

	//MatrixXd b1(1, 3);
	//MatrixXd b2(3, 1);

	//int arrb[] = { 2,1,-2 };
	//for (int i = 0; i < 3; i++)
	//{
	//	b1(0, i) = arrb[i];
	//	b2(i, 0) = arrb[i];
	//}
	//cout << "out:" << endl;
	//cout << b1*a*b2 << endl << endl;


}


void func2()
{
	MatrixXd a(3, 3);
	int arr1[][3] = { 0,1,1,1,0,1,1,1,1 };
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			a(i, j) = arr1[i][j];
		}
	}
	cout << "a:" << endl;
	cout << a << endl << endl;

	MatrixXd b(3, 3);
	int arr2[][3] = { 2,1,-2,1,2,-2,-2,-2,3};
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			b(i, j) = arr2[i][j];
		}
	}
	cout << "b:" << endl;
	cout << b << endl << endl;

	cout << "out:" << endl;
	cout << a*b << endl << endl;

}

int main()
{
	//question1_1();
	cout << "------------" << endl;
	//question2_1();
	//question3_1();
	question4_1();

	//func2();

	return 0;
}

