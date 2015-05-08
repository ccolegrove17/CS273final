#ifndef _EMERGENCYROOM_H_
#define _EMERGENCYROOM_H_
#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include "Random.h"
#include <list>
#include <queue>
#include <iterator>

extern Random random;

class EmergencyRoom{
private:
	std::priority_queue<Patient*> patients;
	std::queue<Nurse*> nurses;
	std::queue<Doctor*> doctors;
	std::vector<std::string> people;
	std::list<Nurse*> nurseTreatment;
	std::list<Doctor*> doctorTreatment;
	double arrivalRate;

public:
	EmergencyRoom(std::vector<std::string> people){
		this->people = people;
	}

	void setArrivalRate(int arrivalRate){
		this->arrivalRate = arrivalRate;
	}

	void addDoctor(int number){
		for (int i = 0; i < number; i++){
			doctors.push(new Doctor());
		}
	}

	void addNurse(int number){
		for (int i = 0; i < number; i++){
			nurses.push(new Nurse());
		}
	}

	void update(int clock){
		if (random.nextDouble() < arrivalRate)
				patients.push(new Patient(people[random.nextInt(2000)]));
		if (!patients.empty()){
			if (patients.top()->getSeverity() <= 10 && !nurses.empty()){
				nurses.front()->treatPatient(clock);
				patients.pop();
				nurseTreatment.push_front(nurses.front());
				nurses.pop();
			}
			else if (!doctors.empty()){
				doctors.front()->treatPatient(clock);
				patients.pop();
				doctorTreatment.push_front(doctors.front());
				doctors.pop();
			}
			else
				std::cout << "No doctors or nurses free" << std::endl;
		}

		std::list<Nurse*>::iterator itN = nurseTreatment.begin();
		while (itN != nurseTreatment.end()){
			if (clock == (*itN)->serviceTime){
				nurses.push(*itN);
				nurseTreatment.erase(itN);
				itN = nurseTreatment.begin();//very inefficient workaround. TRY TO FIX
			}
			if (itN != nurseTreatment.end())//part of the bad workaround
				itN++;
		}
		std::list<Doctor*>::iterator itD = doctorTreatment.begin();
		while (itD != doctorTreatment.end()){

			if (clock == (*itD)->serviceTime){
				doctors.push(*itD);
				doctorTreatment.erase(itD);
				itD = doctorTreatment.begin();//very inefficient workaround. TRY TO FIX
			}
			if (itD != doctorTreatment.end())//part of the bad workaround
				itD++;
		}


	}
};

#endif