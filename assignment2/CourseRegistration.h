#ifndef _COURSE_REGISTRATION_H_
#define _COURSE_REGISTRATION_H_

#include <string>
#include <vector>

using namespace std;


class CourseRegistration 
{
public:
	CourseRegistration(int courseID,
		int studentID,
		int creditHour,
		int grade);
	~CourseRegistration();

	static void ReadFromFile(string path, vector<CourseRegistration>& ret);
	static CourseRegistration CreateFromData(string str);
	static CourseRegistration CreateFromInput();
	string Export();


private:
	int _courseID;
	int _studentID;
	int _creditHour;
	int _grade; // 0 : A, 1 : B, ..., 4 : E(anyway ;)), 5 : F
};

#endif