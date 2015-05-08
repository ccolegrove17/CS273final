#ifndef _NURSE_H_
#define _NURSE_H_
#include "Staff.h"

class Nurse : public Staff{
private:

public:
	Nurse() : Staff(){
		maxSeverity = 10;
		maxTime = 10;
		numServed = 0;
	}

	void treatPatient(int clock){
		numServed++;
		serviceTime = clock + random.nextInt(maxTime);
		//std::cout << "A nurse is treating a patient." << std::endl;
	}

	void update(int clock){
		
	}
};

#endif