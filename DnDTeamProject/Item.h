//! @file
//! @brief Header File for Item class
//!
//! This class handles items. Items have a _name, a _type, and a number of Enchants, implemented through a std::vector.
//! I chose to use std::string as it is suitable for a _name, and std::vector as it is an array of adjustable size that permits random access.
//! Class also has a method to check if the item in question has a legal Enchant. This class is not meant to be initialized
//! the Equipment and Weapon classes are meant to be concrete
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "Enums.h"
#include "Enchant.h"
#include <boost\serialization\vector.hpp>


//! class for the implementation of items
class Item {

public:

	Item();
	Item(std::string name, ItemType type, std::vector<Enchant*> nv);
	Item(const Item& orig);
	virtual ~Item();
	virtual Item* clone();

	std::string getName();
	ItemType getType();
	std::vector<Enchant*> getEnchants();


	void setName(std::string name);
	void setType(ItemType itemType);
	void addEnchant(Enchant* enchantType);
	void removeEnchant(Stat enchantType);

	bool validEnch(ItemType tgt__type, Stat tgt_stat);
	Enchant RandomEnch(int value);
	void rescale(int targetLvl);
	virtual void print();


	friend std::ostream& operator<<(std::ostream& op, Item it);

private:

	std::string _name;
	ItemType _type;
	std::vector<Enchant*> _enchants;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _name;
		ar & _type;
		ar & _enchants;
	}

};
