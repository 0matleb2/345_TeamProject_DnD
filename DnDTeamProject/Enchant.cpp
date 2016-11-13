//! @file
//! @brief Implementation for the Enchant class
//!
#include <iostream>
#include "Enchant.h"


//! default constructor
Enchant::Enchant() : type(Stats::STR), value(0) {
}

//! constructor receives type of stat as an enum and value as an int
//! @param type : type of stat affected
//! @param value : bonus value
Enchant::Enchant(Stats t, int v) : type(t), value(v) {
}

//! copy constructor
//! @param orig : original enchant to be copied
Enchant::Enchant(const Enchant& orig) : type(orig.type), value(orig.value) {
}

//! destructor
Enchant::~Enchant() {
}

//prints out information
void Enchant::print() {
	std::cout << "Enchantment Type: " << type << ", Value: +" << value << std::endl;
}

//! accessor for stat affected by Enchant
//! @return : type of stat of Enchant
Stats Enchant::getType() {
	return type;
}

//! accessor for bonus value of Enchant
//! @return : value of bonus
int Enchant::getValue() {
	return value;
}

//! mutator for type
//! @param nt : new stat type to set
void Enchant::setType(Stats nt) {
	type = nt;
}

//! mutator for bonus value
//! @param nv : new value for Enchant
void Enchant::setValue(int nv) {
	value = nv;
}



//! overload for output operator
std::ostream& operator<<(std::ostream& op, Enchant e)
{
	op << "Enchantment Type: " << e.getType() << ", Value: +" << e.getValue() << std::endl;

	return op;
}