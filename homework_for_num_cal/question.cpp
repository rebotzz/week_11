#define _CRT_SECURE_NO_WARNINGS
#include "my_algrithm_numerical_calculation.h"
using namespace NumericalCalculation;

//第一题:
void question1_1()
{
	//插值点
	vector<double> xi = { 2005,2010,2015,2020 };
	vector<double> yi1 = { 72.8,74.2,75.2,76.4 };
	vector<double> yi2 = { 70.2,70.2,70.3,71.2 };

	//待求点
	vector<double> x = { 2000,2013,2018,2025 };
	vector<double> y1(4, 1);
	vector<double> y2(4, 1);

	//求解
	Interpolate<double> lg1(x, xi, yi1);
	Interpolate<double> lg2(x, xi, yi2);
	y1 = lg1.Lagrange();
	y2 = lg2.Lagrange();

	//打印结果
	cout << "输入年份:" << endl;
	for (auto e : x)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "输出结果,地区一:" << endl;
	for (auto e : y1)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "输出结果,地区二:" << endl;
	for (auto e : y2)
	{
		cout << e << " ";
	}
	cout << endl;

}

//第二题：
void question2_1()
{
	//初始化拟合点数组
	vector<double> xi;
	vector<double> yi = { 18.9,18.9,18.3,17.8,17.2,17.2,16.7,16.7,15.6,15.6,15,14.4,
						14.4,14.4,14.4,14.4,13.9,13.9,13.9,14.4,15.6,17.8,19.4,20 };
	xi.reserve(yi.size());
	for (size_t i = 0; i < yi.size(); ++i)
	{
		xi.push_back(i + 1);
	}

	// 1阶拟合，基函数 g1 = 1, g2 = x ==> 求解两个系数，2*2矩阵
	// 求解法方程组:Ax = B
	cout << "1阶拟合：" << endl;
	LeastSquare<double> ls1(xi, yi, 1);
	ls1.result();

	//2阶拟合,基函数:1,x,x^2
	cout << "2阶拟合：" << endl;
	LeastSquare<double> ls2(xi, yi, 2);
	ls2.result();
}


void question3_1()
{
#define PI acos(-1.0)

	//注意函数奇点
	struct f2		//c = 1.5; m = 1
	{
		long double operator()(long double x)
		{
			return cos(x) * pow(1 - (1 - cos(x)) / (2 * 0.6), 1.5) / (2 * PI);
		}
	};

	struct f3		//c = 1.1; m = 1
	{
		long double operator()(long double x)
		{
			return cos(x) * pow(1 - (1 - cos(x)) / (2 * 0.6), 1.1) / (2 * PI);
		}
	};

	//积分区间 a = -1*acos(1.0 - 2 * 0.6); eplis = 0.6
	long double a = -1 * acos(-0.2);
	long double b = -a;

	RombergIntegration<f2, long double> rg1(a, b, 1.0E-7);
	RombergIntegration<f3, long double> rg2(a, b, 1.0E-7);

	cout << "when c = 1.5:" << endl;
	rg1.integral();
	rg1.print();
	cout << endl;

	cout << "when c = 1.1:" << endl;
	rg2.integral();
	rg2.print();
	cout << endl;
}


void question4_1()
{
	//函数定义 仿函数
	struct f1
	{
		typedef long double Type;

		Type operator()(Type x, Type y)
		{
			return (_g / _m) * (_m - _ro * _v - _k * y) / y;
		}
	private:
		Type _m = 239.46;
		Type _v = 0.2058;
		Type _ro = 1035.71;
		Type _k = 0.6;
		Type _g = 9.8;
	};

	Rouge_Kuta<f1, long double> r1(0.0, 0.001, 90.0, 90.0 / 1000000);
	double ret = r1.result();
	//r1.printTable();
	cout << endl;
	cout << "result:" << endl;
	cout << ret << endl;
}


void question5_1()
{

	//初始化拟合点数组 xi折合流量； yi压比
	vector<double> xi = { 0.877693,0.875873,0.874052,0.87041,0.861305,0.857663,0.850379,
						0.839454,0.826707,0.813961,0.803035,0.792109,0.775721 };
	vector<double> yi = { 2.49895,2.57233,2.66667,2.8239,3.04403,3.15933,3.31656,3.47379,
						3.63103,3.74633,3.85115,3.91405,3.98742 };

	//2阶拟合,基函数:1,x,x^2
	cout << "2阶拟合：" << endl;
	LeastSquare<double> ls2(xi, yi, 2);
	ls2.result();

}