#include "BufferFile.h"

using namespace std;


BufferFile::BufferFile(Buffer& buffer)
: _buffer(buffer) {

}

BufferFile::~BufferFile() {

}

int BufferFile::Open(const string& path, int mode) {
	_fs.open(path.c_str(), mode);
	if( _fs.fail() ) {
		return -1;
	}

	int headerSize = _buffer.ReadHeader(_fs);

	_fs.seekg(headerSize, ios::beg);
	_fs.seekp(headerSize, ios::beg);

	return _fs.good();
}

int BufferFile::Create(const string& path, int mode) {
	if( ! (mode & ios::out) ) {
		return -1;
	}

	_fs.open(path.c_str(), mode | ios::trunc);
	if( _fs.fail() ) {
		return -1;
	}

	int headerSize = _buffer.WriteHeader(_fs);

	_fs.seekg(headerSize, ios::beg);
	_fs.seekp(headerSize, ios::beg);

	return _fs.good();
}

void BufferFile::Close() {
	_fs.close();
}

int BufferFile::Read(int fileOffset) {
	if( fileOffset == -1 ) {
		return _buffer.Read(_fs);
	}

	return _buffer.DirectRead(_fs, fileOffset);
}

int BufferFile::Write(int fileOffset) {
	if( fileOffset == -1 ) {
		return _buffer.Write(_fs);
	}

	return _buffer.DirectWrite(_fs, fileOffset);
}