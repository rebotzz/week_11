//////#include <iostream>
//////#include <cmath>
//////
//////// ���峣΢�ַ��� dy/dx = x^2 + y^2
//////double f(double x, double y)
//////{
//////    return std::pow(x, 2) + std::pow(y, 2);
//////}
//////
//////// ʹ��ŷ��������ⳣ΢�ַ���
//////void eulerMethod(double x0, double y0, double h, double x)
//////{
//////    double y = y0;
//////    while (x0 < x)
//////    {
//////        y += h * f(x0, y);
//////        x0 += h;
//////    }
//////    std::cout << "y(" << x << ") = " << y << std::endl;
//////}
//////
//////int main()
//////{
//////    double x0 = 0.0; // ��ʼ x ֵ
//////    double y0 = 1.0; // ��ʼ y ֵ
//////    double h = 0.1;  // ����
//////    double x = 1.0;  // Ҫ���� x ֵ
//////
//////    eulerMethod(x0, y0, h, x);
//////
//////    return 0;
//////}
////
////
//////#include <iostream>
//////#include <vector>
//////#include <cmath>
//////
//////// ��С���˷�������Իع�
//////void leastSquares(const std::vector<double>& x, const std::vector<double>& y)
//////{
//////    int n = x.size(); // ���ݵ����
//////
//////    double sumX = 0.0; // x �ĺ�
//////    double sumY = 0.0; // y �ĺ�
//////    double sumXY = 0.0; // x*y �ĺ�
//////    double sumX2 = 0.0; // x^2 �ĺ�
//////
//////    for (int i = 0; i < n; i++)
//////    {
//////        sumX += x[i];
//////        sumY += y[i];
//////        sumXY += x[i] * y[i];
//////        sumX2 += x[i] * x[i];
//////    }
//////
//////    double meanX = sumX / n; // x �ľ�ֵ
//////    double meanY = sumY / n; // y �ľ�ֵ
//////
//////    // ����б�ʺͽؾ�
//////    double slope = (sumXY - n * meanX * meanY) / (sumX2 - n * meanX * meanX);
//////    double intercept = meanY - slope * meanX;
//////
//////    std::cout << "б�ʣ� " << slope << std::endl;
//////    std::cout << "�ؾࣺ " << intercept << std::endl;
//////}
//////
//////int main()
//////{
//////    std::vector<double> x = { 1.0, 2.0, 3.0, 4.0, 5.0 }; // x ���ݵ�
//////    std::vector<double> y = { 2.0, 3.0, 4.0, 5.0, 6.0 }; // y ���ݵ�
//////
//////    leastSquares(x, y);
//////
//////    return 0;
//////}
////
////
////#include <iostream>
////#include <cmath>
////#include <vector>
////
////// �������� f(x)
////double f(double x)
////{
////    return std::sin(x);
////}
////
////// Romberg�㷨������
////double rombergIntegration(double a, double b, int n)
////{
////    std::vector<std::vector<double>> R(n, std::vector<double>(n, 0.0));
////
////    double h = b - a;
////    R[0][0] = (f(a) + f(b)) * h / 2.0;
////
////    for (int i = 1; i < n; i++)
////    {
////        h /= 2.0;
////        double sum = 0.0;
////        for (int j = 1; j <= std::pow(2, i - 1); j++)
////        {
////            sum += f(a + (2 * j - 1) * h);
////        }
////        R[i][0] = R[i - 1][0] / 2.0 + sum * h;
////        for (int k = 1; k <= i; k++)
////        {
////            R[i][k] = R[i][k - 1] + (R[i][k - 1] - R[i - 1][k - 1]) / (std::pow(4, k) - 1.0);
////        }
////    }
////
////    return R[n - 1][n - 1];
////}
////
////int main()
////{
////    double a = 0.0; // ��������
////    double b = 3.14159; // ��������
////    int n = 5; // ��������
////
////    double result = rombergIntegration(a, b, n);
////
////    std::cout << "���ֽ���� " << result << std::endl;
////
////    return 0;
////}
//
//
//#include <iostream>
//#include <cmath>
//
//#define N 3             // ���Է������ά��
//#define MAX_ITER 100   // ����������
//#define EPSILON 1e-6   // ����Ҫ��
//
//void gaussSeidel(double A[N][N], double b[N], double x[N]) {
//    double newX[N];
//    int iter = 0;
//    double error = 0.0;
//
//    do {
//        for (int i = 0; i < N; i++) {
//            newX[i] = b[i];
//            for (int j = 0; j < N; j++) {
//                if (j != i) {
//                    newX[i] -= A[i][j] * x[j];
//                }
//            }
//            newX[i] /= A[i][i];
//        }
//
//        error = 0.0;
//        for (int i = 0; i < N; i++) {
//            error += std::fabs(newX[i] - x[i]); //C �⺯�� double fabs(double x) ���ظ����� x �ľ���ֵ��
//            x[i] = newX[i];
//        }
//
//        iter++;
//    } while (iter < MAX_ITER && error > EPSILON);
//}
//
//int main() {
//    double A[N][N] = { {4, 1, -1},
//                      {2, 7, 1},
//                      {1, -3, 12} };
//    double b[N] = { 3, 19, 31 };
//    double x[N] = { 0, 0, 0 };
//
//    gaussSeidel(A, b, x);
//
//    std::cout << "Solution: ";
//    for (int i = 0; i < N; i++) {
//        std::cout << x[i] << " ";
//    }
//    std::cout << std::endl;
//
//    return 0;
//}
