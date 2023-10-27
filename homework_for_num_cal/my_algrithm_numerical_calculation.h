#pragma once
#include <iostream>	
#include <vector>	
#include "Eigen/Dense"
#include <math.h>
#include <assert.h>
#include <iomanip>  //流控制头文件
using namespace std;
using Eigen::MatrixXd;

namespace NumericalCalculation
{
	//插值算法
	//容器必须支持operator[],随机访问迭代器
	template<class T = double, class Container = vector<T>>
	class Interpolate
	{
	//成员变量
	private:	
		//插值点_xi, _yi; 差商表_fi; 待求点_x, 结果_y;
		Container _xi;
		Container _yi;
		Container _fi;
		Container _x;
		Container _y;

	//成员函数
	public:		
		Interpolate(const Container& x, const Container& xi, const Container& yi)
			:_xi(xi)
			,_yi(yi)
			,_x(x)
		{
			_y.resize(_x.size());
			_fi.resize(_xi.size());
		}

		//拉格朗日插值法	时间复杂度O(K*N^2); 空间复杂度O(1)
		//子程序
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
			//求解_x对应的_y
			for (size_t i = 0; i < _x.size(); ++i)
			{
				_y[i] = _Lagrange(_x[i], _xi, _yi);
			}
			return _y;
		}


