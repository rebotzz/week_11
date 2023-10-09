#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

//日期类
class Date
{
	//友元函数,能访问private,protected
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);


public:

	//构造函数,对象实例化时自动调用,初始化成员
	Date(int year = 1, int month = 1, int day = 1)
	{
		this->_year = year;
		this->_month = month;
		this->_day = day;

		//检查日期合法性
		if (!CheckDate())
		{
			cout << "所构造日期非法" << endl;
		}
		assert(CheckDate());
	}

	//拷贝构造函数		默认浅拷贝够用
	Date(const Date& d)
	{
		this->_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	//析构函数		无资源需要释放,默认够用
	//~Date()
	//{

	//}

	//取地址,也会默认生成,一般不用写,除非不想让人取到地址	( Date* const d)
	Date* operator&()
	{
		return this;
	}

	//const取地址,也会默认生成	(const Date* const d)
	const Date* operator&() const
	{
		return this;
	}

	//打印日期,const修饰函数 ==> 修饰this指针,在这个函数作用域,this指向内容不能被修改,能接受临时对象(常数性)
	//void print(const Date* this) 
	void print() const
	{
		std::cout << _year << "-" << _month << "-" << _day << std::endl;

	}

	//成员函数定义和声明分离
	//日期==日期
	bool operator == (const Date& d) const;

	//日期 = 日期
	Date& operator=(const Date& d);

	//++日期
	Date& operator++();

	//日期++
	Date operator++(int);

	// 日期+=天数
	Date& operator+=(int day);
	// 日期+天数
	Date operator+(int day) const;
	// 日期-天数
	Date operator-(int day) const; 
	// 日期-=天数
	Date& operator-=(int day);

	// 日期--
	Date operator--(int);
	// --日期
	Date& operator--();

	// 日期>日期
	bool operator>(const Date& d) const;

	// 日期>=日期
	bool operator >= (const Date& d) const;

	// 日期<日期
	bool operator < (const Date& d) const;
	// 日期<=日期
	bool operator <= (const Date& d) const;
	// 日期!=日期
	bool operator != (const Date& d)const;
	// 日期-日期 返回天数
	int operator-(const Date& d)const;

	//operator<<(Date* const this, ostream& out)
	//d.operator<<(cout);
	//这种写法很奇怪,所以不采用,使用全局函数 + 友元函数
	ostream& operator<<(ostream& out)
	{
		out << _year << "-" << _month << "-" << _day;
		return out;
	}


protected:
	//获取某年某月的天数
	//频繁调用,inline
	int GetMonthDay(int year, int month)
	{
		//每月天数,常用,static
		static int mday[] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
		//判断时候是闰年2月:闰年%4,!%100,或 %400
		if (month == 2
			&& ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)))	//注意条件
		{
			//std::cout << "闰年二月:" << std::endl;
			return 29;
		}
		else
		{

			return mday[month];
		}
	}

	//检查日期合法性	合法,ture
	bool CheckDate()
	{
		if(_year > 0 
			&& (_month > 0 && _month < 13)
			&& (_day > 0 && _day <= GetMonthDay(_year, _month)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	//内置类型
	int _year;
	int _month;
	int _day;
};



//inline:定义和声明不能分离,没有符号表,直接展开,所以除了展开的地方,不能出现在别的地方,会链接报错
//运算符重载 << ,cout属于ostream类型对象
//返回类型==>为了支持连续使用,cout<<d1<<d2;
//cout为<<的左操作数,而成员函数的左操作数被this指针占领了,只能全局函数
inline ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日" ;
	return out;
}

//运算符重载 >> ,cin属于istream类型对象
inline istream& operator>>(istream& in, Date& d)
{
	in >> d._year >> d._month >> d._day;
	if (!d.CheckDate())
	{
		cout << "输入日期不合法." << endl;
	}
	return in;
}

//菜单
enum MEUN
{
	EXIT,	//0
	ADD_SUB_DAY,	//1
	SUB_DATE		//2
};