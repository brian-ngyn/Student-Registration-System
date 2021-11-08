#include "date.h"
#include "course.h"
#include "student.h"

#include <string.h>
#include <iostream>

using namespace std;

Date::Date():year(0),month(0),day(0){}

Date::Date(int y, int m, int d): year(y), month(m), day(d){}

void Date::set_year(int y){
	year = y;
}
void Date::set_month(int m){
	month = m;
}
void Date::set_day(int d){
	day = d;
}

int Date::get_year() const{
	return year;
}
int Date::get_month() const{
	return month;
}
int Date::get_day() const{
	return day;
}
//return date information formated similar to the example provided in the supplementary material file
string Date::date_string(){
	return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
}
