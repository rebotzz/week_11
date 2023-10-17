#define _CRT_SECURE_NO_WARNINGS
#include "my_algrithm_numerical_calculation.h"
using namespace NumericalCalculation;

//��һ��:
void question1_1()
{
	//��ֵ��
	vector<double> xi = { 2005,2010,2015,2020 };
	vector<double> yi1 = { 72.8,74.2,75.2,76.4 };
	vector<double> yi2 = { 70.2,70.2,70.3,71.2 };

	//�����
	vector<double> x = { 2000,2013,2018,2025 };
	vector<double> y1(4, 1);
	vector<double> y2(4, 1);

	//���
	Interpolate<double> lg1(x, xi, yi1);
	Interpolate<double> lg2(x, xi, yi2);
	y1 = lg1.Lagrange();
	y2 = lg2.Lagrange();

	//��ӡ���
	cout << "�������:" << endl;
	for (auto e : x)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "������,����һ:" << endl;
	for (auto e : y1)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "������,������:" << endl;
	for (auto e : y2)
	{
		cout << e << " ";
	}
	cout << endl;
	
}

//�ڶ��⣺
void question2_1()
{
	//��ʼ����ϵ�����
	vector<double> xi;
	vector<double> yi = { 18.9,18.9,18.3,17.8,17.2,17.2,16.7,16.7,15.6,15.6,15,14.4,
						14.4,14.4,14.4,14.4,13.9,13.9,13.9,14.4,15.6,17.8,19.4,20 };
	xi.reserve(yi.size());
	for (size_t i = 0; i < yi.size(); ++i)
	{
		xi.push_back(i + 1);
	}

	// 1����ϣ������� g1 = 1, g2 = x ==> �������ϵ����2*2����
	// ��ⷨ������:Ax = B
	cout << "1����ϣ�" << endl;
	LeastSquare<double> ls1(xi, yi, 1);
	ls1.result();

	//2�����,������:1,x,x^2
	cout << "2����ϣ�" << endl;
	LeastSquare<double> ls2(xi, yi, 2);
	ls2.result();
}


void question3_1()
{
#define PI acos(-1.0)

	//ע�⺯�����
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

	//�������� a = -1*acos(1.0 - 2 * 0.6); eplis = 0.6
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