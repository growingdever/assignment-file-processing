#include "BufferFixedLength.h"

using namespace std;


BufferFixedLength::BufferFixedLength(int bufferSize) 
: Buffer(bufferSize) {

}

BufferFixedLength::~BufferFixedLength() {

}

static const string header("FixedLength");

int BufferFixedLength::ReadHeader(istream &ist) {
	if( Buffer::ReadHeader(ist) < 0 ) {
		return -1;
	}

	char str[MAX_LENGTH] = { 0, };
	ist.read(str, header.size());
	if( ! ist.good() ) {
		return -1;
	}

	int bufferSize;
	ist.read((char*)&bufferSize, sizeof(bufferSize));

	ChangeBufferSize(bufferSize);

	return ist.tellg();
}

int BufferFixedLength::WriteHeader(ostream &ost) {
	if( Buffer::WriteHeader(ost) < 0 ) {
		return -1;
	}

	ost.write(header.c_str(), header.size());

	if( ! ost.good() ) {
		return -1;
	}

	ost.write((char*)&_bufferSize, sizeof(_bufferSize));

	return ost.tellp();
}

int BufferFixedLength::Read(istream &ist) {
	int fileOffset = ist.tellg();
	ist.clear();
	Clear();

	ist.read(_buffer, _bufferSize);

	if( ! ist.good() ) {
		return -1;
	}

	return fileOffset;
}

int BufferFixedLength::Write(ostream &ost) {
	int fileOffset = ost.tellp();
	ost.write(_buffer, _bufferSize);
	if( ! ost.good() ) {
		return -1;
	}

	return fileOffset;
}