#ifndef STUDENT_H
#define STUDENT_H

#include <vector>
#include <string>
#include "date.h"
#include "course.h"
#include "program_functions.h"

using namespace std;

class Course;

struct course_record {
    Course* reg_course;
	double grade;
};

class Student{
	private:
		string Fname;
		string Lname;
		string phone;
		string ID;
		Date birthday;
		vector<course_record> course_list;
		// function to find course name in the course_list. useful for the modify grade function
		int find_course(string c_name);
	public:
		// constructors and destructor
		Student();
		Student(string first, string last, string cell, string uid, Date birth);
		~Student();
		
		//setters
		void set_Fname(string Fn);
		void set_Lname(string ln);
		void set_phone(string cell);
		void set_ID(string uid);
		void set_Date(Date bd);
		
		//getters
		string get_Fname() const;
		string get_Lname() const;
		string get_phone() const;
		string get_ID() const;
		Date get_Date() const;
		int get_course_list_size() const;

		const vector<course_record>& get_course_records() const;
		
		// function to add a course record to the vector course_list. to be called by the course object
		void add_course( Course* course_to_add, double g);
		// removes a course from the course list. to be called by the course object
		void drop_course( Course* course_to_drop);
		// function to modify a grade for a given course name. to be called by the course object
		void modify_grade( Course* course_to_modify, double grade_update);
		// returns a formated string of the student information. the format follows the example provided in the suplementary material
		string student_info();
		// Student id:
		// Firstname:      Last name:
		// constant number:
		// birth date:
		// courses list:
		//       course name           grade
		//        ENSF337				92
		
};
#endif
