#include <iostream>
#include <fstream>
#include "Student.h"
#include "CourseRegistration.h"
#include "iobuffer.h"
#include "varlen.h"
#include "delim.h"
#include "fixfld.h"
#include "fixlen.h"


using namespace std;


Student student1(10, "juhong", "kimhae", "2013.03.02", 19);
CourseRegistration course1(10, 11, 12, 13);


template <class IOB>
void TestBufferCourseRegistration (IOB & buffer, const string path)
{
	int result;
	int recaddr1;

	ofstream TestOut (path, ios::out);
	course1.Pack (buffer);
	recaddr1 = buffer.Write (TestOut);
	cout << "write at " << recaddr1 << endl;
	// 다 썼으니 닫기
	TestOut.close ();


	// test reading
	CourseRegistration course(0, 0, 0, 0);

	// file stream 생성
	ifstream TestIn (path, ios::in);
	buffer.DRead (TestIn, recaddr1);
	course.Unpack (buffer);
	cout << course.Export() << endl;
}

void BufferTestCourseRegistration() {
	// test 1 : FiexFieldBuffer
	FixedFieldBuffer buffer1(8);
	CourseRegistration::InitBuffer(buffer1);
	TestBufferCourseRegistration(buffer1, "course_fixed_field_buffer.txt");

	// test 2 : LengthFieldBuffer
	LengthFieldBuffer buffer2;
	CourseRegistration::InitBuffer(buffer2);
	TestBufferCourseRegistration(buffer2, "course_length_field_buffer.txt");

	// test 3 : DelimFieldBuffer
	DelimFieldBuffer::SetDefaultDelim('|');
	DelimFieldBuffer buffer3;
	CourseRegistration::InitBuffer(buffer3);
	TestBufferCourseRegistration(buffer3, "course_delim_field_buffer.txt");
}


template <class IOB>
void TestBufferStudent (IOB & buffer, const string path)
{
	int result;
	int recaddr1;

	// file stream 생성
	ofstream TestOut (path, ios::out);
	student1.Pack (buffer);
	recaddr1 = buffer.Write (TestOut);
	cout << "write at " << recaddr1 << endl;
	// 다 썼으니 닫기
	TestOut.close ();


	// test reading
	Student student(student1);
	student.SetName("Changed Name");

	// file stream 생성
	ifstream TestIn (path, ios::in);
	buffer.DRead (TestIn, recaddr1);
	student.Unpack (buffer);
	cout << student.Export() << endl;
}

void BufferTestStudent() {
	// test 1 : FiexFieldBuffer
	FixedFieldBuffer buffer1(8);
	Student::InitBuffer(buffer1);
	TestBufferStudent(buffer1, "student_fixed_field_buffer.txt");

	// test 2 : LengthFieldBuffer
	LengthFieldBuffer buffer2;
	Student::InitBuffer(buffer2);
	TestBufferStudent(buffer2, "student_length_field_buffer.txt");

	// test 3 : DelimFieldBuffer
	DelimFieldBuffer::SetDefaultDelim('|');
	DelimFieldBuffer buffer3;
	Student::InitBuffer(buffer3);
	TestBufferStudent(buffer3, "student_delim_field_buffer.txt");
}

int main(int argc, char const *argv[])
{
	vector<Student> students;
	Student::ReadFromFile("students.txt", students);
	vector<CourseRegistration> courses;
	CourseRegistration::ReadFromFile("courses.txt", courses);

	// Test 돌려보자
	BufferTestStudent();
	BufferTestCourseRegistration();

	return 0;
}