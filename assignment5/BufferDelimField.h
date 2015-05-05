#ifndef _BUFFER_DELIM_FIELX_H_
#define _BUFFER_DELIM_FIELX_H_

#include "BufferVariableLength.h"


class BufferDelimField : public BufferVariableLength {
public:
    BufferDelimField(char Delim = '|', int maxBufferSize = MAX_LENGTH);
    virtual ~BufferDelimField();
    
    virtual int ReadHeader(std::istream &ist);
    virtual int WriteHeader(std::ostream &ost);
    
    virtual int Pack(const void*, int size = -1);
    virtual int Unpack(void* field, int maxBytes = -1);
    
private:
    char _delim;
};

#endif
