#ifndef _BUFFER_FIEXED_LENGTH_H_
#define _BUFFER_FIEXED_LENGTH_H_

#include "Buffer.h"


class BufferFixedLength : public Buffer {
public:
	BufferFixedLength(int bufferSize = MAX_LENGTH);
	virtual ~BufferFixedLength();

	virtual int ReadHeader(std::istream &ist);
	virtual int WriteHeader(std::ostream &ost);

	virtual int Read(std::istream &ist);
	virtual int Write(std::ostream &ost);
};

#endif