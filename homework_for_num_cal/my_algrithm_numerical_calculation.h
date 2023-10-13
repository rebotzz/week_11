#pragma once
#include <iostream>	
#include <vector>	
using namespace std;

namespace NumericalCalculation
{
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
						ln *= (x - (double)xi[j]) / ((double)xi[i] - (double)xi[j]);
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

}

namespace NumericalCalculation
{
	void test_L_N()
	{
		//插值点
		vector<double> xi = { 2005,2010,2015,2020 };
		vector<double> yi1 = { 72.8,74.2,75.2,76.4 };
		vector<double> yi2 = { 70.2,70.2,70.3,71.2 };

		//待求点
		vector<double> x = { 2000,2013,2018,2025 };

		//Interpolate<double, vector<double>> ln1(x, xi, yi1);
		//Interpolate<double, vector<double>> ln2(x, xi, yi2);
		Interpolate<double> ln1(x, xi, yi1);
		Interpolate<double> ln2(x, xi, yi2);

		auto l1 = ln1.Lagrange();
		auto l2 = ln2.Lagrange();
		auto n1 = ln1.Newton();
		auto n2 = ln2.Newton();

		//打印结果
		cout << "输入年份:" << endl;
		for (auto e : x)
		{
			cout << e << " ";
		}
		cout << endl;

		cout << "拉格朗日：" << endl;
		cout << "输出结果,地区一:" << endl;
		for (auto e : l1)
		{
			cout << e << " ";
		}
		cout << endl;
		cout << "输出结果,地区二:" << endl;
		for (auto e : l2)
		{
			cout << e << " ";
		}
		cout << endl;
		cout << endl;

		cout << "牛顿：" << endl;
		cout << "输出结果,地区一:" << endl;
		for (auto e : n1)
		{
			cout << e << " ";
		}
		cout << endl;
		cout << "输出结果,地区二:" << endl;
		for (auto e : n2)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}