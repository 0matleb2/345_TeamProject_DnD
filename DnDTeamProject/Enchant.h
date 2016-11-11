//! @file
//! @brief Header file for Enchant class
//!
//! Enchant has a type corresponding to a stat and a value, provides a bonus to items based on these attributes.
#ifndef Enchant_h
#define Enchant_h

#include <iostream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "Enums.h"

using namespace std;

//! class for implementation of an Enchant, or a stat bonus granted by an Item
class Enchant
{
public:
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar & type;
		ar & value;
	}

	// Default Constructor
	Enchant();
	// Parametrized COnstructor
	Enchant(stats t, int v);
	// Copy constructor
	Enchant(const Enchant& orig);

	//prints out information
	void print();

	// Accessor for Type
	stats getType();
	// Accessor for Value
	int getValue();
	// Mutator for Type
	void setType(stats nt);
	// Mutator for Value
	void setValue(int nv);
	// Destructor
	~Enchant();

	// overloaded output operator
	friend ostream& operator<<(ostream& op, Enchant e);

private:
	stats type;
	int value;
};

#endif