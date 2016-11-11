//! @file
//! @brief Implementation of the Equipment class
//!
#include "Equipment.h"

//! default constructor
Equipment::Equipment() : Item()
{

}

//! parametrized constructor
//! @param nm : name of the Item
//! @param tp : Item's type (boots, belt, helmet, etc.)
//! @param nv : Item's vector of Enchants
Equipment::Equipment(string nm, itemType tp, vector<Enchant*> nv) : Item(nm, tp, nv)
{

}

//! copy constructor
//! @param orig : original equipment to be copied
Equipment::Equipment(const Equipment& orig) : Item(orig)
{

}

//! destructor
Equipment::~Equipment()
{

}

//! returns a pointer to a new, identical object
Equipment* Equipment::clone()
{
	return new Equipment(*this);
}


//! override for abstract print method in parent class. Deals with object slicing when printing contents of container
void Equipment::print()
{
	cout << Item::getName() << ", [" << Item::getType() << "]" << endl;

	for (int i = 0; i < Item::getEnch().size(); i++)
	{
		Item::getEnch()[i]->print();
	}
}

ostream& operator<<(ostream& op, Equipment it)
{
	op << it.getName() << ", [" << it.getType() << "] " << "derived" << endl;

	for (int i = 0; i < it.getEnch().size(); i++)
	{
		op << it.getEnch()[i];
	}

	return op;
}