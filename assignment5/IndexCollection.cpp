#include "IndexCollection.h"

using namespace std;


IndexCollection::IndexCollection() {

}

IndexCollection::~IndexCollection() {

}

void IndexCollection::Insert(const string& key, int fileOffset) {
	_collection[key] = fileOffset;
}

void IndexCollection::Remove(const string& key) {
	_collection.erase( _collection.find(key) );
}

int IndexCollection::Search(const string& key) {
	return _collection[key];
}