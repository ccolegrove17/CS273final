#include <iostream>
#include "EmergencyRoom.h"
#include "Simulator.h"
using namespace std;

int main(){
	Simulator hospital;
	hospital.runSimulation();
	//hospital.showStats();
	Doctor *Craig = new Doctor();
}