#pragma once
#include "Scheduler.h"
#include "../Core/LightGroup.h"
#include "../Core/SingleLight.h"
class FixedScheduler :
	public Scheduler
{
public:
	FixedScheduler(void);
	~FixedScheduler(void);
	void initial();

 
	LightGroup calculate(Road& r);
	void first_time_calculate();
	int find_green_time(Road& r);
	int cal_red_time(Road& r);
private:
	int constant_time_;

};

