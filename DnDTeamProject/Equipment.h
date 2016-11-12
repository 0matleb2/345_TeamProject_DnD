//! @file
//! @brief This class is meant to implement wearable items that are not weapons.
//!
//! I chose to separate weapons and wearable equipment,
//! as weapons wil have their own parameters and methods not shared by all equipment.
#pragma once

#include "Item.h"

class Equipment : public Item {

public:

	Equipment();
	Equipment(std::string nm, ItemType tp, std::vector<Enchant*> nv);
	Equipment(const Equipment& orig);
	~Equipment();

	Equipment* clone();
	void print();
	
	friend std::ostream& operator<<(std::ostream& op, Equipment it);

private:

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
	}

};

