#include "date.h"
#include "course.h"
#include "student.h"
#include "program_functions.h"
#include<string.h>
#include <iostream>
#include<fstream>
using namespace std;


Course::Course(): Cid("0"), start(0,0,0), end(0,0,0), capacity(0), enrolled(0) {}

Course::Course(string id, Date s, Date e, int cap): Cid(id), start(s), end(e), capacity(cap) {
	enrolled = 0;
}

Course::~Course(){
}

string Course::Course::get_cid() const
{
	return Cid;
}

Date Course::get_start_date() const {
	return start;
}

Date Course::get_end_date() const {
	return end;
}

int Course::get_capacity() const {
	return capacity;
}

int Course::enroll(Student* S_obj) {
	// Check if class is at max capacity before enrolling
	
	if(capacity == enrolled){
		cout<<"Class is full."<<endl;
		return -1;
	}

	// Check if student is already enrolled
	for(int i = 0; i < (int) student_list.size(); i++){
		if(S_obj->get_ID() == student_list[i].student->get_ID()){
			cout<<"A student is already enrolled."<<endl;
			return 0;
		}
	}

	// Add student to the student list of the course and increase enrolled by one
	struct student_record s;
	s.student = S_obj;
	student_list.push_back(s);
	S_obj->add_course(this, 0);
	enrolled++;
	return 1;
}

int Course::withdraw(string uid) {

	// Find student from student list
	for(int i = 0; i < (int) student_list.size(); i++){
		if(student_list[i].student->get_ID() == uid){

			// Drop student from course 
			student_list[i].student->drop_course(this);
			student_list.erase(student_list.begin()+(i));
			enrolled--;
			return i;
		}
	}
	cout << "Error: Unable to find student with ID: " << uid << endl;
	return -1;
}

void Course::update_grade(string uid, double g){
	// find the student from the student list
	for(int i = 0; i < (int) student_list.size(); i++){
		if(uid == student_list[i].student->get_ID()){

			// Update student Grade
			student_list[i].grade = g;
			student_list[i].student->modify_grade(this, g);
			break;
		}
	}
}
double Course::get_grade(string uid)
{
	for(int i = 0; i < (int) student_list.size(); i++){
		if(uid == student_list[i].student->get_ID()){

			// Update student Grade
			return student_list[i].grade;
			
		}
	}
	return 0;
}

int Course::is_enrolled(string uid)
{
	for (int i = 0; i< (int)student_list.size(); i++)
	{
		if(student_list[i].student->get_ID() == uid)
		{
			return 1;
		}

	}
	return 0;
}
string Course::course_info(){

		// returns a string of course info in this format: 
		//Course ID: ENSF337
		//Start date: 5/5/2021
		//End date: 6/17/2021
		//Capacity: 70
		//Enrolled: 0
		//List of students:
		//        Student name    Grade
		
		string result = "\nCourse ID: " + Cid + "\n" 
		+ "Start date: " + start.date_string() + "\n" + "End date: "
		+ end.date_string() + "\n" + "Capacity: " + to_string(capacity) + "\n"
		+ "Enrolled: " + to_string(enrolled) + "\n" + "List of students:" + "\n" + "\tName\t\t\tGrade\n" + "-------------------------------------------------\n";
	
		string students;
		
		// add the student list of the course to the string 
		for(int i = 0; i < (int) student_list.size(); i++)
		{
			students+= "\t" + student_list[i].student->get_Fname() + " " + student_list[i].student->get_Lname() + "\t\t" + to_string(student_list[i].grade) + "\n";
		}
		return result + students;
}
