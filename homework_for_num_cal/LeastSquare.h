//#pragma once 
//#include <iostream>	
//#include <vector>	
//#include "Eigen/Dense"
//#include <math.h>
//#include <assert.h>
//using namespace Eigen;
//using namespace std;
//
//template<class T = double>
//class LeastSquare
//{
//public:
//	//拟合点(xi,yi),拟合阶数n
//	LeastSquare(const vector<T>& xi, const vector<T>& yi, const size_t n = 1)
//		:_xi(xi)
//		,_yi(yi)
//		,_n(n)
//	{}
//
//	//离散点内积，默认基底为x^power，x的power次幂
//	T MyInnerProduct(const vector<T>& xi, const vector<T>& yi, const size_t powerX, const size_t powerY)
//	{
//		assert(xi.size() == yi.size());
//		T sum = 0.0;
//		size_t n = xi.size();
//		for (size_t i = 0; i < n; ++i)
//		{
//			sum += pow(xi[i], powerX) * pow(yi[i], powerY);
//		}
//		return sum;
//	}
//
//	void result()
//	{
//		//初始化拟合点数组
//		vector<double>& xi = _xi;
//		vector<double>& yi = _yi;
//
//		cout << "xi:" << endl;
//		for (auto e : xi)
//		{
//			cout << e << " ";
//		}
//		cout << endl;
//		cout << "yi:" << endl;
//		for (auto e : yi)
//		{
//			cout << e << " ";
//		}
//		cout << endl;
//
//
//		// 基函数 g1 = 1, g2 = x, g3 = x^2,... ==> 求解n+1个系数，(n+1)*(n+1)矩阵
//		// 求解方程组:Ax = B
//		size_t N = _n + 1;		// N = n + 1, n阶拟合
//		MatrixXd A(N, N);
//		for (size_t i = 0; i < N; ++i)
//		{
//			for (size_t j = 0; j < N; ++j)
//			{
//				A(i, j) = MyInnerProduct(xi, xi, i, j);	//基底的选择使得（gi,gj）= x^(i+j)
//			}
//		}
//
//		cout << "A:" << endl;
//		cout << A << endl;
//
//		//待求解，X
//		MatrixXd X(N, 1);
//		//等式右端矩阵
//		MatrixXd B(N, 1);
//		for (size_t i = 0; i < N; ++i)
//		{
//			B(i, 0) = MyInnerProduct(xi, yi, i, 1);
//		}
//
//		cout << "B:" << endl;
//		cout << B << endl;
//
//		//求解系数矩阵， X = (A^-1)*B;
//		X = A.inverse() * B;	//debug:求逆是inverse(),不是reverse();
//		cout << "AX = B ==> X：" << endl;
//		cout << X << endl;
//
//	}
//
//
//
//private:
//	vector<T> _xi;
//	vector<T> _yi;
//	size_t _n;
//};