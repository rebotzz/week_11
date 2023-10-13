#pragma once
#include <iostream>	
#include <vector>	
using namespace std;

namespace NumericalCalculation
{
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
						ln *= (x - (double)xi[j]) / ((double)xi[i] - (double)xi[j]);
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

}

namespace NumericalCalculation
{
	void test_L_N()
	{
		//��ֵ��
		vector<double> xi = { 2005,2010,2015,2020 };
		vector<double> yi1 = { 72.8,74.2,75.2,76.4 };
		vector<double> yi2 = { 70.2,70.2,70.3,71.2 };

		//�����
		vector<double> x = { 2000,2013,2018,2025 };

		//Interpolate<double, vector<double>> ln1(x, xi, yi1);
		//Interpolate<double, vector<double>> ln2(x, xi, yi2);
		Interpolate<double> ln1(x, xi, yi1);
		Interpolate<double> ln2(x, xi, yi2);

		auto l1 = ln1.Lagrange();
		auto l2 = ln2.Lagrange();
		auto n1 = ln1.Newton();
		auto n2 = ln2.Newton();

		//��ӡ���
		cout << "�������:" << endl;
		for (auto e : x)
		{
			cout << e << " ";
		}
		cout << endl;

		cout << "�������գ�" << endl;
		cout << "������,����һ:" << endl;
		for (auto e : l1)
		{
			cout << e << " ";
		}
		cout << endl;
		cout << "������,������:" << endl;
		for (auto e : l2)
		{
			cout << e << " ";
		}
		cout << endl;
		cout << endl;

		cout << "ţ�٣�" << endl;
		cout << "������,����һ:" << endl;
		for (auto e : n1)
		{
			cout << e << " ";
		}
		cout << endl;
		cout << "������,������:" << endl;
		for (auto e : n2)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}