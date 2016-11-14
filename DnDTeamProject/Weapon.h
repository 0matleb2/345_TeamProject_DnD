//! @file
//! @brief Header file for Weapon class
//!
//! This class handles weapons. Weapons have all the same attributes that standard equipment does,
//! as well as a _subtype for weapon category, a dice object representing damage, and a value
//! representing it's _range. Besides that, it functions just as any other item.
#pragma once

#include "Item.h"

class Weapon : public Item {
public:

	Weapon();
	Weapon(std::string nm, ItemType tp, std::vector<Enchant*> nv, int rng, WeaponType st);
	Weapon(const Weapon& orig);
	~Weapon();

	int getRange();
	WeaponType getSubtype();

	void setRange(int);
	void setSubtype(WeaponType);

	Weapon* clone();
	void print();

private:

	int _range;
	WeaponType _subtype;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _range;
		ar & _subtype;
	}
};

