#ifndef __MACRO_H_
#define __MACRO_H_

#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> GetTokensFromString(std::string input, std::string delimiter);

// template이라서 헤더 파일에 함수 정의까지 함께 한다.
// vector 안의 배열들을 편하게 release 하기 위해 만든 함수
template <class T>
void release(std::vector<T> toRelease) {
	for( int i = 0; i < toRelease.size(); i ++ ) {
		delete[] toRelease[i];
	}

	toRelease.clear();
}

#endif