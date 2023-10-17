//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
//
//#include <iostream>
//#include <iomanip>  //������ͷ�ļ�
//#include <math.h>
//
//using namespace std;
//
////���������
//double deviation;
////��������������ϵ��
//double ratio[3][2] = { {4.0 / 3,1.0 / 3},{16.0 / 15,1.0 / 15},{64.0 / 63,1.0 / 63} };
////�������ɵĽڵ������
//double dataX[1000];
////�������ɵĽڵ�������
//double dataY[1000];
////��������������
//double table[100][100] = { 0 };
//int K = 5;  //���ִ���
////����һ����ѧ����
//double function(double x);
////�ָ�����
//void devide(double a, double b, int N);
////�����������
//double getIntegralValue(double a, double b, int N);
////�������ݲ������ڱ����
//void savaToTable(double a, double b);
////����table���,�����ؽ��
//double updateTable(double a, double b);
////���table
//void print();
//
//int main()
//{
//    double a, b;
//    cout << "��������ֵ�����:";
//    cin >> a;
//    cin >> b;
//    cout << "�����������:";
//    cin >> deviation;
//    double result = updateTable(a, b);
//    print();
//    cout << "the result is:" << result << endl;
//    return 0;
//}
//
////����һ����ѧ����
//double function(double x)
//{
//    //return sin(x) / x;
//    return pow(x, 3.0 / 2); //��x>=0������û�����
//}
////�ָ�����
//void devide(double a, double b, int N)
//{
//    double x = a;
//    double dX = (b - a) / (N);
//    //������㣬���⴦��
//    //dataX[0] = x;
//    //dataY[0] = function(a); 
//    for (int i = 0; i <= N; i++)
//    {
//        x = a + i * dX;
//        dataX[i] = x;
//        dataY[i] = function(x);
//    }
//}
////�����������
//double getIntegralValue(double a, double b, int N)
//{
//    devide(a, b, N);
//    double sum = 0;
//    //��2*f(xk)���ܺͣ�1<= k <= n-1
//    for (int i = 1; i <= N - 1; i++)
//    {
//        sum += 2 * dataY[i];
//    }
//    double value = 0.5 * ((b - a) / N) * (dataY[0] + sum + dataY[N]);
//    return value;
//}
////�������ݲ������ڱ����
//void savaToTable(double a, double b)
//{
//    for (int i = 0; i <= K; i++)
//    {
//        //����TK
//        table[i][0] = getIntegralValue(a, b, pow(2, i));
//    }
//    //���м���Sk,Ck,Rk
//    //i�����У�j������
//    //int k = 0;
//    for (int i = 1; i <= K; i++)
//    {
//        for (int j = i; j <= K; j++)
//        {
//            //double calcValue = table[j + 1][i] * ratio[k][0] - table[j][i] * ratio[k][1];
//
//            double index = pow(4, i);
//            double calcValue = table[j][i - 1] * index / (index - 1) - table[j - 1][i - 1] / (index - 1);
//            table[j][i] = calcValue;
//        }
//        //������һ�м���
//        //k++;
//    }
//}
////����table���,�����ؽ��
//double updateTable(double a, double b)
//{
//    savaToTable(a, b);
//    //������������Ҫ���򷵻�
//    double gap = table[K][K] - table[K - 1][K - 1];
//    if (gap < 0)
//        gap *= -1;
//    if (gap <= deviation)
//    {
//        return table[K][K];
//    }
//
//    //�������޲�����Ҫ�����������table��
//    else {
//        //i�����У�j������
//        for (int i = K + 1; ; i++)
//        {
//            //int k = 0;
//            //����table[i][0]
//            table[i][0] = getIntegralValue(a, b, pow(2, i));
//            for (int j = 1; j <= i; j++)
//            {
//                double index = pow(4, j);
//                table[i][j] = table[i][j - 1] * index / (index - 1) - table[i - 1][j - 1] / (index - 1);
//                //k++;
//            }
//
//            double gap = table[i][i] - table[i - 1][i - 1];
//            if (gap < 0)
//                gap *= -1;
//            if (gap <= deviation)
//            {
//                K = i;
//                return table[i][i];
//            }
//        }
//    }
//}
////���table
//void print()
//{
//    cout << "------------------------------------------------------------------" << endl;
//    cout << "k " << "   T     " << "    S     " << "   C     " << "    R    " << endl;
//    for (int i = 0; i <= K; i++)
//    {
//        cout << i << " ";
//        for (int j = 0; j <= i; j++)
//        {
//            //if (j <= 3)
//            {
//                cout.setf(ios::showpoint);
//                cout << setprecision(6) << table[i][j] << " ";
//            }
//        }
//        cout << endl;
//    }
//}