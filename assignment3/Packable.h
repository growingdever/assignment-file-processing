#ifndef _PACKABLE_H_
#define _PACKABLE_H_

#include "iobuffer.h"

class Packable {
public:
	virtual bool Pack(IOBuffer& buffer) = 0;
	virtual bool Unpack(IOBuffer& buffer) = 0;
};

#endif