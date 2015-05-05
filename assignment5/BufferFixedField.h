#ifndef _BUFFER_FIXED_FIELD_H_
#define _BUFFER_FIXED_FIELD_H_

#include "BufferFixedLength.h"
#include <vector>


class BufferFixedField : public BufferFixedLength {
public:
	BufferFixedField(int maxField, int bufferSize = MAX_LENGTH);
	virtual ~BufferFixedField();

	virtual int ReadHeader(std::istream &ist);
	virtual int WriteHeader(std::ostream &ost);

	int Pack(const void* field, int size = -1);
	int Unpack(void* field, int maxbytes = -1);

	int AddField(int fieldSize);

private:
	std::vector<int> _fieldSizes;
	int _nextField;
	int _maxNumOfField;
};

#endif