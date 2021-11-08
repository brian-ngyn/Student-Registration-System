#ifndef COURSE_H
#define COURSE_H
#include "program_functions.h"
#include "date.h"
#include "student.h"
#include <vector>

class Student;

struct student_record{
		Student* student;
		double grade;
};

class Course{
	private:
		const string Cid;
		Date start;
		Date end;
		int capacity;
		int enrolled;
		vector<student_record> student_list;
		// function to find student in the student_list. useful for enroll, withdraw and modify to check if the student is in the list and return the index
		int find_student(string id);
	public:
		// constructors and destructor
		Course();
		Course(string id, Date s, Date e, int max);
		~Course();
		
		// no need to implemetn other getters or setters
		string get_cid() const;
		Date get_start_date() const;
		Date get_end_date() const;
		int get_capacity() const;
		
		// adds a student to the student list. the student must exist as an object and the reference of the student object is passed to the function
		// the student should not be already enrolled in the course
		// this function must also add itself to the course_list of the student
		int enroll(Student* S_obj);
		// looks up the student id in the student list and removes the student from the student list and also updates the course list of the student object, be carefull with the sequence of how you do this.
		int withdraw(string uid);
		// modifies the grade of the student in the course. note that the grade must be updated in the course object and the corresponding student object
		void update_grade(string uid, double g);
		//return course info
		double get_grade(string uid);
		int is_enrolled(string uid);
		
		
		string course_info();
		//Course ID: ENSF337
		//Start date: 5/5/2021
		//End date: 6/17/2021
		//Capacity: 70
		//Enrolled: 0
		//List of students:
		//        Student name    Grade

		
};
#endif
