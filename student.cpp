#include "date.h"
#include "course.h"
#include "student.h"
#include<string.h>
#include <iostream>
#include<vector>
using namespace std;
//constructors and destructors
Student::Student(): Fname("NONE"), Lname("NONE"), phone("NONE"), ID("NONE"), birthday() {}

Student::Student(string first, string last, string cell, string uid, Date birth):Fname(first), Lname(last), phone(cell), ID(uid), birthday(birth){}

Student::~Student(){}

void Student::set_Fname(string Fn)
{
	Fname = Fn;
}
void Student::set_Lname(string ln)
{
	Lname = ln;
}

void Student::set_phone(string cell)
{
	phone = cell;
}

void Student::set_ID(string uid)
{
	ID = uid;
}

void Student::set_Date(Date bd)
{
	birthday = bd;
}

string Student::get_Fname() const
{
	return Fname;
}

string Student::get_Lname() const
{
	return Lname;
}

string Student::get_phone() const
{
	return phone;
}

string Student::get_ID() const
{
	return ID;
}

Date Student::get_Date() const
{
	return birthday;
}

const vector<course_record>& Student::get_course_records() const
{	
	return course_list;
}
int Student::get_course_list_size() const
{
	return (int) course_list.size();
}

//creates course record structure and adds the student object as well as grade to struct. adds struct to course list.
void Student::add_course( Course* course_to_add, double g)
{
	struct course_record a = { course_to_add, g };
	course_list.push_back(a);
}
//iterates through course list and finds the corresponding course_record struct then deletes it from the list.
void Student::drop_course(Course* course_to_drop)
{
	for(int i = 0; i < (int) course_list.size();i++)
	{
		if(course_list[i].reg_course->get_cid() == course_to_drop->get_cid())
		{
			course_list.erase(course_list.begin()+i);
			break;
		}
	}
}
//finds course in course list and updates the grade in the struct.
void Student::modify_grade( Course* course_to_modify, double grade_update)
{
	int i = find_course(course_to_modify->get_cid());
	course_list[i].grade = grade_update;
}
//creates base structure of string type with the object info then uses a loop to display the courses and grades.
//returns the two strings concatenated.
string Student::student_info()
{
	string result = "\nStudent ID: " + ID + "\n" + "First Name: " + Fname + "\nLast Name: " + Lname + "\n"
	+"Phone number: " + phone + "\n" + "Birth Date: " + to_string(birthday.get_day()) + "/" + to_string(birthday.get_month()) + "/" + to_string(birthday.get_year()) + "\n" 
	+"Courses List: " + "\n" + "Course Name	Grade\n" + "-----------------------------\n";

	string courses;
	
	for(int i = 0; i < (int) course_list.size(); i++)
	{
		courses+= course_list[i].reg_course->get_cid() + "		" + to_string(course_list[i].grade) + "\n";
	}
	return result + courses;
}	
//iterates through the course list and finds the given course name
int Student::find_course(string c_name)
{
	for(int i = 0; i < (int) course_list.size(); i++)
	{
		if(c_name == course_list[i].reg_course->get_cid())
		{
			return i;
		}
	}
	return -1;
}
