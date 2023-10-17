//#define _CRT_SECURE_NO_WARNINGS
//
//#include <iostream>
//#include <iomanip>  //流控制头文件
//#include <math.h>
//
//using namespace std;
//
////定义误差限
//double deviation;
////保存龙贝格计算的系数
//double ratio[3][2] = { {4.0 / 3,1.0 / 3},{16.0 / 15,1.0 / 15},{64.0 / 63,1.0 / 63} };
////保存生成的节点横坐标
//double dataX[1000];
////保存生成的节点纵坐标
//double dataY[1000];
////保存计算出的数据
//double table[100][100] = { 0 };
//int K = 4;  //二分次数
////定义一个数学函数
//double function(double x);
////分割区间
//void devide(double a, double b, int N);
////复化梯形求积
//double getIntegralValue(double a, double b, int N);
////计算数据并保存在表格中
//void savaToTable(double a, double b);
////更新table表格,并返回结果
//double updateTable(double a, double b);
////输出table
//void print();
//
//int main()
//{
//    double a, b;
//    cout << "请输入积分的区间:";
//    cin >> a;
//    cin >> b;
//    cout << "请输入误差限:";
//    cin >> deviation;
//    double result = updateTable(a, b);
//    print();
//    cout << "the result is:" << result << endl;
//    return 0;
//}
//
////定义一个数学函数
//double function(double x)
//{
//    //return sin(x) / x;
//    return pow(x, 3.0 / 2); //在x>=0练习，没有奇点
//}
////分割区间
//void devide(double a, double b, int N)
//{
//    double x = a;
//    double dX = (b - a) / (N);
//    //当有奇点，特殊处理
//    //dataX[0] = x;
//    //dataY[0] = function(a); 
//    for (int i = 0; i <= N; i++)
//    {
//        x = a + i * dX;
//        dataX[i] = x;
//        dataY[i] = function(x);
//    }
//}
////复化梯形求积
//double getIntegralValue(double a, double b, int N)
//{
//    devide(a, b, N);
//    double sum = 0;
//    //求2*f(xk)的总和，1<= k <= n-1
//    for (int i = 1; i <= N - 1; i++)
//    {
//        sum += 2 * dataY[i];
//    }
//    double value = 0.5 * ((b - a) / N) * (dataY[0] + sum + dataY[N]);
//    return value;
//}
////计算数据并保存在表格中
//void savaToTable(double a, double b)
//{
//    for (int i = 0; i <= K; i++)
//    {
//        //更新TK
//        table[i][0] = getIntegralValue(a, b, pow(2, i));
//    }
//    //进行计算Sk,Ck,Rk
//    //i代表列，j代表行
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
//        //进行下一列计算
//        //k++;
//    }
//}
////更新table表格,并返回结果
//double updateTable(double a, double b)
//{
//    savaToTable(a, b);
//    //如果误差限满足要求则返回
//    if (table[4][3] - table[3][3] <= deviation)
//    {
//        return table[4][3];
//    }
//    //如果误差限不满足要求，则继续更新table表
//    else {
//        //i代表行，j代表列
//        for (int i = 5; ; i++)
//        {
//            int k = 0;
//            //更新table[i][0]
//            table[i][0] = getIntegralValue(a, b, pow(2, i));
//            for (int j = 0; j < 3; j++)
//            {
//                table[i][j + 1] = table[i][j] * ratio[k][0] - table[i - 1][j] * ratio[k][0];
//                k++;
//            }
//            if (table[i][3] - table[i - 1][3] <= deviation)
//            {
//                return table[i][3];
//            }
//        }
//    }
//}
////输出table
//void print()
//{
//    cout << "------------------------------------------------------------------" << endl;
//    cout << "k " << "   T     " << "    S     " << "   C     " << "    R    " << endl;
//    for (int i = 0; i <= 4; i++)
//    {
//        cout << i << " ";
//        for (int j = 0; j <= i; j++)
//        {
//            if (j <= 3)
//            {
//                cout.setf(ios::showpoint);
//                cout << setprecision(6) << table[i][j] << " ";
//            }
//        }
//        cout << endl;
//    }
//}