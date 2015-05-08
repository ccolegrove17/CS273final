#include <iostream>
#include "EmergencyRoom.h"
#include "Simulator.h"
using namespace std;

int main(){
	Simulator hospital;
	hospital.enterData();
	hospital.runSimulation();
	//hospital.showStats();
}