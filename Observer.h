#pragma once

class Subject;
class Observer
{
public:
	Observer(void);
	virtual ~Observer(void);
	virtual void update(Subject* changed_sub)=0;
};

