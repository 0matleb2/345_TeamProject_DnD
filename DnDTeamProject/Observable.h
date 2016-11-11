#pragma once

#include <vector>
#include "Observer.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost\serialization\vector.hpp>



using namespace std;

//forward declaration
class Observer;

class Observable {
	public:
		Observable();
		virtual ~Observable();
		virtual void attach(Observer* o);
		virtual void detach(Observer* o);
		virtual void notify();

		friend class boost::serialization::access;

		template<class Archive> void serialize(Archive & ar, const unsigned int version)
		{
			ar & views;
		}

	private:
		vector<Observer*> views;
};

