#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "EmergencyRoom.h"
#include "Random.h"

Random random;


class Simulator{
private:
	int total_time, clock;
	EmergencyRoom *emergencyRoom;
	Nurse *nurse;
	Doctor *doctor;

public:
	std::vector<std::string> people;

	Simulator(){
		//nurse = new Nurse();
		//doctor = new Doctor();
		fillVector();
		emergencyRoom = new EmergencyRoom(people);
	}

	void fillVector(){
		std::ifstream myfile("residents_273ville.txt");
		if (!myfile){
			std::cout << "Fail" << std::endl;
		}
		else{
			std::string str;
			while (std::getline(myfile, str)){
				people.push_back(str);
			}
			myfile.close();
		}
	}

	void runSimulation(){
		for (clock = 0; clock < total_time; clock++){
			(*emergencyRoom).update(clock);
		}
	}


	void enterData(){
		int doctorNum, nurseNum, arrivalRate;
		std::cout << "How many doctors work at this emergency room?\n";
		std::cin >> doctorNum;
		emergencyRoom->addDoctor(doctorNum);
		std::cout << "How many nurses work at this emergency room?\n";
		std::cin >> nurseNum;
		emergencyRoom->addNurse(nurseNum);
		std::cout << "What is the arrival rate of patients per hour?\n";
		std::cin >> arrivalRate;
		emergencyRoom->setArrivalRate(static_cast<double>(arrivalRate)/60);
		std::cout << "For how many hours will this simulation run?\n";
		std::cin >> total_time;
		total_time = total_time * 60;
	}


	void showStats(){
		std::cout << "\tFinal stats of Emergency Room: \n";
		std::cout << "Total time of simulation: " << total_time << std::endl;
		std::cout << "Number of patients served by nurses: " << emergencyRoom->nurseServed << std::endl;
		std::cout << "Number of patients served by doctor: " << emergencyRoom->doctorServed << std::endl;
		std::cout << "Total visit time: " << static_cast<double>(emergencyRoom->visitTime)/(emergencyRoom->nurseServed + emergencyRoom->doctorServed) << std::endl;
	}

};




#endif