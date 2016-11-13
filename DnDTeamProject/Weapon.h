//! @file
//! @brief Header file for Weapon class
//!
//! This class handles weapons. Weapons have all the same attributes that standard equipment does,
//! as well as a subtype for weapon category, a dice object representing damage, and a value
//! representing it's range. Besides that, it functions just as any other item.
#pragma once

#include "Item.h"

class Weapon : public Item
{
public:
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Item>(*this);
		ar & range;
		ar & subtype;
	}

	// default constructor
	Weapon();
	// parametrized constructor
	Weapon(std::string nm, ItemType tp, std::vector<Enchant*> nv, int rng, WeaponType st);

	Weapon(const Weapon& orig);

	// get weapon's range
	int getRange();
	// get weapon's subtype
	WeaponType getSubtype();
	// set weapon's range
	void setRange(int nr);
	// set weapon's subtype
	void setSubtype(WeaponType nt);
	// overriden print method

	Weapon* clone();

	void print();
	// destructor
	~Weapon();
private:
	//Dice object for weapon damage, implement later
	//Dice damage

	//Range of weapon, set as int for now
	int range;

	//type of weapon: sword, bow, etc...
	WeaponType subtype;
};

