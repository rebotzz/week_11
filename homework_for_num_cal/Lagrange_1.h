#pragma once
#include <iostream>
#include <vector>
using namespace std;

//�������ղ�ֵ��
//��ֵ��xi, yi; �����x
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


//��һ��:
void question1_1()
{
	//��ֵ��
	vector<double> xi = { 2005,2010,2015,2020 };
	vector<double> yi1 = { 72.8,74.2,75.2,76.4 };
	vector<double> yi2 = { 70.2,70.2,70.3,71.2 };

	//�����
	vector<double> x = { 2000,2013,2018,2025 };
	vector<double> y1(4, 1);
	vector<double> y2(4, 1);

	//���
	for (size_t i = 0; i < x.size(); ++i)
	{
		y1[i] = Lagrange(x[i], xi, yi1);
		y2[i] = Lagrange(x[i], xi, yi2);
	}

	//��ӡ���
	cout << "�������:" << endl;
	for (auto e : x)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "������,����һ:" << endl;
	for (auto e : y1)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "������,������:" << endl;
	for (auto e : y2)
	{
		cout << e << " ";
	}
	cout << endl;
}


////ţ�ٲ�ֵ	1.0	ʱ�临�Ӷ�O��N^2��,�ռ临�Ӷ�O��N^2��
//template<class T>
//T newton(T x, const vector<T>& xi, const vector<T>& yi)
//{
//	//����
//	size_t n = yi.size() - 1;
//	vector<T> tmp(n + 1, 0);
//	vector<vector<T>> fi(n + 1, tmp);	
//	//0�ײ��̣���yi
//	fi[0] = yi;
//
//	//cout << "��ʼ�����̱���" << endl;
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
//	//��㣬���̽���
//	for (size_t i = 1; i <= n; ++i)
//	{
//		//�ڲ㣬��ͬ����
//		for (size_t j = i; j <= n; ++j)
//		{
//			fi[i][j] = (fi[i - 1][j] - fi[i - 1][j - 1]) / (xi[j] - xi[j - i]);	//debug:������j - i
//		}
//	}
//
//	//cout << "�������̱���" << endl;
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
//	//���ֵ���ڲ�ֵ����ʽ��ֵ
//	double p = yi[0];
//	for (size_t i = 1; i <= n; ++i)
//	{
//		//fi[i][n - i + 1]*(x - xi[n - i]) + fi[i]
//
//		//������
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



////ţ�ٲ�ֵ	2.0	ʱ�临�Ӷ�O��N^2��,�ռ临�Ӷ�O��N^2��
//template<class T>
//T newton(T x, const vector<T>& xi, const vector<T>& yi)
//{
//	//����
//	size_t n = yi.size() - 1;
//	vector<T> tmp(n + 1, 0);
//	vector<vector<T>> fi(n + 1, tmp);
//	//0�ײ��̣���yi
//	fi[0] = yi;
//
//	//��㣬���̽���
//	for (size_t i = 1; i <= n; ++i)
//	{
//		//�ڲ㣬��ͬ����
//		for (size_t j = i; j <= n; ++j)
//		{
//			fi[i][j] = (fi[i - 1][j] - fi[i - 1][j - 1]) / (xi[j] - xi[j - i]);	//debug:������j - i
//		}
//	}
//
//	//���ֵ���ڲ�ֵ����ʽ��ֵ
//	//��ֵ����ʽ
//	double p = fi[n][n];
//	for (size_t i = n; i > 0; --i)
//	{
//		p *= (x - xi[i - 1]);
//		p += fi[i - 1][i - 1];
//	}
//
//	return p;
//}

//ţ�ٲ�ֵ	3.0	ʱ�临�Ӷ�O��N^2��,�ռ临�Ӷ�O��N��
template<class T>
T newton(T x, const vector<T>& xi, const vector<T>& yi)
{
	//����
	size_t n = yi.size() - 1;
	vector<T> fi(yi);		//0�ײ��̣���yi
	vector<T> fi_last(fi);	//��һ�����

	//��㣬���̽���
	for (size_t i = 1; i <= n; ++i)
	{
		//�ڲ�
		for (size_t j = i; j <= n; ++j)
		{
			fi[j] = (fi_last[j] - fi_last[j - 1]) / (xi[j] - xi[j - i]);	//debug:������j - i
		}
		fi_last = fi;
	}

	//���ֵ���ڲ�ֵ����ʽ��ֵ
	//��ֵ����ʽ
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
	//��ֵ��
	vector<double> xi = { 2005,2010,2015,2020 };
	vector<double> yi1 = { 72.8,74.2,75.2,76.4 };
	vector<double> yi2 = { 70.2,70.2,70.3,71.2 };

	//�����
	vector<double> x = { 2000,2013,2018,2025 };
	vector<double> y1(4, 1);
	vector<double> y2(4, 1);

	//���
	for (size_t i = 0; i < x.size(); ++i)
	{
		y1[i] = newton(x[i], xi, yi1);
		y2[i] = newton(x[i], xi, yi2);
	}

	//��ӡ���
	cout << "�������:" << endl;
	for (auto e : x)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "������,����һ:" << endl;
	for (auto e : y1)
	{
		cout << e << " ";
	}
	cout << endl;
	cout << "������,������:" << endl;
	for (auto e : y2)
	{
		cout << e << " ";
	}
	cout << endl;
}