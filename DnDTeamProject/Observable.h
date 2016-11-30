#pragma once
#include <vector>

#include "Observer.h"

class Observable {

	public:

		Observable();
		~Observable();

		void attach(Observer* observer);
		void detach(Observer* observer);
		void notify();


	private:
		std::vector<Observer*> _views;

	
};

