#ifndef _DOCTOR_H_
#define _DOCTOR_H_
#include "Staff.h"


class Doctor : public Staff{
private:

public:
	Doctor(){
		maxSeverity = 20;
		maxTime = 20;
	}

	void treatPatient(){

	}

	void update(int clock){

	}
};

#endif