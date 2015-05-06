#ifndef _SIMULATOR_H_
#define _SIMULATOR_H_
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "EmergencyRoom.h"

class Simulator{
private:
	int total_time, clock;
	EmergencyRoom *emergencyRoom;
	Nurse *nurse;
	Doctor *doctor;

public:
	std::vector<std::string> people;

	Simulator(){
		emergencyRoom = new EmergencyRoom();
		nurse = new Nurse();
		doctor = new Doctor();
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
			emergencyRoom->update(clock);
			nurse->update(clock);
			doctor->update(clock);
		}
	}

	void showStats(){

	}

friend class Nurse;
};




#endif