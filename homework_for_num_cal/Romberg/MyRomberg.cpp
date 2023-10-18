#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <iomanip>  //������ͷ�ļ�
using namespace std;


//�����㷨	
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
		//Type gap = _table[K][K] - _table[K - 1][K - 1];//gap <= 3*_accy
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

				//Type gap = _table[i][i] - _table[i - 1][i - 1];//gap <= 3*_accy
				Type gap = _table[i][i] - _table[i][i - 1];		 //���������Ʒ���������
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


int main()
{
#define PI acos(-1.0)

	////��������
	//struct f1		//ע�⺯�����
	//{
	//	long double operator()(long double x)
	//	{
	//		return pow(x, 3.0 / 2);
	//	}
	//};
	//RombergIntegration<f1, long double> rg_example(0, 1, 0.00000001);
	//cout << "test example: " << endl;
	//rg_example.integral();
	//rg_example.print();
	//cout << endl;

	struct f2		//c = 1.5; m = 1
	{
		long double operator()(long double x)
		{
			return cos(x) * pow(1 - (1 - cos(x)) / (2 * 0.6), 1.5) / (2 * PI);
		}
	};

	struct f3		//c = 1.1; m = 1
	{
		long double operator()(long double x)
		{
			return cos(x) * pow(1 - (1 - cos(x)) / (2 * 0.6), 1.1) / (2 * PI);
		}
	};

	//�������� a = -1*acos(1.0 - 2 * 0.6); eplis = 0.6
	long double a = -1 * acos(-0.2);
	long double b = -a;

	RombergIntegration<f2, long double> rg1(a, b, 1.0E-7);
	RombergIntegration<f3, long double> rg2(a, b, 1.0E-7);

	cout << "when c = 1.5:" << endl;
	rg1.integral();
	rg1.print();
	cout << endl;

	cout << "when c = 1.1:" << endl;
	rg2.integral();
	rg2.print();
	cout << endl;

	return 0;
}