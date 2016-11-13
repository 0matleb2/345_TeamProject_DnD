#pragma once

#include <vector>
#include "Observer.h"



class Observable {

	public:

		Observable();
		virtual ~Observable();

		virtual void attach(Observer* o);
		virtual void detach(Observer* o);
		virtual void notify();

	private:

		std::vector<Observer*> _views;

};

