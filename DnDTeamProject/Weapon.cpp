//! @file
//! @brief Implementation file for the Weapon class
//! 
#include "Weapon.h"

//! default constructor
Weapon::Weapon() : Item("Default", itemType::WEAPON, vector<Enchant*>()), range(0), subtype(weaponType::MELEE)
{

}

//! parametrized constructor
//! @param nm : name of weapon
//! @param tp : item type of weapon (always "weapon")
//! @param nv : weapon's vector of Enchants
//! @param rng : range of weapon
//! @param st : subtype of weapon (sword, bow, ...)
Weapon::Weapon(string nm, itemType tp, vector<Enchant*> nv, int rng, weaponType st) : Item(nm, tp, nv), range(rng), subtype(st)
{

}

//! copy constructor
//! @param orig : original weapon to be copied
Weapon::Weapon(const Weapon& orig) : Item(orig), subtype(orig.subtype), range(orig.range)
{

}

//! accessor for weapon range
int Weapon::getRange()
{
	return range;
}

//! accessor for weapon subtype
weaponType Weapon::getSubtype()
{
	return subtype;
}

//! mutator for weapon range
//! @param nr : new range of weapon
void Weapon::setRange(int nr)
{
	range = nr;
}

//! mutator for weapon type
//! @param nt : new subtype for weapon
void Weapon::setSubtype(weaponType nt)
{
	subtype = nt;
}

// returns a pointer to a newly-created identical object
Weapon* Weapon::clone()
{
	return new Weapon(*this);
}

//! print method for weapon
void Weapon::print()
{
	cout << Item::getName() << ", [" << Weapon::subtype << "], range: " << Weapon::getRange() << endl;

	for (int i = 0; i < Item::getEnch().size(); i++)
	{
		Item::getEnch()[i]->print();
	}
}

Weapon::~Weapon()
{

}