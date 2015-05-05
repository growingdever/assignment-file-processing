#include "Record.h"
#include <sstream>

using namespace std;

Record::Record(int id, const std::string& label, const std::string& title, const std::string& composer)
: _id(id)
, _label(label)
, _title(title)
, _composer(composer) {

}

Record::~Record() {

}

int Record::InitBuffer (BufferFixedField &buffer)
{
	int result;
	result = buffer.AddField(16);
	result = result && buffer.AddField(16);
	result = result && buffer.AddField(32);
	result = result && buffer.AddField(32);
	return result;
}

int Record::GetLengthForFixedFieldBuffer() {
	return 16 + 16 + 32 + 32;
}

string Record::PrimaryKey() {
	ostringstream ss;
	ss << _label << _id;

	return ss.str();
}

string Record::SecondaryKey() {
	ostringstream ss;
	ss << _composer;

	return ss.str();
}

bool Record::Pack(Buffer& buffer) const {
    buffer.Clear();
    
	if( buffer.Pack(to_string(_id).c_str()) < 0 ) {
		return false;
	}

	if( buffer.Pack(_label.c_str()) < 0 ) {
		return false;
	}

	if( buffer.Pack(_title.c_str()) < 0 ) {
		return false;
	}

	if( buffer.Pack(_composer.c_str()) < 0 ) {
		return false;
	}

	return true;
}

bool Record::Unpack(Buffer& buffer) {
	char str1[64];
	char str2[64];
	char str3[64];
	char str4[64];

	if( buffer.Unpack(str1) < 0 ) {
		return false;
	}
	if( buffer.Unpack(str2) < 0 ) {
		return false;
	}
	if( buffer.Unpack(str3) < 0 ) {
		return false;
	}
	if( buffer.Unpack(str4) < 0 ) {
		return false;
	}

	_id = atoi(str1);
	_label = string(str2);
	_title = string(str3);
	_composer = string(str4);

	return true;
}