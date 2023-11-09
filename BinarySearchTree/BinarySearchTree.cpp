#define _CRT_SECURE_NO_WARNINGS
#include "BinarySearchTree.h"

void testBSTree1()
{
	//int a[] = { 8, 3, 1 };
	//int a[] = { 8, 3, 1, 10 };
	//int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 0, 2, 11, 9 };
	BSTree<int> b;

	for (auto e : a)
	{
		b.Insert(e);
	}

	b.InOrder();
	//b.Erase(0);
	//b.InOrder();
	//b.Erase(13);
	//b.InOrder();
	//b.Erase(3);
	//b.InOrder();
	//b.Erase(17);
	//b.InOrder();

	for (auto e : a)
	{
		cout << e << ": ";
		b.InOrder();
		b.Erase(e);
	}
	b.InOrder();

	//for (int i = 3; i < sizeof(a) / sizeof(a[0]); i++)
	//{
	//	cout << a[i] << ": ";
	//	b.InOrder();
	//	b.Erase(a[i]);
	//}
	//b.InOrder();

}

void testBSTree2()
{
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	BSTree<int> b;

	for (auto e : a)
	{
		b.InsertR(e);
	}
	b.InOrder();

	//cout << b.FindR(14) << endl;
	//cout << b.FindR(15) << endl;
	//cout << b.FindR(1) << endl;
	//cout << b.FindR(7) << endl;


	//b.EraseR(8);
	//b.InOrder();

	//for (auto e : a)
	//{
	//	cout << e << ": ";
	//	b.InOrder();
	//	b.EraseR(e);
	//}
	//b.InOrder();
}

int main()
{
	testBSTree2();

	return 0;
}
