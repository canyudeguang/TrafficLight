#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"

Subject::Subject(void):p_observer_(NULL)
{
	p_observer_ = new ObserverContainer();
}


Subject::~Subject(void)
{
	if (p_observer_!=NULL) 
		delete p_observer_;
}

void Subject::Attach( Observer* obs )
{
	if (std::find(p_observer_->begin(),p_observer_->end(),obs) != p_observer_->end()) {
		return;
	}
	p_observer_->push_back(obs);
}

void Subject::Detach( Observer* obs )
{
// 	auto obs_iter = std::find(p_observer_->begin(),p_observer_->end(),obs);
// 	if (obs_iter != p_observer_->end()) {
// 		p_observer_->erase(obs_iter);
// 	}
	p_observer_->remove(obs);

}

void Subject::Notify()
{
	for (auto& obs : *p_observer_) {
		obs->update(this);
	}
}
