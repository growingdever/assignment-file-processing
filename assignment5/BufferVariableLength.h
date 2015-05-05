#ifndef _BUFFER_VARIABLE_LENGTH_
#define _BUFFER_VARIABLE_LENGTH_

#include "Buffer.h"

#include <iostream>


class BufferVariableLength : public Buffer {
public:
    BufferVariableLength(int bufferSize = MAX_LENGTH);
    virtual ~BufferVariableLength();
    
    virtual int ReadHeader(std::istream &ist);
    virtual int WriteHeader(std::ostream &ost);
    
    virtual int Read(std::istream &ist);
    virtual int Write(std::ostream &ost);
    
};

#endif
