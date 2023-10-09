#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"

//日期==日期		
bool Date::operator == (const Date& d) const
{
	return _year == d._year
		&& _month == d._month
		&& _day == d._day;
}

//日期 = 日期		针对两个都已存在,d2.operator=(d1)
Date& Date::operator=(const Date& d)
{
	if (this != &d)	//出去自己给自己赋值
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}
	return *this;	//出来作用域还在,返回引用
}

//++日期
Date& Date::operator++()
{
	//1.0
	//_day++;
	//int day = GetMonthDay(_year, _month);
	//if (_day > day)
	//{
	//	_day -= day;
	//	_month++;
	//	if (_month > 12)
	//	{
	//		_month = 1;
	//		_year++;
	//	}
	//}

	//2.0
	* this += 1;	//复用:+=日期

	return *this;
}

//日期++
Date Date::operator++(int)
{
	Date tmp = *this;
	*this += 1;		//复用:+=日期
	return tmp;
}

// 日期+=天数
Date& Date::operator+=(int day)		//d.operator+=(day);
{
	//day < 0 的情况
	// d + (-|day|) = d - |day|
	if (day < 0)
	{
		day = -day;
		*this -= day;
		return *this;
	}

	_day += day;
	int maxday = GetMonthDay(_year, _month);
	while (_day > maxday)	//调整日期,使其格式合法
	{
		_day -= maxday;
		_month++;
		if (_month > 12)
		{
			_month = 1;
			_year++;
		}
		maxday = GetMonthDay(_year, _month);
	}
	return *this;
}
// 日期+天数
Date Date::operator+(int day) const
{
	Date tmp(*this);
	tmp += day;		//复用 +=
	return tmp;
}
// 日期-天数
Date Date::operator-(int day) const
{
	Date tmp(*this);
	tmp -= day;		//复用 -=
	return tmp;
}
// 日期-=天数
Date& Date::operator-=(int day)
{
	//day < 0 天数小于0的情况
	// d - (-|day|) = d + |day|
	if (day < 0)
	{
		day = -day;
		*this += day;
		return *this;
	}

	_day -= day;
	//日期为正数:合法 ; 日期为负数,上一个月
	while (_day <= 0)
	{
		_month--;
		if (_month == 0)
		{
			_month = 12;
			_year--;
		}

		_day += GetMonthDay(_year, _month);
	}

	return *this;
}

// 日期--
Date Date::operator--(int)
{
	Date tmp = *this;
	*this -= 1;		//复用 -=
	return tmp;
}
// --日期
Date& Date::operator--()
{
	*this -= 1;		//复用 -=
	return *this;
}

// 日期>日期
bool Date::operator>(const Date& d) const
{
	if (_year > d._year)	//年大
	{
		return true;
	}
	else if (_year == d._year && _month > d._month)		//年相等,月大
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day > d._day)	//年,月相等,天数大
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 日期>=日期
bool Date::operator >= (const Date& d) const
{
	return (*this == d) || (*this > d);	//复用 == >
}

// 日期<日期
bool Date::operator < (const Date& d)const
{
	return !(*this >= d);	//复用 >=
}
// 日期<=日期
bool Date::operator <= (const Date& d)const
{
	return !(*this > d);	//复用 >
}
// 日期!=日期
bool Date::operator != (const Date& d)const
{
	return !(*this == d);	//复用 ==
}
//// 日期-日期 返回天数		1.0
//int Date::operator-(const Date& d)
//{
//	Date d1 = *this;	//大日期
//	Date d2 = d;		//小日期
//	int symbol = 1;		//正负号
//	int day = 0;		//相差天数
//	if (d1 < d2)
//	{
//		d1 = d;
//		d2 = *this;
//		symbol = -1;
//	}
//
//	//年月日分别调整	小日期d2增加,直至等于d1
//	while (d1._year != d2._year)
//	{
//		//分界:3/1号,3/1之前可能存在2/29;
//		//3/1号之后跨年:考虑明年可能是闰年;之前,考虑今年是闰年	==> 影响跨年天数
//		if (d2._month >= 3)
//		{
//			d2._year++;
//			if ((d2._year % 4 == 0 && d2._year % 100 != 0) || (d2._year % 400 == 0))
//			{
//				day += 366;
//			}
//			else
//			{
//				day += 365;
//			}
//		}
//		else
//		{
//			if ((d2._year % 4 == 0 && d2._year % 100 != 0) || (d2._year % 400 == 0))
//			{
//				day += 366;
//			}
//			else
//			{
//				day += 365;
//			}
//			d2._year++;
//		}
//	}
//
//	//计算两者相对于1/1号的天数
//	int day1 = 0;
//	int day2 = 0;
//	Date tmp(d1._year, 1, 1);
//	while (tmp._month < d1._month)
//	{
//		day1 += GetMonthDay(tmp._year, tmp._month);
//		tmp._month++;
//	}
//	day1 += d1._day - tmp._day;
//
//	tmp._month = tmp._day = 1;	//初始化
//	while (tmp._month < d2._month)
//	{
//		day2 += GetMonthDay(tmp._year, tmp._month);
//		tmp._month++;
//	}
//	day2 += d2._day - tmp._day;
//
//	//两者相差天数
//	int gap = day1 - day2;
//	day += gap;
//	return symbol * day;
//}

// 日期-日期 返回天数	代码优化2.0
int Date::operator-(const Date& d)const
{
	Date max = *this;	//大日期
	Date min = d;		//小日期
	int symbol = 1;		//正负号
	int day = 0;		//相差天数
	if (max < min)
	{
		max = d;
		min = *this;
		symbol = -1;
	}

	while (max != min)
	{
		min += 1;
		day += 1;
	}
	return symbol*day;
}


