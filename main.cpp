#include "date.h"
#include "course.h"
#include "student.h"
#include "program_functions.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])
{

	if (argc!=3){
		cout << "Only two files can be passed";
		exit(1);
	}
	string courses = "courses.txt";
	string students = "students.txt";

	system("clear");
	vector<Student> studentVector;
	vector<Course*> courseVector;
	
	cout << "Student Registration System: V1.0" << endl;
	cout << "Release date: June 15, 2021\n" << endl;

	wait_for_user();
	system("clear");

	if(argv[1] == courses) // if the second input from the terminal is "courses.txt" this will execute.
	{
		int a = load_coursefile(argv[1], courseVector);
		int b = load_studentfile(argv[2], studentVector);
		cout << b << "  students loaded from students file." << endl;
		cout << a << "  courses loaded from courses file." << endl;
		
	}
	else{ // if the first if statement isn't true, then the second input must be "students.txt".
		int a = load_coursefile(argv[2], courseVector);
		int b = load_studentfile(argv[1], studentVector);
		cout << b << "  students loaded from students file." << endl;
		cout << a << "  courses loaded from courses file." << endl;
	}

	wait_for_user();
	system("clear");
	
	cout << "\n";
	
	while(1) { // the while(1) is an infinite loop, it will keep executing this until a break statement.
		int i = main_menu();
		system("clear");
		if(i == 1) { // i == 1 is option 1
			cout<<"1. Load students list file\n" << endl;
			string str;
			cout<<"Enter text file name: ";
			cin>>str;
			buffer_cleaner(); // flush the input stream buffer after cin to clear any leftovers.
			int a = load_studentfile(str, studentVector); // this calls the load_studentfile function, returns the amount of students loaded from file
			if(a >= 0) {
				cout << a << "  students loaded from students file." << endl;
			} 
			else{
				cout<<"Couldn't open file."<<endl;
			}
		}
		else if(i == 2) { // i == 2 is option 2
			cout<<"2. Load courses file\n" << endl;
			cout<<"Enter text file name: ";
			string str;
			cin>> str;
			buffer_cleaner();
			int b = load_coursefile(str, courseVector); // this calls the load_coursefile function, returns the amount of courses loaded from file.
			if(b >= 0) {
				cout << b << "  courses loaded from courses file." << endl;
			}
			else{
				cout<<"Couldn't open file."<<endl;
			}

		}
		else if(i == 3) { // i == 3 is option 3
			cout<<"3. Enroll from file\n" << endl;
			int a = enrollment_file("enroll.txt" , courseVector, studentVector); // this calls the enrollment_file function, returns the number of students enrolled
			if(a == -1){
				cout<<"0 new students were enrolled"<<endl;
			}
			else if (a > 0){
				cout<<a<<" students were enrolled."<<endl;
			} else{
				cout << "0 new students were enrolled" << endl;
			}
			
		}
		else if(i == 4) {  // i == 4 is option 4
			string crse;
			cout<<"4. Show course details\n\nCourse name: ";
			cin>>crse;
			buffer_cleaner();
			show_course_details(crse, courseVector); // we pass the course name and the courseVector to show_course_details to display details about the course.
	 	}
		else if(i == 5) { // i == 5 is option 5
			string id;
			cout<<"5. Show student details\n\nStudent ID: ";
			cin>>id;
			buffer_cleaner();
			show_student_details(id, studentVector); // we pass the student id and the student vector to show_student_details to display details about the student.
		}
		else if(i == 6) { // i == 6 is option 6
			cout<<"6. Create course\n"<<endl;
			Course* crs = create_course(); // creates a new course object called crs, calls the create_course function asking for name, date, etc.
			courseVector.push_back(crs); // puts the new course object in the courseVector. push_back places crs in the current postion in the vector.
		}
		else if(i == 7) { // i == 7 is option 7
			cout<<"7. Add student to database\n"<<endl;
			Student std = create_student(); // creates a new student object called std, calls the create_student function asking for name, birthday, etc.
			studentVector.push_back(std); // puts the new student object in the studentVector. push-backs places std in the current position in the vector.

		}
		else if(i == 8) { // i == 8 is option 8
			string id, cid; // creates these strings to add a student(id) to a class(cid).
			cout<<"8. Enroll student to a course\n"<<endl; 
			cout<<"Enter Student ID: ";
			cin>>id;
			buffer_cleaner();
			cout<<"Enter course ID: ";
			cin>>cid;
			buffer_cleaner();
			enroll_to_course(id,cid,studentVector,courseVector); // passes id and cid to enroll_to_course and puts them in studentVector & courseVector.
		}
		else if(i == 9) { // i == 9 is option 9
			string course_id, student_id; // creates these strings to remove a student(student_id) to a class(course_id)
			cout<<"9. Withdraw student from a course\n"<<endl;
			cout << "Withdraw student from a course\n" << endl;
			cout << "Provide the following information to withdraw student from a course: " << endl;
			cout << "Course ID: ";
			cin >> course_id;
			buffer_cleaner();
			cout << "Student ID: ";
			cin >> student_id;
			buffer_cleaner();
			cout << "\n";
			// calls the remove_from_course function, passing the student id and the course name.
			if(remove_student_from_course(student_id, course_id, courseVector) != -1) { 
				cout << "Student with ID: " << student_id << " successfully removed from " << course_id<<endl;
			} 
		}
		else if(i == 10) { // i == 10 is option 10
			double g;
			string sid, cid; // initializes these variables which will be asked by the user
			cout<<"10. Update student grade\n"<<endl;
			cout<<"Enter Student ID: ";
			cin>>sid;
			buffer_cleaner();
			cout<<"Enter Course ID: ";
			cin>>cid;
			buffer_cleaner();
			cout<<"Enter Grade: ";
			cin>>g;
			buffer_cleaner();
			update_student_grade(sid,cid,g,studentVector,courseVector); //  upgrade the student grade
		}
		else if(i == 11) { 
			cout<<"11. Save changes\n" << endl;
			save_changes("courses.txt", "students.txt", "enroll.txt", studentVector, courseVector);
			cout << "Succesfully saved changes";
		}
		else if(i == 12) {
			cout<<"12. Exit\n" << endl;
			cout<<"Now exiting program."<<endl;
			break;
		}
		else {
			cout << "Unknown Input\n" << endl;
		}
		
		wait_for_user();
		system("clear");
	}
	
	for(int i = 0; i < (int) courseVector.size(); i++) {
		delete courseVector[i];
	}
	exit(0);
}
