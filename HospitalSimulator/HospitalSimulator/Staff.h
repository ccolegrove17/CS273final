#ifndef _STAFF_H_
#define _STAFF_H_
#include <queue>

class Staff{
public:
	int maxSeverity, maxTime;
	virtual void treatPatient() = 0;
	virtual void update(int clock) = 0;
};

#endif