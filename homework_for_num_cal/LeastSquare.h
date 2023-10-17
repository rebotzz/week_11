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
//	//��ϵ�(xi,yi),��Ͻ���n
//	LeastSquare(const vector<T>& xi, const vector<T>& yi, const size_t n = 1)
//		:_xi(xi)
//		,_yi(yi)
//		,_n(n)
//	{}
//
//	//��ɢ���ڻ���Ĭ�ϻ���Ϊx^power��x��power����
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
//		//��ʼ����ϵ�����
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
//		// ������ g1 = 1, g2 = x, g3 = x^2,... ==> ���n+1��ϵ����(n+1)*(n+1)����
//		// ��ⷽ����:Ax = B
//		size_t N = _n + 1;		// N = n + 1, n�����
//		MatrixXd A(N, N);
//		for (size_t i = 0; i < N; ++i)
//		{
//			for (size_t j = 0; j < N; ++j)
//			{
//				A(i, j) = MyInnerProduct(xi, xi, i, j);	//���׵�ѡ��ʹ�ã�gi,gj��= x^(i+j)
//			}
//		}
//
//		cout << "A:" << endl;
//		cout << A << endl;
//
//		//����⣬X
//		MatrixXd X(N, 1);
//		//��ʽ�Ҷ˾���
//		MatrixXd B(N, 1);
//		for (size_t i = 0; i < N; ++i)
//		{
//			B(i, 0) = MyInnerProduct(xi, yi, i, 1);
//		}
//
//		cout << "B:" << endl;
//		cout << B << endl;
//
//		//���ϵ������ X = (A^-1)*B;
//		X = A.inverse() * B;	//debug:������inverse(),����reverse();
//		cout << "AX = B ==> X��" << endl;
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