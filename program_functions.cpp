#include "date.h"
#include "course.h"
#include "student.h"
#include "program_functions.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void wait_for_user() { // waits for user to press enter
	
	char ch;
	while(1) {
		
		cout << "\n<<<<<<<<<< Press Enter to continue >>>>>>>>>>>" << endl;
		ch = cin.get();
		if(ch == '\n'){// If the user presses enter, the program will move on, otherwise, it will wait.
			break;
		}
		else {
			buffer_cleaner();
		}
	}
}


int main_menu() // while(1) or while(true) creates an infinite loop so that the menu will continually display the options after every selection until the exit option is chosen.
{
	int i;
	while(1)
	{
		cout << "\t\t Main Menu\n" << endl;
		cout<<"Select the desired functionality by typing the corresponding number and hit enter" << endl;
		cout<<"1. Load students list file" << endl;
		cout<<"2. Load courses file" << endl;
		cout<<"3. Enroll from file" << endl;
		cout<<"4. Show course details" << endl;
		cout<<"5. Show student details" << endl;
		cout<<"6. Create course" << endl;
		cout<<"7. Add student to database" << endl;
		cout<<"8. Enroll student to a course" << endl;
		cout<<"9. Withdraw student from a course" << endl;
		cout<<"10. Update student grade" << endl;
		cout<<"11. Save changes" << endl;
		cout<<"12. Exit" << endl;
		
		cin >> i;
		buffer_cleaner();
		if(i>0 && i<13) { // if the user input is an integer between 0 and 13, it will return the value of i to the main function and the desired option will be executed.
							
			//system("clear");
			break;
		}
		else { // the user will be prompted for another input if an invalid value is given
			cout<<"invalid input";
		}
	}
	return i;
}

void buffer_cleaner() 
{

	
	char ch;
	cin.clear();
	do
	{
		ch = cin.get();
	}	
	while(ch!='\n' && ch!=EOF);
}

int load_coursefile(string filename, vector<Course*>& clist) // opens the desired file and extracts the course information from that file.
{
	ifstream file(filename);
	if(file.fail()){ // the file doesn't exist so the function can't run
		cout << "Error: Couldn't open file " << filename << endl;
		return 0;
	}
	string cid;
	int sy, sm, sd, ey, em, ed, cap;
	int i = 0;
	while (!file.eof()) // the file exists so the function can run
	{
		file >> cid >> sy >> sm >> sd >> ey >> em >> ed >> cap; // extracts the course information in the file in this order/format:
																// start year, month, day, and end year, month, day.
		if(find_course(cid, clist)) {
			continue;
		}
		Course* crse = new Course(cid,Date(sy,sm,sd), Date(ey,em,ed), cap);
		
		
		clist.push_back(crse);
		i++;
	}
	file.close();
	return i;
}

int load_studentfile(string filename, vector<Student> & slist)
{
	ifstream file(filename);
	if(file.fail()) { // the file doesn't exist so the function can't run
		cout << "Error: Couldn't open " << filename << endl;
		return 0;
	}
	string fname, lname, phone, id;
	int y, m, d;
	int i = 0;
	while (!file.eof()) // the file exists so the function can run
	{
		file >> id >> fname >> lname >> phone >> y >> m >> d; // extracts the course information in the file in this order/format:
		if(find_student(id, slist)) {						  // id, first name, last name, phone number, and the DOB shown as year, month, day.
			continue;
		}
		Student stdnt(fname, lname, phone, id, Date(y,m,d));
		
		slist.push_back(stdnt);
		i++;
	}
	file.close();
	return i;
}

Student* find_student(string id, vector<Student>& student_list) // see if the student exists in the file and returns a pointer to the student if it exists.
{
	Student* s1;
	for(int i = 0; i < (int) student_list.size(); i++) // uses a counter to go through the vector of students to find the desired one. The counter will not exceed the size of the vector.
	{
		if(id == student_list[i].get_ID()) // returns a pointer to the student object if it exists, otherwise will return NULL.
		{
			s1 = &student_list[i];
			return s1;
		}
	}
	
	return NULL; 
}

