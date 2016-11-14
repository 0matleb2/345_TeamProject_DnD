//! @file
//! @brief Implementation file for the Weapon class
//! 
#include "Weapon.h"



Weapon::Weapon() : Item("Default", ItemType::WEAPON, std::vector<Enchant*>()), _range(0), _subtype(WeaponType::MELEE) {
}

//! parametrized constructor
//! @param nm : name of weapon
//! @param tp : item type of weapon (always "weapon")
//! @param nv : weapon's std::vector of Enchants
//! @param rng : _range of weapon
//! @param st : _subtype of weapon (sword, bow, ...)
Weapon::Weapon(std::string nm, ItemType tp, std::vector<Enchant*> nv, int rng, WeaponType st) : Item(nm, tp, nv), _range(rng), _subtype(st) {
}

Weapon::Weapon(const Weapon& orig) : Item(orig), _subtype(orig._subtype), _range(orig._range) {
}

Weapon::~Weapon() {
}


//Accessors
int Weapon::getRange() {
	return _range;
}

WeaponType Weapon::getSubtype() {
	return _subtype;
}


//Mutators
void Weapon::setRange(int nr) {
	_range = nr;
}

void Weapon::setSubtype(WeaponType nt) {
	_subtype = nt;
}



Weapon* Weapon::clone() {
	return new Weapon(*this);
}

void Weapon::print() {
	std::cout << Item::getName() << ", [" << Weapon::_subtype << "], _range: " << Weapon::getRange() << std::endl;
	for (int i = 0, n = getEnch().size(); i < n; ++i) {
		Item::getEnch()[i]->print();
	}
}
