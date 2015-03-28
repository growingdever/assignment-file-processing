#include "CourseRegistration.h"
#include "macro.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>


CourseRegistration::CourseRegistration(int courseID,
	int studentID,
	int creditHour,
	int grade)
: _courseID(courseID)
, _studentID(studentID)
, _creditHour(creditHour)
, _grade(grade)
{

}

CourseRegistration::~CourseRegistration()
{

}

void CourseRegistration::ReadFromFile(string path, vector<CourseRegistration>& ret)
{
	ifstream ifs(path);
	if( ! ifs.is_open() ) {
		return;
	}

	string line;
	while( !ifs.eof() ) {
		ifs >> line;
		ret.push_back(CourseRegistration::CreateFromData(line));
	}
}

CourseRegistration CourseRegistration::CreateFromData(string str)
{
	vector<string> tokens = GetTokensFromString(str, "/");
	int courseID = stoi(tokens[0]);
	int studentID = stoi(tokens[1]);
	int creditHours = stoi(tokens[2]);
	int grade = stoi(tokens[3]);
	
	CourseRegistration ret(courseID, studentID, creditHours, grade);
	return ret;
}

CourseRegistration CourseRegistration::CreateFromInput()
{
	int courseID, studentID, creditHours, grade;

	cout << "Create course registration data from input" << endl;

	cout << "course id : ";
	cin >> courseID;

	cout << "student id : ";
	cin >> studentID;

	cout << "credit hour : ";
	cin >> creditHours;

	cout << "grade(0:A, 1:B, ..., 5:F) : ";
	cin >> grade;

	CourseRegistration course(courseID, studentID, creditHours, grade);
	return course;
}

string CourseRegistration::Export()
{
	ostringstream ss;
	ss << _courseID << "/"
		<< _studentID << "/"
		<< _creditHour << "/"
		<< _grade;
	return ss.str();
}