Course* find_course(string cid, vector<Course*>& course_list) // see if the course exists in the file and returns a pointer to the course if it exists.
{
	Course* c1;
	for(int i = 0; i < (int) course_list.size(); i++) // uses a counter to go through the vector of courses to find the desired one. The counter will not exceed the size of the vector.
	{
		if(cid == course_list[i]->get_cid()) // returns a pointer to the course object if it exists, otherwise will return NULL.
		{
			c1 = course_list[i];
			return c1;
		}
	}
	return NULL;
}

int enrollment_file(string filename, vector<Course*> & clist, vector<Student>& slist) // opens enrollment file and extracts information regarding a student's enrollment in a course.
{
	ifstream file(filename);

	if(file.fail()){ // if there is an error opening the file a message will be displayed. 
		cout<<"couldnt open file or it doesn't exist \n";
		return 0;
	}
	
	string line;
	string cls;
	string id;
	double grade;
	int num;
	int i = 0;
	int k = 0;
	Course* crs;
	Student* st;


	while(getline(file, line))
	{
		stringstream ls(line);
		ls >> id >> num;
		while(ls >> cls >> grade)
		{
			st = find_student(id, slist);
			crs = find_course(cls, clist);
			int j = crs->enroll(st);
			update_student_grade(id, cls, grade, slist, clist); 
			if(j==0){
				k++;
			}
			else if(j == -1){
				return -1;
			}
			
			
		}
		i++;
	}
	file.close();
	return i-k;
}
		
void show_course_details(string c,vector<Course*>& clist) // receives a user input of the desired course id and displays the information of the course object as a string. 
{
	Course* course = find_course(c, clist);
	if(course == NULL) { // if the course id doesn't exist in the vector of courses then a message will be displayed.
						 // otherwise the information will be displayed.
		cout << "Error: Course: " << c << " Not Found" << endl;
	} else {
		cout << course->course_info() << endl;
	}
}

void show_student_details(string s,vector<Student>& slist) // receives a user input of the desired student id and displays the information of the student object as a string.
{
	string result;
	for(int i = 0; i < (int) slist.size(); i++) // uses a counter to go through the vector of students to find the id that corresponds with the user input. The counter will not exceed the size of the vector.
	{
		if(s == slist[i].get_ID()) // if the student id that the user inputted is the same as the one that the counter found in the vector, the information corresponding to that id will be displayed.
		{
			result = slist[i].student_info();
			break;
		}
	}
	cout<<result<<endl;
}	

Course* create_course() // creates a new course object by prompting the user to input the required information fields.
{
	string id;
	int sy, sm, sd, ey, em, ed, cap;
	cout<<"What is the name of your class: ";
	cin>>id;
	cout << endl;
	cout<<"What year does it start: ";
	cin>>sy;
	cout << endl;
	cout<<"What month does it start: ";
	cin>>sm;
	cout<<endl;
	cout<<"What day does it start: ";
	cin>>sd;
	cout<<endl;
	cout<<"What year does it end: ";
	cin>>ey;
	cout<<endl;
	cout<<"What month does it end: ";
	cin>>em;
	cout<<endl;
	cout<<"What day does it end: ";
	cin>>ed;
	cout<<endl;
	cout<<"What is the max capacity: ";
	cin>>cap;
	cout<<endl;
	buffer_cleaner();
	Date s(sy,sm,sd);
	Date e(ey,em,ed);
	
	
	Course* cr = new Course(id,s,e,cap);
	
	return cr;
}

Student create_student() // creates a new student object by prompting the user to input the required information fields.
{
	string fname,lname,phone,id;
	int y,m,d;
	cout<<"What is the students first name: ";
	cin>>fname;
	cout<<endl;
	cout<<"What is the students last name: ";
	cin>>lname;
	cout<<endl;
	cout<<"What is the students phone number: ";
	cin>>phone;
	cout<<endl;
	cout<<"What is the students birthday (mm dd yy ex: 08 31 1999): ";
	cin>>m>>d>>y;
	cout<<endl;
	cout<<"What is the students ID number: ";
	cin>>id;
	cout<<endl;
	buffer_cleaner();
	Date b(y,m,d);
	Student st(fname, lname, phone, id, b);
	return st;
}

