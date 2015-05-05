//
//  SecondaryIndex.h
//  file-processing5
//
//  Created by loki on 2015. 5. 5..
//  Copyright (c) 2015년 loki. All rights reserved.
//

#ifndef __file_processing5__SecondaryIndex__
#define __file_processing5__SecondaryIndex__

#include <string>
#include <map>
#include <vector>


class SecondaryIndex {
public:
    SecondaryIndex();
    virtual ~SecondaryIndex();
    
    void Insert(const std::string& pk, const std::string& secondKey);
    std::vector<std::string> Search(const std::string& secondKey);
    
    const std::map<std::string, std::vector<std::string> >& GetKeyPairs() const {
        return _keyMap;
    }
    
private:
    std::map< std::string, std::vector<std::string> > _keyMap;
};

#endif /* defined(__file_processing5__SecondaryIndex__) */
