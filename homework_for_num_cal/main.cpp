#define _CRT_SECURE_NO_WARNINGS
#include "question.h"


void test2()
{
    // �����Ǽ������
    const int N = 1;

    // ��������vector
    vector<float> x, y;
	y = { 18.9,18.9,18.3,17.8,17.2,17.2,16.7,16.7,15.6,15.6,15,14.4,
		14.4,14.4,14.4,14.4,13.9,13.9,13.9,14.4,15.6,17.8,19.4,20 };
	x.reserve(y.size());
	for (size_t i = 0; i < y.size(); ++i)
	{
		x.push_back(i + 1);
	}

	//A*W = B
    // ����A����
    Eigen::MatrixXd A(x.size(), N + 1);

    for (unsigned int i = 0; i < x.size(); ++i) {  // �������е�

        for (int n = N, dex = 0; n >= 1; --n, ++dex) {  // ����N��1��
            A(i, dex) = pow(x[i], n);
        }

        A(i, N) = 1;  //
    }

    // ����B����
    Eigen::MatrixXd B(y.size(), 1);

    for (unsigned int i = 0; i < y.size(); ++i) {
        B(i, 0) = y[i];
    }

    // ��������W
    Eigen::MatrixXd W;
    W = (A.transpose() * A).inverse() * A.transpose() * B;

    // ��ӡW���
    cout << W << endl;
}


int main()
{
    //question1_1();
    cout << "------------" << endl;
	//question2_1();
    question3_1();

	return 0;
}

