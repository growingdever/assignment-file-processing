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


template <class IOB>
void TestBufferStudent (IOB & buffer, const string& path)
{	
	int result;
	int recaddr1, recaddr2, recaddr3;

	BufferFile TestOut(buffer);
	result = TestOut.Open(path.c_str(), ios::out | ios::in);
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

	int delete_pk_id = 11;
	cout << "delete student id == " << delete_pk_id << endl;
	TestOut.Delete(3, delete_pk_id);

	TestOut.Close ();


	// test reading
	Student student(student1);
	student.SetName("Changed Name");

	BufferFile TestIn (buffer);
	TestIn.Open (path.c_str(), ios::in);
	TestIn.Read (recaddr3);
	student.Unpack (buffer);
	printf("First record(%d) : %s\n", recaddr3, student.Str().c_str());
	TestIn.Read (recaddr2);
	student.Unpack (buffer);
	printf("Second record(%d) : %s\n", recaddr2, student.Str().c_str());
	TestIn.Read (recaddr1);
	student.Unpack (buffer);
	printf("Third record(%d) : %s\n", recaddr1, student.Str().c_str());
	
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

	TestBufferStudent(buffer, "student_fixed_field_buffer.txt");
}

int main(int argc, char const *argv[])
{
	Student::ReadFromFile("students.txt", students);

	BufferTestStudent();
	return 0;
}