//! @file
//! @brief Implementation of the Equipment class
//!
#include "Equipment.h"

//! default constructor
Equipment::Equipment() : Item() {
}

//! parametrized constructor
//! @param nm : name of the Item
//! @param tp : Item's type (boots, belt, helmet, etc.)
//! @param nv : Item's std::vector of Enchants
Equipment::Equipment(std::string nm, ItemType tp, std::vector<Enchant*> nv) : Item(nm, tp, nv) {
}

//! copy constructor
//! @param orig : original equipment to be copied
Equipment::Equipment(const Equipment& orig) : Item(orig) {
}

//! destructor
Equipment::~Equipment() {
}

//! returns a pointer to a new, identical object
Equipment* Equipment::clone() {
	return &Equipment(*this);
}

//! override for abstract print method in parent class. Deals with object slistd::cing when printing contents of container
void Equipment::print() {
	std::cout << Item::getName() << ", [" << Item::getType() << "]" << std::endl;
	for (int i = 0; i < Item::getEnch().size(); i++)
	{
		Item::getEnch()[i]->print();
	}
}

std::ostream& operator<<(std::ostream& op, Equipment it) {
	op << it.getName() << ", [" << it.getType() << "] " << "derived" << std::endl;
	for (int i = 0; i < it.getEnch().size(); i++) {
		op << it.getEnch()[i];
	}
	return op;
}