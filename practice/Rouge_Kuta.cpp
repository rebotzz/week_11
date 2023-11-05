//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <vector>
//using namespace std;
//
////常微分方程求解
//template<class Function, class T = double>
//class Rouge_Kuta
//{
//public:
//	//初值，待求点, 步长
//	Rouge_Kuta(T x0, T y0, T x, T h)
//		:_x0(x0)
//		, _y0(y0)
//		, _h(h)
//		, _x(x)
//	{
//		arr.reserve((_x - _x0) / h * 2);
//	}
//
//	//计算待求点(x,y)
//	T result()
//	{
//		T xi = _x0;
//		T yi1 = _y0, yi0 = _y0;
//		T k1, k2, k3, k4;
//		T h = _h;
//		arr.push_back(xi);
//		arr.push_back(yi0);
//		while (xi < _x)
//		{
//			//4阶Rouge-Kuta 算法
//			k1 = _func(xi, yi0);
//			k2 = _func(xi + h / 2, yi0 + h / 2 * k1);
//			k3 = _func(xi + h / 2, yi0 + h / 2 * k2);
//			k4 = _func(xi + h, yi0 + h * k3);
//			yi1 = yi0 + (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
//
//			xi += h;
//			yi0 = yi1;
//			arr.push_back(xi);
//			arr.push_back(yi0);
//		}
//
//		return yi1;
//	}
//
//	//打印各点函数值(xi,yi)
//	void printTable()
//	{
//		cout << "------------------" << endl;
//		cout << "x: ";
//		for (int i = 0; i < arr.size(); ++i)
//		{
//			if (i % 2 == 0)
//			{
//				cout << arr[i] << " ";
//			}
//		}
//		cout << endl << endl;
//
//		cout << "------------------" << endl;
//		cout << "y: ";
//		for (int i = 0; i < arr.size(); ++i)
//		{
//			if (i % 2 == 1)
//			{
//				cout << arr[i] << " ";
//			}
//		}
//		cout << endl;
//	}
//
//	//获取各点函数值(xi,yi)
//	vector<T> getTable()
//	{
//		return arr;
//	}
//
//private:
//	T _x0;	//初值
//	T _y0;
//	T _h;	//步长
//	T _x;	//待求点
//	Function _func;
//	vector<T> arr;	//各点函数值(xi,yi)
//};
//
//
//void question4_1()
//{
//	//函数定义 仿函数
//	struct f1
//	{
//		typedef long double Type;
//
//		Type operator()(Type x, Type y)
//		{
//			return (_g / _m) * (_m - _ro * _v - _k * y) / y;
//		}
//	private:
//		Type _m = 239.46;
//		Type _v = 0.2058;
//		Type _ro = 1035.71;
//		Type _k = 0.6;
//		Type _g = 9.8;
//	};
//
//	Rouge_Kuta<f1, long double> r1(0.0, 0.001, 90.0, 90.0 / 1000000);
//	double ret = r1.result();
//	//r1.printTable();
//	cout << endl;
//	cout << "result:" << endl;
//	cout << ret << endl;
//}
//
//void test()
//{
//	//函数定义 仿函数
//	struct f1
//	{
//		typedef long double Type;
//
//		Type operator()(Type x, Type y)
//		{
//			return x * x;
//		}
//	};
//
//	Rouge_Kuta<f1, long double> r1(0.0, 0.0, 1.0, 1.0 / 640);
//	double ret = r1.result();
//	r1.printTable();
//	cout << endl;
//	cout << "result:" << endl;
//	cout << ret << endl;
//}
//
//int main()
//{
//	//test();
//	question4_1();
//
//	return 0;
//}