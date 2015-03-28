#include "Student.h"
#include "macro.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <vector>


Student::Student(int id, 
	string name, 
	string address, 
	string firstEnrollmentDate,
	int completedCreditHours)
: _id(id)
, _name(name)
, _address(address)
, _dateOfFirstEnrollment(firstEnrollmentDate)
, _completedCreditHours(completedCreditHours)
{

}

Student::~Student()
{
	
}

Student& Student::operator=(const Student& rhs)
{
	this->_id = rhs._id;
	this->_name = rhs._name;
	this->_address = rhs._address;
	this->_dateOfFirstEnrollment = rhs._dateOfFirstEnrollment;
	this->_completedCreditHours = rhs._completedCreditHours;

	return *this;
}

void Student::ReadFromFile(string path, vector<Student>& ret)
{
	ifstream ifs(path);
	if( ! ifs.is_open() ) {
		return;
	}

	string line;
	while( !ifs.eof() ) {
		ifs >> line;
		ret.push_back(Student::CreateFromData(line));
	}
}

Student Student::CreateFromData(string str)
{
	vector<string> tokens = GetTokensFromString(str, "/");
	int id = stoi(tokens[0]);
	string name = tokens[1];
	string address = tokens[2];
	string date = tokens[3];
	int creditHours = stoi(tokens[4]);

	Student ret(id, name, address, date, creditHours);
	return ret;
}

Student Student::CreateFromInput()
{
	int id, creditHours;
	string name, address, date;

	cout << "Create student data from input" << endl;

	cout << "id : ";
	cin >> id;

	cout << "name : ";
	cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 
	getline(cin, name);

	cout << "address : ";
	getline(cin, address);

	cout << "first enrollment date : ";
	getline(cin, date);

	cout << "completed credit hour : ";
	cin >> creditHours;

	Student student(id, name, address, date, creditHours);
	return student;
}

string Student::Export()
{
	ostringstream ss;
	ss << _id << "/"
		<< _name << "/"
		<< _address << "/"
		<< _dateOfFirstEnrollment << "/"
		<< _completedCreditHours;
	return ss.str();
}


int Student::InitBuffer (FixedFieldBuffer &buffer)
{
	int result;
	result = buffer.AddField(16);
	result = result && buffer.AddField(16);
	result = result && buffer.AddField(32);
	result = result && buffer.AddField(16);
	result = result && buffer.AddField(16);
	return result;
}

int Student::InitBuffer (DelimFieldBuffer & Buffer) {
	return TRUE;
}

int Student::InitBuffer (LengthFieldBuffer & Buffer) {
	return TRUE;
}

bool Student::Pack(IOBuffer& buffer) {
	int numBytes;
	buffer.Clear ();

	string idString = to_string(_id);
	string completedCreditHoursString = to_string(_completedCreditHours);

	numBytes = buffer.Pack (idString.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack (_name.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack (_address.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack (_dateOfFirstEnrollment.c_str());
	if (numBytes == -1) return false;
	numBytes = buffer.Pack (completedCreditHoursString.c_str());
	if (numBytes == -1) return false;

	return true;
}

bool Student::Unpack(IOBuffer& buffer) {
	int numBytes;
	string idString, completedCreditHoursString;

	char *containerID = new char[64];
	char *containerName = new char[64];
	char *containerAddress = new char[64];
	char *containerEnrollment = new char[64];
	char *containerCredit = new char[64];

	vector<char*> toRelease;
	toRelease.push_back(containerID);
	toRelease.push_back(containerName);
	toRelease.push_back(containerAddress);
	toRelease.push_back(containerEnrollment);
	toRelease.push_back(containerCredit);

	numBytes = buffer.Unpack(containerID);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}
	numBytes = buffer.Unpack(containerName);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}
	numBytes = buffer.Unpack(containerAddress);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}
	numBytes = buffer.Unpack(containerEnrollment);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}
	numBytes = buffer.Unpack(containerCredit);
	if (numBytes == -1) {
		release(toRelease);
		return false;
	}

	_id = atoi(containerID);
	_name = string(containerName);
	_address = string(containerAddress);
	_dateOfFirstEnrollment = string(containerEnrollment);
	_completedCreditHours = atoi(containerCredit);

	release(toRelease);

	return true;
}