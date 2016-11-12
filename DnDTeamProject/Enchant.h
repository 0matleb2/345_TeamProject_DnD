//! @file
//! @brief Header file for Enchant class
//!
//! Enchant has a type corresponding to a stat and a value, provides a bonus to items based on these attributes.
#pragma once
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "Enums.h"



//! class for implementation of an Enchant, or a stat bonus granted by an Item
class Enchant {

public:

	Enchant();
	Enchant(Stats t, int v);
	Enchant(const Enchant& orig);
	~Enchant();

	void print();


	Stats getType();
	int getValue();

	void setType(Stats nt);
	void setValue(int nv);

	friend std::ostream& operator<<(std::ostream& op, Enchant e);

private:

	Stats type;
	int value;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & type;
		ar & value;
	}
};
