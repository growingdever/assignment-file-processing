#ifndef _RECORD_H_
#define _RECORD_H_

#include "Buffer.h"
#include "BufferFixedField.h"
#include <string>


class Record {
public:
	Record(int id, const std::string& label, const std::string& title, const std::string& composer);
	~Record();

	static int InitBuffer(BufferFixedField &);
	static int GetLengthForFixedFieldBuffer();

	std::string PrimaryKey();
	std::string SecondaryKey();

    bool Pack(Buffer& buffer) const;
	bool Unpack(Buffer& buffer);
    
    friend std::ostream& operator<<(std::ostream& ost, const Record& record) {
        ost << record._id << " " << record._label << " " << record._title << " " << record._composer;
        return ost;
    }

private:
	int _id;
	std::string _label;
	std::string _title;
	std::string _composer;
};

#endif