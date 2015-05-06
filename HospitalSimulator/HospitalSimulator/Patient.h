#ifndef _PATIENT_H_
#define _PATIENT_H_
#include <ctime>
#include <cstdlib>
#include <string>

class Patient{
private:
	int severity;
	std::string name;

public:
	Patient(std::string name){
		this->name = name;
		severity = RandomSeverity();
	}

	std::string getName(){
		return name;
	}

	int getSeverity(){
		return severity;
	}

	int RandomSeverity(){
		srand(unsigned int(std::time(NULL)));
		int prob = rand() % 10;
		if (prob <= 6)
			return rand() % 10 + 1;
		else if (prob <= 8)
			return rand() % 5 + 11;
		else
			return rand() % 5 + 16;
	}
};

#endif