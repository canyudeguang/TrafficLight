#pragma once
#include "scheduler.h"
class LessWaitTimeScheduler :
	public Scheduler
{
public:
	LessWaitTimeScheduler(void);
	~LessWaitTimeScheduler(void);
};

