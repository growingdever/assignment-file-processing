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
	int recaddr1, recaddr2, recaddr3, recaddr4, recaddr5;

	BufferFile TestOut(buffer);
	result = TestOut.Create(path.c_str(), ios::out | ios::in);
	if ( ! result ) {
		cout << "Failed to open file " << path << endl;
		return;
	}
	
	// 일단 다 파일에 추가해놓고
	student1.Pack (buffer);
	recaddr1 = TestOut.Write ();
	printf("write student1 at %d\n", recaddr1);
	student2.Pack (buffer);
	recaddr2 = TestOut.Write ();
	printf("write student2 at %d\n", recaddr2);
	student3.Pack (buffer);
	recaddr3 = TestOut.Write ();
	printf("write student3 at %d\n", recaddr3);
	student4.Pack (buffer);
	recaddr4 = TestOut.Write ();
	printf("write student4 at %d\n", recaddr4);

	// 두번째, 세번째 레코드 지워놓고
	delete_student(TestOut, 11);
	delete_student(TestOut, 12);

	// 학생 추가를 Append로 하면 마지막으로 지운 세번째 레코드에 추가되고
	student2.Pack(buffer);
	recaddr5 = TestOut.Append();
	printf("write student2 at %d\n", recaddr5);

	// 또 학생 추가를 Append로 하면 두번째 레코드에 추가되고
	student3.Pack(buffer);
	recaddr5 = TestOut.Append();
	printf("write student3 at %d\n", recaddr5);

	// 또 학생 추가를 Append로 하면 파일의 끝에 추가된다.
	student2.Pack(buffer);
	recaddr5 = TestOut.Append();
	printf("write student2 at %d\n", recaddr5);

	TestOut.Close ();


	// test reading
	students.clear();
	Student student(student1);
	student.SetName("Changed Name");

	BufferFile TestIn (buffer);
	TestIn.Open (path.c_str(), ios::out | ios::in);

	// 첫 번째 레코드는 정상적으로 읽히고
	TestIn.Read (recaddr1);
	student.Unpack (buffer);
	print_student(student);

	// 두 번째 레코드는 아까 Append로 student3가 들어갔고
	TestIn.Read (recaddr2);
	student.Unpack (buffer);
	print_student(student);

	// 세 번째 레코드는 아까 Append로 student2가 들어갔고
	TestIn.Read (recaddr3);
	student.Unpack (buffer);
	print_student(student);

	// 네 번째 레코드는 정상적으로 읽히고
	TestIn.Read (recaddr4);
	student.Unpack (buffer);
	print_student(student);

	// 다섯 번째 레코드도 아까 새로 추가했으니 정상적으로 읽힌다
	TestIn.Read (recaddr5);
	student.Unpack (buffer);
	print_student(student);
}

void BufferTestStudent() {
	FixedFieldBuffer buffer(6);
	Student::InitBuffer(buffer);

	// 학생 삭제하는 메소드에서 쓰려고 배열에 넣어둠
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