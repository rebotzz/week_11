#pragma once
#include <iostream>	
#include <vector>	
#include "Eigen/Dense"
#include <math.h>
#include <assert.h>
#include <iomanip>  //������ͷ�ļ�
using namespace std;
using Eigen::MatrixXd;

namespace NumericalCalculation
{
	//��ֵ�㷨
	//��������֧��operator[],������ʵ�����
	template<class T = double, class Container = vector<T>>
	class Interpolate
	{
	//��Ա����
	private:	
		//��ֵ��_xi, _yi; ���̱�_fi; �����_x, ���_y;
		Container _xi;
		Container _yi;
		Container _fi;
		Container _x;
		Container _y;

	//��Ա����
	public:		
		Interpolate(const Container& x, const Container& xi, const Container& yi)
			:_xi(xi)
			,_yi(yi)
			,_x(x)
		{
			_y.resize(_x.size());
			_fi.resize(_xi.size());
		}

		//�������ղ�ֵ��	ʱ�临�Ӷ�O(K*N^2); �ռ临�Ӷ�O(1)
		//�ӳ���
		T _Lagrange(T x, const Container& xi, Container& yi)
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
						ln *= (x - xi[j]) / (xi[i] - xi[j]);
					}
				}
				y += yi[i] * ln;
			}

			return y;
		}

		Container& Lagrange()
		{
			//���_x��Ӧ��_y
			for (size_t i = 0; i < _x.size(); ++i)
			{
				_y[i] = _Lagrange(_x[i], _xi, _yi);
			}
			return _y;
		}


		//ţ�ٲ�ֵ	4.0	ʱ�临�Ӷ�O��N^2��,�ռ临�Ӷ�O��N�������˲��̵��ظ����
		//�ӳ���
		T _Newton(T x, const Container& xi, const Container& fi)
		{
			//���ֵ���ڲ�ֵ����ʽ��ֵ
			//��ֵ����ʽ
			size_t n = _xi.size() - 1;
			double p = fi[n];
			for (size_t i = n; i > 0; --i)
			{
				p *= (x - xi[i - 1]);
				p += fi[i - 1];
			}

			return p;
		}

		Container& Newton()
		{
			//������
			_fi = _yi;		//0�ײ��̳�ʼ��
			size_t n = _yi.size() - 1;
			Container fi_last(_fi);	//��һ�����

			//��㣬���̽���
			for (size_t i = 1; i <= n; ++i)
			{
				//�ڲ�
				for (size_t j = i; j <= n; ++j)
				{
					_fi[j] = (fi_last[j] - fi_last[j - 1]) / (_xi[j] - _xi[j - i]);	//debug:������j - i
				}
				fi_last = _fi;
			}

			//���_x��Ӧ��_y
			for (size_t i = 0; i < _x.size(); ++i)
			{
				_y[i] = _Newton(_x[i], _xi, _fi);
			}
			return _y;
		}
	};


	//��С��������㷨
	template<class T = double>
	class LeastSquare
	{
	public:
		//��ϵ�(xi,yi),��Ͻ���n
		LeastSquare(const vector<T>& xi, const vector<T>& yi, const size_t n = 1)
			:_xi(xi)
			, _yi(yi)
			, _n(n)
		{}

		//��ɢ���ڻ���Ĭ�ϻ���Ϊx^power��x��power����
		T MyInnerProduct(const vector<T>& xi, const vector<T>& yi, const size_t powerX, const size_t powerY)
		{
			assert(xi.size() == yi.size());
			T sum = 0.0;
			size_t n = xi.size();
			for (size_t i = 0; i < n; ++i)
			{
				sum += pow(xi[i], powerX) * pow(yi[i], powerY);
			}
			return sum;
		}

		void result()
		{
			//��ʼ����ϵ�����
			vector<double>& xi = _xi;
			vector<double>& yi = _yi;

			cout << "xi:" << endl;
			for (auto e : xi)
			{
				cout << e << " ";
			}
			cout << endl;
			cout << "yi:" << endl;
			for (auto e : yi)
			{
				cout << e << " ";
			}
			cout << endl;


			// ������ g1 = 1, g2 = x, g3 = x^2,... ==> ���n+1��ϵ����(n+1)*(n+1)����
			// ��ⷽ����:Ax = B
			size_t N = _n + 1;		// N = n + 1, n�����
			MatrixXd A(N, N);
			for (size_t i = 0; i < N; ++i)
			{
				for (size_t j = 0; j < N; ++j)
				{
					A(i, j) = MyInnerProduct(xi, xi, i, j);	//���׵�ѡ��ʹ�ã�gi,gj��= x^(i+j)
				}
			}

			cout << "A:" << endl;
			cout << A << endl;

			//����⣬X
			MatrixXd X(N, 1);
			//��ʽ�Ҷ˾���
			MatrixXd B(N, 1);
			for (size_t i = 0; i < N; ++i)
			{
				B(i, 0) = MyInnerProduct(xi, yi, i, 1);
			}

			cout << "B:" << endl;
			cout << B << endl;

			//���ϵ������ X = (A^-1)*B;
			X = A.inverse() * B;	//debug:������inverse(),����reverse();
			cout << "AX = B ==> X��" << endl;
			cout << X << endl;
		}

	private:
		vector<T> _xi;
		vector<T> _yi;
		size_t _n;
	};


	//Romberg�����㷨	
	//Function���ֺ���(��������)��Type��������
	template<class Function, class Type = double>
	class RombergIntegration	
	{
	public:
		//��������a,b,���־���accuracy,����������MaxSize
		RombergIntegration(Type a, Type b, Type accuracy, size_t MaxSize = 30)
			:_a(a)
			, _b(b)
			, _accy(accuracy)
			, _maxSize(MaxSize)
		{
			//���ٶ�ά���飬�����ڴ�ռ�	MaxSize * MaxSize
			_table = new Type * [MaxSize];
			for (int i = 0; i < MaxSize; ++i)
			{
				_table[i] = new Type[MaxSize];
			}
		}

		~RombergIntegration()
		{
			//�ͷ��ڴ�ռ�
			for (int i = 0; i < _maxSize; ++i)
			{
				delete[] _table[i];
			}
			delete[] _table;
		}

		Type integral()
		{
			//1.����T0(h)
			Type h = _b - _a;		//��ʼ����,���ִ���0
			Type T0 = h * (_func(_a) + _func(_b)) / 2;
			_table[0][0] = T0;
			//2.����Tk((b-a)/2^k) ���ƹ�ʽ:Tk = 0.5*T(k-1)+�²���*�½ڵ㺯��ֵ
			for (int i = 1; i <= K; i++)
			{
				_table[i][0] = getIntegralValue(_table[i - 1][0], pow(2, i));
			}


			//3.�����ֵTk_m(h),����Sk,Ck,Rk������
			for (int mi = 1; mi <= K; mi++)			//��
			{
				for (int ki = mi; ki <= K; ki++)	//��
				{
					Type index = pow(4, mi);
					_table[ki][mi] = _table[ki][mi - 1] * index / (index - 1) - _table[ki - 1][mi - 1] / (index - 1);
				}
			}

			//4.���ȼ���
			//Type gap = _table[K][K] - _table[K - 1][K - 1];
			Type gap = _table[K][K] - _table[K][K - 1];
			if (gap < 0)
				gap *= -1;
			if (gap <= _accy)
			{
				return _table[K][K];
			}

			//�������޲�����Ҫ�����������table��
			else
			{
				//i�����У�j������
				int i = K + 1;
				while (gap > _accy)
				{
					_table[i][0] = getIntegralValue(_table[i - 1][0], pow(2, i));
					for (int j = 1; j <= i; j++)
					{
						Type index = pow(4, j);
						_table[i][j] = _table[i][j - 1] * index / (index - 1) - _table[i - 1][j - 1] / (index - 1);
					}

					//Type gap = _table[i][i] - _table[i - 1][i - 1];
					Type gap = _table[i][i] - _table[i][i - 1];		//���������Ʒ���������
					if (gap < 0)
						gap *= -1;
					if (gap <= _accy)
					{
						K = i;
						return _table[i][i];
					}
				}
			}
		}

		//�����������	2.0
		Type getIntegralValue(Type preT, int newN)
		{
			Type sum = 0;
			Type h = (_b - _a) / newN;			//���ֺ��µĲ���
			int preN = newN / 2;
			for (int i = 1; i <= preN; ++i)
			{
				sum += h * _func(_a + (2 * i - 1) * h);
			}
			Type value = 0.5 * preT + sum;
			return value;
		}

		//���table
		void print()
		{
			cout << "------------------------------------------------------------------" << endl;
			cout << "k " << "   T     " << "    S     " << "   C     " << "    R    " << endl;
			for (int i = 0; i <= K; i++)
			{
				cout << i << " ";
				for (int j = 0; j <= i; j++)
				{
					//if (j <= 3)
					{
						cout.setf(ios::showpoint);
						cout << setprecision(8) << _table[i][j] << " ";
					}
				}
				cout << endl;
			}
			cout << "------------------------------------------------------------------" << endl;
			cout << "this is result: " << _table[K][K] << endl;
		}

	private:
		Type _a;
		Type _b;				//��������[_a,_b]
		Type _accy;				//����
		Function _func;			//����������ʹ�÷º�������
		int K = 4;				//��ʼ���ִ���
		size_t _maxSize;
		//Type _table[30][30];	//1.0���ݴ洢��ջ��
		Type** _table;			//2.0���ݴ洢�ڶ���
	};


}


#define DEBUG
#ifdef DEBUG

namespace NumericalCalculation
{


}

#endif // DEBUG
