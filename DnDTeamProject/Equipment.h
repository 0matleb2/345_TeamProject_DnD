//! @file
//! @brief This class is meant to implement wearable items that are not weapons.
//!
//! I chose to separate weapons and wearable equipment,
//! as weapons wil have their own parameters and methods not shared by all equipment.
#ifndef Equipment_h
#define Equipment_h

#include "Item.h"

class Equipment : public Item
{
public:
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Item>(*this);

	}

	// default constructor
	Equipment();
	// parametrized constructor
	Equipment(string nm, itemType tp, vector<Enchant*> nv);
	// copy constructor
	Equipment(const Equipment& orig);
	//clone method
	Equipment* clone();

	// print method
	void print();
	// destructor
	~Equipment();

	friend ostream& operator<<(ostream& op, Equipment it);
};

#endif
