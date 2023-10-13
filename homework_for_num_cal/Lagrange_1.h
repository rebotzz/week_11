#pragma once
#include <iostream>
#include <vector>
using namespace std;

//拉格朗日插值法
//插值点xi, yi; 待求点x
template<class T = double, class Container = vector<T>>
//double Lagrange(double x, vector<double>& xi, vector<double>& yi)
T Lagrange(T x, const Container& xi, Container& yi)
{
	size_t n = xi.size();
	double y = 0.0;
	for (size_t i = 0; i < n; ++i)
	{
		double ln = 1.0;
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


////牛顿插值	1.0	时间复杂度O（N^2）,空间复杂度O（N^2）
//template<class T>
//T newton(T x, const vector<T>& xi, const vector<T>& yi)
//{
//	//差商
//	size_t n = yi.size() - 1;
//	vector<T> tmp(n + 1, 0);
//	vector<vector<T>> fi(n + 1, tmp);	
//	//0阶差商，即yi
//	fi[0] = yi;
//
//	//cout << "初始化差商表：" << endl;
//	//for (size_t i = 0; i < fi.size(); ++i)
//	//{
//	//	for (size_t j = 0; j < fi.size(); ++j)
//	//	{
//	//		//cout << fi[i][j] << " ";
//	//		cout << fi[j][i] << " ";
//	//	}
//	//	cout << endl;
//	//}
//	//cout << endl;
//
//	//外层，差商阶数
//	for (size_t i = 1; i <= n; ++i)
//	{
//		//内层，不同差商
//		for (size_t j = i; j <= n; ++j)
//		{
//			fi[i][j] = (fi[i - 1][j] - fi[i - 1][j - 1]) / (xi[j] - xi[j - i]);	//debug:这里是j - i
//		}
//	}
//
//	//cout << "计算后差商表：" << endl;
//	//for (size_t i = 0; i < fi.size(); ++i)
//	//{
//	//	for (size_t j = 0; j < fi.size(); ++j)
//	//	{
//	//		cout << fi[j][i] << " ";
//	//	}
//	//	cout << endl;
//	//}
//	//cout << endl;
//
//	//求插值点在插值多项式的值
//	double p = yi[0];
//	for (size_t i = 1; i <= n; ++i)
//	{
//		//fi[i][n - i + 1]*(x - xi[n - i]) + fi[i]
//
//		//基函数
//		double fn = 1.0;
//		size_t j = i;
//		while (j > 0)	//debug
//		{
//			fn *= x - xi[j - 1];
//			j--;
//		}
//		p += fi[i][i] * fn;
//	}
//
//	return p;
//}



////牛顿插值	2.0	时间复杂度O（N^2）,空间复杂度O（N^2）
//template<class T>
//T newton(T x, const vector<T>& xi, const vector<T>& yi)
//{
//	//差商
//	size_t n = yi.size() - 1;
//	vector<T> tmp(n + 1, 0);
//	vector<vector<T>> fi(n + 1, tmp);
//	//0阶差商，即yi
//	fi[0] = yi;
//
//	//外层，差商阶数
//	for (size_t i = 1; i <= n; ++i)
//	{
//		//内层，不同差商
//		for (size_t j = i; j <= n; ++j)
//		{
//			fi[i][j] = (fi[i - 1][j] - fi[i - 1][j - 1]) / (xi[j] - xi[j - i]);	//debug:这里是j - i
//		}
//	}
//
//	//求插值点在插值多项式的值
//	//插值多项式
//	double p = fi[n][n];
//	for (size_t i = n; i > 0; --i)
//	{
//		p *= (x - xi[i - 1]);
//		p += fi[i - 1][i - 1];
//	}
//
//	return p;
//}

//牛顿插值	3.0	时间复杂度O（N^2）,空间复杂度O（N）
template<class T>
T newton(T x, const vector<T>& xi, const vector<T>& yi)
{
	//差商
	size_t n = yi.size() - 1;
	vector<T> fi(yi);		//0阶差商，即yi
	vector<T> fi_last(fi);	//上一层差商

	//外层，差商阶数
	for (size_t i = 1; i <= n; ++i)
	{
		//内层
		for (size_t j = i; j <= n; ++j)
		{
			fi[j] = (fi_last[j] - fi_last[j - 1]) / (xi[j] - xi[j - i]);	//debug:这里是j - i
		}
		fi_last = fi;
	}

	//求插值点在插值多项式的值
	//插值多项式
	double p = fi[n];
	for (size_t i = n; i > 0; --i)
	{
		p *= (x - xi[i - 1]);
		p += fi[i - 1];
	}

	return p;
}


void test_newton()
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
		y1[i] = newton(x[i], xi, yi1);
		y2[i] = newton(x[i], xi, yi2);
	}

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