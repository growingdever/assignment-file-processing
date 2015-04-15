#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Student.h"
#include "fixfld.h"
#include "buffile.h"


using namespace std;


vector<Student> students;
Student student1(10, "jung", "kimhae", "2013.03.02", 19);
Student student2(11, "ju", "seoul", "2013.03.02", 38);
Student student3(12, "hong", "city1234", "2013.03.02", 57);
Student student4(13, "growingdever", "city5678", "2013.03.02", 57);


void print_student(const Student& student) {
	printf("record : %s\n", student.Str().c_str());
}

template <class BufferFile>
void delete_student(BufferFile& bufferFile, int target_pk_id) {
	cout << "delete student id : " << target_pk_id << endl;
	bufferFile.Delete(students.size(), target_pk_id);
}


template <class IOB>
void TestBufferStudent (IOB & buffer, const string& path)
{	
	int result;
	int recaddr1, recaddr2, recaddr3, recaddr4;

	BufferFile TestOut(buffer);
	result = TestOut.Create(path.c_str(), ios::out | ios::in);
	if ( ! result ) {
		cout << "Failed to open file " << path << endl;
		return;
	}
	
	student1.Pack (buffer);
	recaddr1 = TestOut.Write ();
	cout << "write at " << recaddr1 << endl;

	student2.Pack (buffer);
	recaddr2 = TestOut.Write ();
	cout << "write at " << recaddr2 << endl;

	student3.Pack (buffer);
	recaddr3 = TestOut.Write ();
	cout << "write at " << recaddr3 << endl;

	student4.Pack (buffer);
	recaddr4 = TestOut.Write ();
	cout << "write at " << recaddr4 << endl;

	delete_student(TestOut, 11);
	delete_student(TestOut, 12);

	TestOut.Close ();


	// test reading
	students.clear();
	Student student(student1);
	student.SetName("Changed Name");

	BufferFile TestIn (buffer);
	TestIn.Open (path.c_str(), ios::out | ios::in);

	TestIn.Read (recaddr1);
	student.Unpack (buffer);
	print_student(student);

	TestIn.Read (recaddr2);
	student.Unpack (buffer);
	print_student(student);

	TestIn.Read (recaddr3);
	student.Unpack (buffer);
	print_student(student);

	TestIn.Read (recaddr4);
	student.Unpack (buffer);
	print_student(student);

	result = TestIn.Read(recaddr3 * 2);
	if (result!= -1) {
		cout << "Read past end of file! Error." << endl;
	} else {
		cout << "Read past end of file failed! Correct." << endl;
	}
}

void BufferTestStudent() {
	FixedFieldBuffer buffer(6);
	Student::InitBuffer(buffer);

	students.push_back(student1);
	students.push_back(student2);
	students.push_back(student3);
	students.push_back(student3);

	TestBufferStudent(buffer, "student_fixed_field_buffer.txt");
}

int main(int argc, char const *argv[])
{
	BufferTestStudent();
	return 0;
}