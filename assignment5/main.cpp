#include <iostream>
#include <stdio.h>
#include "BufferFixedField.h"
#include "BufferDelimField.h"
#include "BufferFile.h"
#include "IndexCollection.h"
#include "SecondaryIndex.h"
#include "Record.h"
#include <map>
#include <string>

#define PATH_DATA_FILE "data.txt"
#define PATH_INDEX_PK "IndexPk.txt"
#define PATH_INDEX_SK "IndexSk.txt"
#define BUFFER_FIELD_SIZE_PK 32
#define BUFFER_FIELD_SIZE_SK 16


using namespace std;


void CreateIndexFileOfPrimaryKey(const string &path, Buffer &buffer, IndexCollection &indexFile) {
	BufferFile dataFile(buffer);
	dataFile.Open(PATH_DATA_FILE, ios::in);

	int fileOffset;
	while( (fileOffset = dataFile.Read()) >= 0 ) {
		Record record(0, "", "", "");
		if( ! record.Unpack(buffer) ) {
			cout << "error" << endl;
			break;
		}

		indexFile.Insert(record.PrimaryKey(), fileOffset);
	}

	dataFile.Close();

    
    BufferFixedField buffer2(2);
    buffer2.AddField(BUFFER_FIELD_SIZE_PK);
    buffer2.AddField(BUFFER_FIELD_SIZE_PK);
    
	BufferFile file(buffer2);
    file.Create(path, ios::out);
    
    map<string, int> indexList = indexFile.GetCollection();
    for( map<string, int>::iterator it = indexList.begin(); it != indexList.end(); ++it ) {
        buffer2.Clear();
        
        buffer2.Pack(it->first.c_str());

        string strFileOffset = to_string(it->second);
        buffer2.Pack(strFileOffset.c_str());
        
        file.Write();
    }
    
    file.Close();
}

void CreateIndexFileOfSecondaryKey(const string& path, Buffer& buffer, SecondaryIndex& secondaryIndex) {
	BufferFile dataFile(buffer);
	dataFile.Open(PATH_DATA_FILE, ios::in);

	int fileOffset;
	while( (fileOffset = dataFile.Read()) >= 0 ) {
		Record record(0, "", "", "");
		record.Unpack(buffer);
        
        secondaryIndex.Insert(record.PrimaryKey(), record.SecondaryKey());
	}

	dataFile.Close();


    BufferFixedField buffer2(2);
    buffer2.AddField(BUFFER_FIELD_SIZE_SK);
    buffer2.AddField(BUFFER_FIELD_SIZE_SK);
    
    BufferFile file(buffer2);
    file.Create(path, ios::out);
    
    map< string, vector<string> > indexList = secondaryIndex.GetKeyPairs();
    for( map<string, vector<string> >::iterator it = indexList.begin(); it != indexList.end(); ++it ) {
        buffer2.Clear();
        
        buffer2.Pack(it->first.c_str());
        
        const vector<string>& list = it->second;
        for( int i = 0; i < list.size(); i ++ ) {
            buffer2.Clear();
            buffer2.Pack(it->first.c_str());
            buffer2.Pack(list[i].c_str());
            file.Write();
        }
    }
    
    file.Close();
}

void SearchOnSecondary(const SecondaryIndex& secondaryIndex,
                       const string& composer,
                       Buffer& dataBuffer,
                       IndexCollection& indexCollectionPrimaryKey) {
    BufferFile dataFile(dataBuffer);
    dataFile.Open(PATH_DATA_FILE, ios::in);
    
    map<string, vector<string> > pairs = secondaryIndex.GetKeyPairs();
    for( map< string, vector<string> >::iterator it = pairs.begin(); it != pairs.end(); ++ it ) {
        if( it->first == composer ) {
            const vector<string>& pkList = it->second;
            
            for( int i = 0; i < pkList.size(); i ++ ) {
                const string& pk = pkList[i];
                int fileOffset = indexCollectionPrimaryKey.Search(pk);
                
                if( dataFile.Read(fileOffset) < 0 ) {
                    cout << "error" << endl;
                    continue;
                }
                
                Record record(0, "", "", "");
                record.Unpack(dataBuffer);
                cout << "fileOffset : " << fileOffset << endl << record << endl;
            }
        }
    }
    cout << endl;
    
    dataFile.Close();
}


void CreateTestData(const string &path, Buffer &buffer) {
    vector<Record> records;
    records.push_back( Record(2312, "LON", "Romeo and Juliet", "Prokofiev") );
    records.push_back( Record(3795, "ANG", "Symphony No.9", "Beethoven") ) ; // Beethoven!
    records.push_back( Record(23699, "WAR", "Touchstone", "Corea") );
    records.push_back( Record(18807, "DG", "Symphony No.9", "Beethoven") ) ; // Beethoven!
    records.push_back( Record(38358, "COL", "Nebraska", "Springsteen") );
    records.push_back( Record(31809, "COL", "Symphony No.9", "Beethoven") ) ; // Beethoven!
    records.push_back( Record(245, "FF", "Good News", "Sweet Honey in the Rock") );

	BufferFile file(buffer);
	file.Create(path, ios::out);

    for( int i = 0; i < records.size(); i ++ ) {
        const Record& record = records[i];
        record.Pack(buffer);
        int fileOffset = file.Write();
        cout << "Record" << i + 1 << " : " << fileOffset << endl;
    }

    file.Close();
}

void RunTest() {
	// get test data
	BufferDelimField buffer;

	CreateTestData(PATH_DATA_FILE, buffer);

	IndexCollection indexCollectionPrimaryKey;
    SecondaryIndex secondaryIndex;
	CreateIndexFileOfPrimaryKey(PATH_INDEX_PK, buffer, indexCollectionPrimaryKey);
    CreateIndexFileOfSecondaryKey(PATH_INDEX_SK, buffer, secondaryIndex);
    
    SearchOnSecondary(secondaryIndex, "Beethoven", buffer, indexCollectionPrimaryKey);
}

int main(int argc, char const *argv[])
{
	RunTest();
	return 0;
}