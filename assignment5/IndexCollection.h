#ifndef _INDEX_COLLECTION_H_
#define _INDEX_COLLECTION_H_

#include <map>
#include <string>

class IndexCollection {
public:
	IndexCollection();
	~IndexCollection();

	void Insert(const std::string& key, int fileOffset);
	void Remove(const std::string& key);
	int Search(const std::string& key);
    
    std::map<std::string, int>& GetCollection() {
        return _collection;
    }

private:
	std::map<std::string, int> _collection;
};

#endif