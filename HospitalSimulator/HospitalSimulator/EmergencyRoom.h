#ifndef _EMERGENCYROOM_H_
#define _EMERGENCYROOM_H_
#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include <queue>

class EmergencyRoom{
private:
	std::priority_queue<Patient> patients;
	std::queue<Nurse> nurses;
	std::queue<Doctor> doctors;
	int arrivalRate;

public:
	EmergencyRoom(){

	}

	//void update(int clock){
	//	if (/*if person arrives*/)
	//		/*put them into the priority queue of patients*/
	//}

	friend class Nurse;
	friend class Doctor;
};

#endif