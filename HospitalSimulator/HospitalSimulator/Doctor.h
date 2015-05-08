#ifndef _DOCTOR_H_
#define _DOCTOR_H_
#include "Staff.h"


class Doctor : public Staff{
private:

public:
	Doctor() : Staff(){
		maxSeverity = 20;
		maxTime = 20;
		numServed = 0;
	}

	void treatPatient(int clock){
		numServed++;
		serviceTime = clock + random.nextInt(maxTime);
		//std::cout << "A doctor is treating a patient." << std::endl;
	}

	void update(int clock){

	}
};

#endif