		//牛顿插值	4.0	时间复杂度O（N^2）,空间复杂度O（N）减少了差商的重复求解
		//子程序
		T _Newton(T x, const Container& xi, const Container& fi)
		{
			//求插值点在插值多项式的值
			//插值多项式
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
			//求解差商
			_fi = _yi;		//0阶差商初始化
			size_t n = _yi.size() - 1;
			Container fi_last(_fi);	//上一层差商

			//外层，差商阶数
			for (size_t i = 1; i <= n; ++i)
			{
				//内层
				for (size_t j = i; j <= n; ++j)
				{
					_fi[j] = (fi_last[j] - fi_last[j - 1]) / (_xi[j] - _xi[j - i]);	//debug:这里是j - i
				}
				fi_last = _fi;
			}

			//求解_x对应的_y
			for (size_t i = 0; i < _x.size(); ++i)
			{
				_y[i] = _Newton(_x[i], _xi, _fi);
			}
			return _y;
		}
	};


	//最小二乘拟合算法
	template<class T = double>
	class LeastSquare
	{
	public:
		//拟合点(xi,yi),拟合阶数n
		LeastSquare(const vector<T>& xi, const vector<T>& yi, const size_t n = 1)
			:_xi(xi)
			, _yi(yi)
			, _n(n)
		{}

		//离散点内积，默认基底为x^power，x的power次幂
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
			//初始化拟合点数组
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


			// 基函数 g1 = 1, g2 = x, g3 = x^2,... ==> 求解n+1个系数，(n+1)*(n+1)矩阵
			// 求解方程组:Ax = B
			size_t N = _n + 1;		// N = n + 1, n阶拟合
			MatrixXd A(N, N);
			for (size_t i = 0; i < N; ++i)
			{
				for (size_t j = 0; j < N; ++j)
				{
					A(i, j) = MyInnerProduct(xi, xi, i, j);	//基底的选择使得（gi,gj）= x^(i+j)
				}
			}

			cout << "A:" << endl;
			cout << A << endl;

			//待求解，X
			MatrixXd X(N, 1);
			//等式右端矩阵
			MatrixXd B(N, 1);
			for (size_t i = 0; i < N; ++i)
			{
				B(i, 0) = MyInnerProduct(xi, yi, i, 1);
			}

			cout << "B:" << endl;
			cout << B << endl;

			//求解系数矩阵， X = (A^-1)*B;
			X = A.inverse() * B;	//debug:求逆是inverse(),不是reverse();
			cout << "AX = B ==> X：" << endl;
			cout << X << endl;
		}

	private:
		vector<T> _xi;
		vector<T> _yi;
		size_t _n;
	};


	//Romberg积分算法	
	//Function积分函数(函数对象)，Type数据类型
	template<class Function, class Type = double>
	class RombergIntegration	
	{
	public:
		//积分区间a,b,积分精度accuracy,表格最大容量MaxSize
		RombergIntegration(Type a, Type b, Type accuracy, size_t MaxSize = 30)
			:_a(a)
			, _b(b)
			, _accy(accuracy)
			, _maxSize(MaxSize)
		{
			//开辟二维数组，申请内存空间	MaxSize * MaxSize
			_table = new Type * [MaxSize];
			for (int i = 0; i < MaxSize; ++i)
			{
				_table[i] = new Type[MaxSize];
			}
		}

		~RombergIntegration()
		{
			//释放内存空间
			for (int i = 0; i < _maxSize; ++i)
			{
				delete[] _table[i];
			}
			delete[] _table;
		}

		Type integral()
		{
			//1.计算T0(h)
			Type h = _b - _a;		//初始步长,二分次数0
			Type T0 = h * (_func(_a) + _func(_b)) / 2;
			_table[0][0] = T0;
			//2.计算Tk((b-a)/2^k) 递推公式:Tk = 0.5*T(k-1)+新步长*新节点函数值
			for (int i = 1; i <= K; i++)
			{
				_table[i][0] = getIntegralValue(_table[i - 1][0], pow(2, i));
			}


			//3.求加速值Tk_m(h),即：Sk,Ck,Rk。。。
			for (int mi = 1; mi <= K; mi++)			//列
			{
				for (int ki = mi; ki <= K; ki++)	//行
				{
					Type index = pow(4, mi);
					_table[ki][mi] = _table[ki][mi - 1] * index / (index - 1) - _table[ki - 1][mi - 1] / (index - 1);
				}
			}

			//4.精度检验
			//Type gap = _table[K][K] - _table[K - 1][K - 1];
			Type gap = _table[K][K] - _table[K][K - 1];
			if (gap < 0)
				gap *= -1;
			if (gap <= _accy)
			{
				return _table[K][K];
			}

			//如果误差限不满足要求，则继续更新table表
			else
			{
				//i代表行，j代表列
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
					Type gap = _table[i][i] - _table[i][i - 1];		//两种误差估计方法都可以
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

		//复化梯形求积	2.0
		Type getIntegralValue(Type preT, int newN)
		{
			Type sum = 0;
			Type h = (_b - _a) / newN;			//二分后新的步长
			int preN = newN / 2;
			for (int i = 1; i <= preN; ++i)
			{
				sum += h * _func(_a + (2 * i - 1) * h);
			}
			Type value = 0.5 * preT + sum;
			return value;
		}

		//输出table
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
		Type _b;				//积分区间[_a,_b]
		Type _accy;				//精度
		Function _func;			//被积函数，使用仿函数定义
		int K = 4;				//初始二分次数
		size_t _maxSize;
		//Type _table[30][30];	//1.0数据存储在栈上
		Type** _table;			//2.0数据存储在堆上
	};


	//常微分方程求解
	template<class Function, class T = double>
	class Rouge_Kuta
	{
	public:
		//初值，待求点, 步长
		Rouge_Kuta(T x0, T y0, T x, T h)
			:_x0(x0)
			, _y0(y0)
			, _h(h)
			, _x(x)
		{
			arr.reserve((_x - _x0) / h * 2);
		}

		//计算待求点(x,y)
		T result()
		{
			T xi = _x0;
			T yi1 = _y0, yi0 = _y0;
			T k1, k2, k3, k4;
			T h = _h;
			arr.push_back(xi);
			arr.push_back(yi0);
			while (xi < _x)
			{
				//4阶Rouge-Kuta 算法
				k1 = _func(xi, yi0);
				k2 = _func(xi + h / 2, yi0 + h / 2 * k1);
				k3 = _func(xi + h / 2, yi0 + h / 2 * k2);
				k4 = _func(xi + h, yi0 + h * k3);
				yi1 = yi0 + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);

				xi += h;
				yi0 = yi1;
				arr.push_back(xi);
				arr.push_back(yi0);
			}

			return yi1;
		}

		//打印各点函数值(xi,yi)
		void printTable()
		{
			cout << "------------------" << endl;
			cout << "x: ";
			for (int i = 0; i < arr.size(); ++i)
			{
				if (i % 2 == 0)
				{
					cout << arr[i] << " ";
				}
			}
			cout << endl << endl;

			cout << "------------------" << endl;
			cout << "y: ";
			for (int i = 0; i < arr.size(); ++i)
			{
				if (i % 2 == 1)
				{
					cout << arr[i] << " ";
				}
			}
			cout << endl;
		}

		//获取各点函数值(xi,yi)
		vector<T> getTable()
		{
			return arr;
		}

	private:
		T _x0;	//初值
		T _y0;
		T _h;	//步长
		T _x;	//待求点
		Function _func;
		vector<T> arr;	//各点函数值(xi,yi)
	};

}


#define DEBUG
#ifdef DEBUG

namespace NumericalCalculation
{


}

#endif // DEBUG
