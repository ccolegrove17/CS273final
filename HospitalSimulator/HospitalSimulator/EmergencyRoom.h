#ifndef _EMERGENCYROOM_H_
#define _EMERGENCYROOM_H_
#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include <queue>

class EmergencyRoom{
private:
	std::priority_queue<Patient*> patients;
	std::queue<Nurse*> nurses;
	std::queue<Doctor*> doctors;
	std::vector<std::string> people;
	int arrivalRate;

public:
	EmergencyRoom(std::vector<std::string> people){
		this->people = people;
	}

	void update(int clock){
		nurses.push(new Nurse());
		doctors.push(new Doctor());
		patients.push(new Patient(people[10]));
	//	if (/*if person arrives*/)
	//		/*put them into the priority queue of patients*/
		if (!patients.empty()){
			if (patients.top()->getSeverity() <= 10 && !nurses.empty()){
				nurses.front()->treatPatient();
				nurses.pop();
			}
			else if (!doctors.empty()){
				doctors.front()->treatPatient();
				doctors.pop();
			}
			else
				std::cout << "No doctors or nurses free" << std::endl;
		}
	}

	friend class Nurse;
	friend class Doctor;
};

#endif