#include "Chrono.h"

namespace Chrono{
	Date::Date(Year yy, Month mm, int dd)
		:y(yy), m(mm), d(dd){
		if(!check(yy,mm,dd))throw Invalid();
	}
	Date::Date(){}
/*	
	const Date* default_date(){
		const Date *p = new const Date dd(2001, Date::jan, 1);
		return p;
	}
	Date::Date():y(default_date().year()), m(default_date().month()), d(default_date().day())
	{
	}
*/

	void Date::add_day(int n){
		//...
	}
	void Date::add_month(int n){
		//...
	}
	void Date::add_year(int n){
		if(m==feb && d==29 && !leapyear(y+n)){
				m=mar;
				d=1;
		}
		y+=n;
	}

	bool is_date(int y, Date::Month m, int d){
		if(d<=0)return false;

		int days_in_month=30;

		switch(m){
			case Date::jan: case Date::mar: case Date::may: case Date::jul: case Date::aug: case Date::oct: case Date::dec:
			{
				days_in_month=31;
				break;
			}
			case Date::feb:
			{
				days_in_month=(leapyear(y))?29:28;
				break;
			}																				default:
				days_in_month=30;
		}
			if(days_in_month<d)return false;
			return true;
	}
	bool leapyear(int y){
		//...
		//Fix this function to make it work correctly
		return false;
	}

	bool check(int y, Date::Month m, int d){
		//...
		return true;
	}
	bool operator==(const Date& a, const Date& b){
		return a.year()==b.year() && a.month()==b.month() && a.day()==b.day();
	}
	bool operator!=(const Date& a, const Date& b){
		return !(a==b);
	}

	ostream& operator<<(ostream & os, Date& d){
		return os<<'('<<d.year()<<','<<d.month()<<','<<d.day()<<')';
	}

	istream& operator>>(istream & is, Date& dd){
		int y, d;
		//Date::Month m;
		int m;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if(!is)return is;
		if(ch1!='(' || ch2!=',' || ch3!=',' || ch4!=')'){
			is.clear(ios_base::failbit);
			return is;
		}
		dd = Date(y,Date::Month(m),d);
		return is;
	}

	enum Day{sunday, monday, tuesday, wednesday, thursday, friday, saturday};
/*
	Day day_of_week(const Date& d){
		//...
	}

	Date next_sunday(const Date& d){
		//...
	}
	Date next_weekday(const Date& d){
		//...
	}
*/	
} //Chrono