#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <fstream>
#include <iostream>
#include <string>

#define MAX_LENGTH 1024


class Buffer {
public:
	Buffer(int bufferSize = MAX_LENGTH);
	virtual ~Buffer();

	virtual void Clear();
    virtual int ChangeBufferSize(int bufferSize);

	virtual int ReadHeader(std::istream &ist);
	virtual int WriteHeader(std::ostream &ost);

	int DirectRead(std::istream &ist, int fileOffset);
	virtual int Read(std::istream &ist) = 0;
	int DirectWrite(std::ostream &ost, int fileOffset);
	virtual int Write(std::ostream &ost) = 0;

	virtual int Pack(const void* field, int size = -1) = 0;
	virtual int Unpack(void* field, int maxbytes = -1) = 0;

protected:
	char _buffer[MAX_LENGTH];
	int _bufferSize;
	int _nextBufferOffset;
};

#endif