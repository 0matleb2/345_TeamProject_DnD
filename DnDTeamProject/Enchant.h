//! @file
//! @brief Header file for Enchant class
//!
//! Enchant has a _type corresponding to a stat and a _value, provides a bonus to items based on these attributes.
#pragma once
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Enums.h"



//! class for implementation of an Enchant, or a stat bonus granted by an Item
class Enchant {

public:

	Enchant();
	Enchant(Stat t, int v);
	Enchant(const Enchant& orig);
	~Enchant();



	Stat getType();
	int getValue();

	void setType(Stat nt);
	void setValue(int nv);


	void print();
	friend std::ostream& operator<<(std::ostream& op, Enchant e);

private:

	Stat _type;
	int _value;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _type;
		ar & _value;
	}
};
