//#pragma once
//#include <iostream>
//#include <vector>
//using namespace std;
//
////拉格朗日插值法
////插值点xi, yi; 待求点x
//template<class T = double, class Container = vector<T>>
////double Lagrange(double x, vector<double>& xi, vector<double>& yi)
//T Lagrange(T x, const Container& xi, Container& yi)
//{
//	size_t n = xi.size();
//	double y = 0.0;
//	for (size_t i = 0; i < n; ++i)
//	{
//		double ln = 1.0;
//		for (size_t j = 0; j < n; ++j)
//		{
//			if (j != i)
//			{
//				ln *= (x - xi[j]) / (xi[i] - xi[j]);
//			}
//		}
//		y += yi[i] * ln;
//	}
//
//	return y;
//}
//
//
//
//
//
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
//			fi[i][j] = (fi[i - 1][j] - fi[i - 1][j - 1]) / (xi[j] - xi[j - i]);	//debug:这里是j - i,即f[0,..,n] = (...)/(x[n] - x[0])
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
//
//
//
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
//
////牛顿插值	3.0	时间复杂度O（N^2）,空间复杂度O（N）
//template<class T>
//T newton(T x, const vector<T>& xi, const vector<T>& yi)
//{
//	//差商
//	size_t n = yi.size() - 1;
//	vector<T> fi(yi);		//0阶差商，即yi
//	vector<T> fi_last(fi);	//上一层差商
//
//	//外层，差商阶数
//	for (size_t i = 1; i <= n; ++i)
//	{
//		//内层
//		for (size_t j = i; j <= n; ++j)
//		{
//			fi[j] = (fi_last[j] - fi_last[j - 1]) / (xi[j] - xi[j - i]);	//debug:这里是j - i
//		}
//		fi_last = fi;
//	}
//
//	//求插值点在插值多项式的值
//	//插值多项式
//	double p = fi[n];
//	for (size_t i = n; i > 0; --i)
//	{
//		p *= (x - xi[i - 1]);
//		p += fi[i - 1];
//	}
//
//	return p;
//}
//
//
