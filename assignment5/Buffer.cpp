#include "Buffer.h"

using namespace std;


Buffer::Buffer(int bufferSize)
: _bufferSize(bufferSize)
, _nextBufferOffset(0) {

}

Buffer::~Buffer() {

}

void Buffer::Clear() {
	memset(_buffer, 0, sizeof(_buffer));
	_nextBufferOffset = 0;
}

int Buffer::ChangeBufferSize(int bufferSize) {
    _bufferSize = bufferSize;
    
    return 1;
}


static const string header("Buffer");

int Buffer::ReadHeader(istream &ist) {
	char buffer[MAX_LENGTH] = { 0, };
	ist.seekg(0, ios::beg);
	ist.read(buffer, header.size());
	if( !ist.good() || ist.gcount() != header.size() ) {
		return -1;
	}

	return ist.tellg();
}

int Buffer::WriteHeader(ostream &ost) {
	ost.seekp(0, ios::beg);

	ost.write(header.c_str(), header.size());

	if( !ost.good() ) {
		return -1;
	}

	return ost.tellp();
}

int Buffer::DirectRead(istream &ist, int fileOffset) {
	Clear();

	ist.seekg(fileOffset);
	if( ! ist.good() || ! (ist.tellg() == fileOffset) ) {
		return -1;
	}

	return this->Read(ist);
}

int Buffer::DirectWrite(ostream &ost, int fileOffset) {
	ost.seekp(fileOffset);
	if( ! ost.good() || ! (ost.tellp() == fileOffset) ) {
		return -1;
	}

	return this->Write(ost);
}