//
//  SecondaryIndex.cpp
//  file-processing5
//
//  Created by loki on 2015. 5. 5..
//  Copyright (c) 2015년 loki. All rights reserved.
//

#include "SecondaryIndex.h"

using namespace std;


SecondaryIndex::SecondaryIndex() {
    
}

SecondaryIndex::~SecondaryIndex() {
    
}

void SecondaryIndex::Insert(const std::string &pk, const std::string &secondKey) {
    _keyMap[secondKey].push_back(pk);
}

vector<string> SecondaryIndex::Search(const std::string &secondKey) {
    map<string, vector<string> >::iterator it = _keyMap.find(secondKey);
    if( it != _keyMap.end() ) {
        return it->second;
    }
    
    // not found key
    return vector<string>();
}