//////#include <iostream>
//////#include <cmath>
//////
//////// 定义常微分方程 dy/dx = x^2 + y^2
//////double f(double x, double y)
//////{
//////    return std::pow(x, 2) + std::pow(y, 2);
//////}
//////
//////// 使用欧拉方法求解常微分方程
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
//////    double x0 = 0.0; // 初始 x 值
//////    double y0 = 1.0; // 初始 y 值
//////    double h = 0.1;  // 步长
//////    double x = 1.0;  // 要求解的 x 值
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
//////// 最小二乘法求解线性回归
//////void leastSquares(const std::vector<double>& x, const std::vector<double>& y)
//////{
//////    int n = x.size(); // 数据点个数
//////
//////    double sumX = 0.0; // x 的和
//////    double sumY = 0.0; // y 的和
//////    double sumXY = 0.0; // x*y 的和
//////    double sumX2 = 0.0; // x^2 的和
//////
//////    for (int i = 0; i < n; i++)
//////    {
//////        sumX += x[i];
//////        sumY += y[i];
//////        sumXY += x[i] * y[i];
//////        sumX2 += x[i] * x[i];
//////    }
//////
//////    double meanX = sumX / n; // x 的均值
//////    double meanY = sumY / n; // y 的均值
//////
//////    // 计算斜率和截距
//////    double slope = (sumXY - n * meanX * meanY) / (sumX2 - n * meanX * meanX);
//////    double intercept = meanY - slope * meanX;
//////
//////    std::cout << "斜率： " << slope << std::endl;
//////    std::cout << "截距： " << intercept << std::endl;
//////}
//////
//////int main()
//////{
//////    std::vector<double> x = { 1.0, 2.0, 3.0, 4.0, 5.0 }; // x 数据点
//////    std::vector<double> y = { 2.0, 3.0, 4.0, 5.0, 6.0 }; // y 数据点
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
////// 被积函数 f(x)
////double f(double x)
////{
////    return std::sin(x);
////}
////
////// Romberg算法求解积分
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
////    double a = 0.0; // 积分下限
////    double b = 3.14159; // 积分上限
////    int n = 5; // 迭代次数
////
////    double result = rombergIntegration(a, b, n);
////
////    std::cout << "积分结果： " << result << std::endl;
////
////    return 0;
////}
//
//
//#include <iostream>
//#include <cmath>
//
//#define N 3             // 线性方程组的维度
//#define MAX_ITER 100   // 最大迭代次数
//#define EPSILON 1e-6   // 精度要求
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
//            error += std::fabs(newX[i] - x[i]); //C 库函数 double fabs(double x) 返回浮点数 x 的绝对值。
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
