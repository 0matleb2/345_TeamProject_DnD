//Observer class, abstract

#pragma once
#include "Observable.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <boost\serialization\vector.hpp>

//forward declaration
class Observable;

class Observer {
	public:
		Observer() {};
		virtual ~Observer() {};
		virtual void update() = 0;

		friend class boost::serialization::access;

		template<class Archive> void serialize(Archive & ar, const unsigned int version)
		{}

};