#ifndef _BUFFER_FILE_H_
#define _BUFFER_FILE_H_

#include <fstream>
#include <string>
#include "Buffer.h"


class BufferFile {
public:
	BufferFile(Buffer& buffer);
	~BufferFile();

	int Open(const std::string& path, int mode);
	int Create(const std::string& path, int mode);
	void Close();
	int Read(int fileOffset = -1);
	int Write(int fileOffset = -1);

private:
	Buffer& _buffer;
	std::fstream _fs;
};

#endif