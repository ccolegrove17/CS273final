#ifndef _EMERGENCYROOM_H_
#define _EMERGENCYROOM_H_
#include "Doctor.h"
#include "Nurse.h"
#include "Patient.h"
#include "Random.h"
#include <list>
#include <queue>
#include <set>
#include <iterator>
#include "Record.h"

extern Random random;

class EmergencyRoom{
private:
	int nurseServed, doctorServed, visitTime;
	std::priority_queue<Patient*> highPatients;
	std::priority_queue<Patient*> lowPatients;
	std::queue<Nurse*> nurses;
	std::queue<Doctor*> doctors;
	std::vector<std::string> people;
	std::list<Nurse*> nurseTreatment;
	std::list<Doctor*> doctorTreatment;
	double arrivalRate;
	std::set<Record> records;

public:
	EmergencyRoom(std::vector<std::string> people){
		this->people = people;
		nurseServed = 0;
		doctorServed = 0;
		visitTime = 0;
	}

	void setArrivalRate(double arrivalRate){
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
		std::cout << "\tClock tick: " << clock << std::endl;
		if (random.nextDouble() < arrivalRate)
		{
			Patient *p1 = new Patient(people[random.nextInt(1999)], clock);
			if (p1->getSeverity() > 10){
				std::cout << "A severely sick patient has arrived.\n";
				highPatients.push(p1);
				records.insert(Record(p1->getSeverity(), p1->getName()));
			}
			else{
				std::cout << "A lowly sick patient has arrived.\n";
				lowPatients.push(p1);
				records.insert(Record(p1->getSeverity(), p1->getName()));
			}
		}
		if (!highPatients.empty()){
			if (doctors.empty())
				std::cout << "There are no doctors to treat the " << highPatients.size() << " severely sick patients." << std::endl;
			while (!doctors.empty()){
				if (highPatients.empty())
					break;
				doctors.front()->treatPatient(clock);
				std::cout << "A doctor has left to treat a severely sick patient." << std::endl;
				visitTime += clock - highPatients.top()->arrivalTime;
				highPatients.pop();
				doctorTreatment.push_front(doctors.front());
				doctors.pop();
			}
		}
		if (!lowPatients.empty()){
			if (doctors.empty() && nurses.empty())
				std::cout << "There is no staff to treat the " << lowPatients.size() << " lowly sick patients." << std::endl;
			while (!nurses.empty()){
				if (lowPatients.empty())
					break;
				nurses.front()->treatPatient(clock);
				std::cout << "A nurse has left to treat a patient." << std::endl;
				visitTime += clock - lowPatients.top()->arrivalTime;
				lowPatients.pop();
				nurseTreatment.push_front(nurses.front());
				nurses.pop();
			}
			while (!doctors.empty()){
				if (lowPatients.empty())
					break;
				doctors.front()->treatPatient(clock);
				visitTime += (clock - lowPatients.top()->arrivalTime);
				lowPatients.pop();
				std::cout << "A doctor has left to treat a patient." << std::endl;
				doctorTreatment.push_front(doctors.front());
				doctors.pop();
			}
		}

		std::list<Nurse*>::iterator itN = nurseTreatment.begin();
		while (itN != nurseTreatment.end()){
			if (clock == (*itN)->serviceTime){
				nurses.push(*itN);
				visitTime += (*itN)->scaledServiceTime;
				std::cout << "The nurse has finished treatment." << std::endl;
				nurseServed++;
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
				visitTime += (*itD)->scaledServiceTime;
				doctorServed++;
				std::cout << "The doctor has finished treatment." << std::endl;
				doctorTreatment.erase(itD);
				itD = doctorTreatment.begin();//very inefficient workaround. TRY TO FIX
			}
			if (itD != doctorTreatment.end())//part of the bad workaround
				itD++;
		}

		std::cout << "\n\n";
	}


	friend class Simulator;
};

#endif