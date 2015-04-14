#ifndef _PACKABLE_H_
#define _PACKABLE_H_

#include "iobuffer.h"

// pack, unpack을 하는 클래스들을 위한 인터페이스
class Packable {
public:
	virtual bool Pack(IOBuffer& buffer) = 0;
	virtual bool Unpack(IOBuffer& buffer) = 0;
};

#endif