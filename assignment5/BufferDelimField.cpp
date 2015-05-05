//
//  BufferDelimField.cpp
//  file-processing5
//
//  Created by loki on 2015. 5. 4..
//  Copyright (c) 2015년 loki. All rights reserved.
//

#include "BufferDelimField.h"

using namespace std;


BufferDelimField::BufferDelimField(char delim, int maxBufferSize)
: BufferVariableLength(maxBufferSize)
, _delim(delim) {
    
}

BufferDelimField::~BufferDelimField() {
    
}

static const string header("VariableLength");

int BufferDelimField::ReadHeader(istream &ist) {
    if( BufferVariableLength::ReadHeader(ist) < 0 ) {
        return -1;
    }
    
    char str[MAX_LENGTH] = { 0, };
    ist.read(str, header.size());
    if( ! ist.good() ) {
        return -1;
    }
    
    ist.get(_delim);
    if( ! ist.good() ) {
        return -1;
    }
    
    return ist.tellg();
}

int BufferDelimField::WriteHeader(ostream &ost) {
    if( BufferVariableLength::WriteHeader(ost) < 0 ) {
        return -1;
    }
    
    ost.write(header.c_str(), header.size());
    if( ! ost.good() ) {
        return -1;
    }
    
    ost.put(_delim);
    if( ! ost.good() ) {
        return -1;
    }
    
    return ost.tellp();
}

int BufferDelimField::Pack(const void* field, int size) {
    size_t length;
    if( size == -1 ) {
        length = strlen((char*)field);
    } else {
        length = size;
    }
    
    int start = _nextBufferOffset;
    _nextBufferOffset += length + 1; // delim size
    
    memcpy(&_buffer[start], field, length);
    _buffer[start + length] = _delim;
    _bufferSize = _nextBufferOffset;
    
    return (int)length;
}

int BufferDelimField::Unpack(void* field, int maxBytes) {
    size_t length = -1;
    int start = _nextBufferOffset;
    for( int i = start; i < _bufferSize; i ++ ) {
        if( _buffer[i] == _delim ) {
            length = i - start;
            break;
        }
    }
    
    if( length == -1 ) {
        return -1;
    }
    
    _nextBufferOffset += length + 1;
    memcpy(field, &_buffer[start], length);
    ((char*)field)[length] = 0;
    
    return length;
}
