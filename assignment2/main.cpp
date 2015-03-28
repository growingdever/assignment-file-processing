#include <iostream>
#include <fstream>
#include "Student.h"
#include "CourseRegistration.h"

using namespace std;


int main(int argc, char const *argv[])
{
	Student student1(10, "juhong", "kimhae", "2013.03.02", 19);
	Student student2 = Student::CreateFromData("20/jung/busan/2013.03.02/38");
	cout << student1.Export() << endl;
	cout << student2.Export() << endl;
	student2 = student1;
	cout << student2.Export() << endl;

	CourseRegistration course1(10, 11, 12, 13);
	CourseRegistration course2 = CourseRegistration::CreateFromData("20/21/22/23");
	cout << course1.Export() << endl;
	cout << course2.Export() << endl;


	vector<Student> students;
	Student::ReadFromFile("students.txt", students);

	vector<CourseRegistration> courses;
	CourseRegistration::ReadFromFile("courses.txt", courses);

	// change some data
	for( int i = 0; i < students.size(); i ++ ) {
		if( i%2 == 0 ) {
			students[i].IncreaseCreditHours(10);
		}
	}
	students[0].SetName("New Named!");

	Student student3 = Student::CreateFromInput();
	students.push_back(student3);
	cout << student3.Export() << endl;

	CourseRegistration course3 = CourseRegistration::CreateFromInput();
	cout << course3.Export() << endl;
	courses.push_back(course3);

	ofstream ofs_students("students2.txt");
	if( ofs_students.is_open() ) {
		for( int i = 0; i < students.size(); i ++ ) {
			ofs_students << students[i].Export() << endl;
		}
	}

	ofstream ofs_courses("courses2.txt");
	if( ofs_courses.is_open() ) {
		for( int i = 0; i < courses.size(); i ++ ) {
			ofs_courses << courses[i].Export() << endl;
		}
	}

	return 0;
}