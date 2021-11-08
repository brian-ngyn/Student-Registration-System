#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

class Date{
	private:
		int year;
		int month;
		int day;
	public:
		Date();
		Date(int y, int m, int d);
	//setters
		void set_year(int y);
		void set_month(int m);
		void set_day(int d);
	//getters
		int get_year() const;
		int get_month() const;
		int get_day() const;
	//return date information formated similar to the example provided in the supplementary material file
		string date_string();
		// Date: mm/dd/yyyy
};

#endif
