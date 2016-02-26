#include <iostream>

namespace Chrono{

	using namespace std;
	class Date{
	public:
		enum Month{
			jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
		};
		typedef int Year;

		class Invalid{};  //to throw as exception

		Date(Year y, Month m, int d);
		Date();

		int day() const{return d;}
		Month month() const{return m;}
		int year() const{return y;}

		void add_day(int n);
		void add_month(int n);
		void add_year(int n);
	private:
		int y;
		Month m;
		int d;
	};
	
	bool is_date(int y, Date::Month m, int d);

	bool leapyear(int y);

	bool check(int y, Date::Month m, int d);

	bool operator==(const Date& a, const Date& b);

	bool operator!=(const Date& a, const Date& b);

	ostream& operator<<(ostream & os, Date& d);

	istream& operator>>(istream & is, Date& d);
}
