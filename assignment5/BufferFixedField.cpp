#include "BufferFixedField.h"

using namespace std;


BufferFixedField::BufferFixedField(int maxField, int bufferSize)
: BufferFixedLength(bufferSize)
, _maxNumOfField(maxField)
, _nextField(0) {
	ChangeBufferSize(0);
}

BufferFixedField::~BufferFixedField() {

}

static const string header("FixedField");

int BufferFixedField::ReadHeader(istream &ist) {
	if( BufferFixedLength::ReadHeader(ist) < 0 ) {
		return -1;
	}

	char str[MAX_LENGTH] = { 0, };
	ist.read(str, header.size());
	if( ! ist.good() ) {
		return -1;
	}

	int numOfField;
	ist.read((char*)&numOfField, sizeof(numOfField));
	_fieldSizes.clear();
	for( int i = 0; i < numOfField; i ++ ) {
		int fieldSize;
		ist.read((char*)&fieldSize, sizeof(fieldSize));
		_fieldSizes.push_back(fieldSize);
	}

	return ist.tellg();
}

int BufferFixedField::WriteHeader(ostream &ost) {
	if( BufferFixedLength::WriteHeader(ost) < 0 ) {
		return -1;
	}

	ost.write(header.c_str(), header.size());

	if( ! ost.good() ) {
		return -1;
	}

	int numOfField = _fieldSizes.size();
	ost.write((char*)&numOfField, sizeof(numOfField));
	for( int i = 0; i < numOfField; i ++ ) {
		int fieldSize = _fieldSizes[i];
		ost.write((char*)&fieldSize, sizeof(fieldSize));
	}

	return ost.tellp();
}

int BufferFixedField::Pack(const void* field, int size) {
	int fieldSize = _fieldSizes[_nextField];

	int start = _nextBufferOffset;
	memcpy(&_buffer[start], field, fieldSize);

	_nextBufferOffset += fieldSize;
	_nextField++;

	if( _nextField == _fieldSizes.size() ) {
		_nextBufferOffset = 0;
		_nextField = 0;
	}

	return fieldSize;
}

int BufferFixedField::Unpack(void* field, int maxbytes) {
	if( _nextField == _fieldSizes.size() ) {
		return -1;
	}

	int fieldSize = _fieldSizes[_nextField];

	memcpy(field, &_buffer[_nextBufferOffset], fieldSize);

	_nextBufferOffset += fieldSize;
	_nextField++;
	if( _nextField == _fieldSizes.size() ) {
		Clear();
        _nextField = 0;
	}

	return fieldSize;
}

int BufferFixedField::AddField(int fieldSize) {
	if( _fieldSizes.size() == _maxNumOfField ) {
		return -1;
	}

	_bufferSize += fieldSize;

	_fieldSizes.push_back(fieldSize);
	return fieldSize;
}
