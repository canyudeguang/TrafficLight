#pragma once
#include <list>

class Observer;

typedef std::list<Observer*> ObserverContainer;
class Subject
{
public:
	Subject(void);
	virtual ~Subject(void);

	virtual void Attach(Observer* obs);
	virtual void Detach(Observer* obs);
	virtual void Notify();

private:
	ObserverContainer *p_observer_;
};

