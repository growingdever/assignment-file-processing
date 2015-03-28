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


int CourseRegistration::InitBuffer (FixedFieldBuffer &buffer)
{
	int result;
	result = buffer.AddField(16);
	result = result && buffer.AddField(16);
	result = result && buffer.AddField(16);
	result = result && buffer.AddField(16);
	return result;
}

int CourseRegistration::InitBuffer (DelimFieldBuffer & Buffer) {
	return TRUE;
}

int CourseRegistration::InitBuffer (LengthFieldBuffer & Buffer) {
	return TRUE;
}

bool CourseRegistration::Pack(IOBuffer& buffer) {
	int numBytes;
	buffer.Clear ();

	string courseIDString = to_string(_courseID);
	string studentIDString = to_string(_studentID);
	string creditHourString = to_string(_creditHour);
	string gradeString = to_string(_grade);

	numBytes = buffer.Pack (courseIDString.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack (studentIDString.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack (creditHourString.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack (gradeString.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool CourseRegistration::Unpack(IOBuffer& buffer) {
	int numBytes;
	string idString, completedCreditHoursString;

	char *containerCourseID = new char[64];
	char *containerStudentID = new char[64];
	char *containerCreditHour = new char[64];
	char *containerGrade = new char[64];

	vector<char*> toRelease;
	toRelease.push_back(containerCourseID);
	toRelease.push_back(containerStudentID);
	toRelease.push_back(containerCreditHour);
	toRelease.push_back(containerGrade);

	numBytes = buffer.Unpack(containerCourseID);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}
	numBytes = buffer.Unpack(containerStudentID);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}
	numBytes = buffer.Unpack(containerCreditHour);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}
	numBytes = buffer.Unpack(containerGrade);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}

	_courseID = stoi(containerCourseID);
	_studentID = stoi(containerStudentID);
	_creditHour = stoi(containerCreditHour);
	_grade = stoi(containerGrade);

	release(toRelease);

	return true;
}