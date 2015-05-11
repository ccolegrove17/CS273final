#ifndef _RECORD_H_
#define _RECORD_H_
#include <string>




class Record{
private:
	int severity;
	std::string name;
public:
	Record(int severity, std::string name){
		this->severity = severity;
		this->name = name;
	}

	bool operator<(const Record &other) const {
		if (severity < other.severity)
			return true;
		else
			return false;
	}

};



#endif