void enroll_to_course(string sid, string cid,vector<Student>& slist,vector<Course*>& clist) // function that enrolls a student with a user-inputted id into a course with a user-inputted id
{
	for(int i =0; i < (int) slist.size();i++) // uses a counter to find the desired student id in the student file. 
	{
		if(sid == slist[i].get_ID())
		{
			for(int j = 0; j < (int) clist.size(); j++) // uses a counter to find the desired course id in the course file. 
			{
				if(clist[j]->get_cid() == cid) 
				{
					clist[j]->enroll(&slist[i]); // the student is added to the course's list of enrolled students
					return;
				}
			}
		}
	}
}

int remove_student_from_course(string student_id, string course_id, vector<Course*>& courseVector) { // function receives a user-inputted student and course id so that the student can be removed from that course.
	Course* course = find_course(course_id, courseVector);
	if(course == NULL) { // displays message when course id cannot be found in the course list
						 // otherwise will use the withdraw function to remove the student from the course.
		cout << "Error: Unable to find course with ID: " << course_id;
		return -1;
	}
	
	return course->withdraw(student_id);
}

int update_student_grade(string sid,string cid, double g, vector<Student>& slist, vector<Course*>& clist) // function receives a user-inputted student and course id, and a grade so that the student's grade in that course can be updated. 
{
	Course* crs = find_course(cid, clist);
	Student* stdt = find_student(sid, slist);
	if(crs == NULL || stdt == NULL) // return NULL if either the course id or the student id doesn't exist.
	{
		return -1;
	}
	crs->update_grade(sid, g); // use update_grade function to update the student's grade in that course
	return 1;
}

int save_changes(string courses, string students, string enroll, vector<Student> &slist, vector<Course*> &clist) // function will save the changes to the student, course, or enroll list made during the program run to the respective text files.
{
	saveStudentFile(students, slist);
	saveCourseFile(courses, clist);
	saveEnrollFile(enroll, slist, clist);
	return 1;
}

int saveStudentFile(string studentFile, vector<Student> &slist) // function that saves the changes made to the student text file.
{
	ofstream file(studentFile);
	if(file.fail()){
		cout << "Couldnt open file or it doesn't exist" << endl;
		return -1;
	}

	for(int i = 0; i < (int) slist.size(); i++){ // loops through the vector to find and save the changes to the correct student
		file<<slist.at(i).get_ID()<<" "<<slist.at(i).get_Fname()<<" "<<slist.at(i).get_Lname()<<" "<<slist.at(i).get_phone()<<" "<<slist.at(i).get_Date().get_year()<<" "<<slist.at(i).get_Date().get_month()<<" "<<slist.at(i).get_Date().get_day()<<endl;
	}

	file.close();
	return 1;
}

int saveCourseFile(string courseFile, vector<Course*>& clist) // function that saves the changes made to the course text file.
{
	ofstream file(courseFile);
	if(file.fail()) {
		cout << "Couldnt open file or it doesn't exist" << endl;
		return -1;
	}
	
	for(int i = 0; i < (int) clist.size(); i++) { // loops through the vector to find and save the changes to the correct course
		file << clist.at(i)->get_cid() << " " << clist.at(i)->get_start_date().get_year() << " " << clist.at(i)->get_start_date().get_month() << " " << clist.at(i)->get_start_date().get_day() << " " << clist.at(i)->get_end_date().get_year() << " " << clist.at(i)->get_end_date().get_month() << " " << clist.at(i)->get_end_date().get_day() << " " << clist.at(i)->get_capacity() << "\n";
	}

	file.close();
	cout << "saved courses" << endl;
	return 1;

}

int saveEnrollFile(string enrollFile, vector<Student> &slist, vector<Course*> &clist) { // function that saves the changes made to the enroll text file
	ofstream file(enrollFile);
	if(file.fail()) {
		cout << "Couldnt open file or it doesn't exist" << endl;
		return -1;
	}

	for(int i = 0; i < (int)slist.size(); i++) { // save the changes to the number of courses that a student is in
		
		if((int) slist.at(i).get_course_records().size() == 0) { // removes a student from the enroll.txt if they aren't enrolled in any courses
			continue;
		}
		file << slist.at(i).get_ID() << " " << slist.at(i).get_course_records().size() << " ";
		for(int j = 0; j < (int)slist.at(i).get_course_records().size(); j++) { // save the changes to the number of students in a course
			file << slist.at(i).get_course_records().at(j).reg_course->get_cid() << " " << slist.at(i).get_course_records().at(j).grade << " ";
		}
		file << "\n";
	}
	file.close();
	return 1;
}
