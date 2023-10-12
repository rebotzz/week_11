#pragma once
#include <iostream>
#include <vector>
using namespace std;

//插值点xi, yi; 待求点x
double Lagrange(double x, vector<double>& xi, vector<double>& yi)
{
	size_t n = xi.size();
	double y = 0;
	for (size_t i = 0; i < n; ++i)
	{
		double ln = 1;
		for (size_t j = 0; j < n; ++j)
		{
			if (j != i)
			{
				ln *= (x - (double)xi[j]) / ((double)xi[i] - (double)xi[j]);
			}
		}
		y += yi[i] * ln;
	}

	return y;
}


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
	for (size_t i = 0; i < x.size(); ++i)
	{
		y1[i] = Lagrange(x[i], xi, yi1);
		y2[i] = Lagrange(x[i], xi, yi2);
	}

	//打印结果
	cout << "输入年份:" << endl;
	for(auto e : x)
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