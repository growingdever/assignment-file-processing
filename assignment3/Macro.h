#ifndef __MACRO_H_
#define __MACRO_H_

#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> GetTokensFromString(std::string input, std::string delimiter);

template <class T>
void release(std::vector<T> toRelease) {
	for( int i = 0; i < toRelease.size(); i ++ ) {
		delete[] toRelease[i];
	}

	toRelease.clear();
}

#endif