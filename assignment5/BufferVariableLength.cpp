#include "BufferVariableLength.h"

using namespace std;


BufferVariableLength::BufferVariableLength(int bufferSize)
: Buffer(bufferSize) {
    
}

BufferVariableLength::~BufferVariableLength() {
    
}

static const string header("VariableLength");

int BufferVariableLength::ReadHeader(istream &ist) {
    if( Buffer::ReadHeader(ist) < 0 ) {
        return -1;
    }
    
    char str[MAX_LENGTH] = { 0, };
    ist.read(str, header.size());
    if( ! ist.good() ) {
        return -1;
    }
    
    return ist.tellg();
}

int BufferVariableLength::WriteHeader(ostream &ost) {
    if( Buffer::WriteHeader(ost) < 0 ) {
        return -1;
    }
    
    ost.write(header.c_str(), header.size());
    
    if( ! ost.good() ) {
        return -1;
    }
    
    return ost.tellp();
}

int BufferVariableLength::Read(istream &ist) {
    int fileOffset = ist.tellg();
    ist.clear();
    Clear();
    
    int nextReadSize;
    ist.read((char*)&nextReadSize, sizeof(nextReadSize));
    
    _bufferSize = nextReadSize;
    ist.read(_buffer, nextReadSize);
    
    if( ! ist.good() ) {
        return -1;
    }
    
    return fileOffset;
}

int BufferVariableLength::Write(ostream &ost) {
    int fileOffset = ost.tellp();
    ost.write((char*)&_bufferSize, sizeof(_bufferSize));
    ost.write(_buffer, _bufferSize);
    if( ! ost.good() ) {
        return -1;
    }
    
    return fileOffset;
}
