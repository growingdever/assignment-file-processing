#include "Student.h"
#include "macro.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>


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