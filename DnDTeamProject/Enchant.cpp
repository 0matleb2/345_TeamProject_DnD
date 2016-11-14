//! @file
//! @brief Implementation for the Enchant class
//!
#include <iostream>
#include "Enchant.h"


Enchant::Enchant() : _type(Stats::STR), _value(0) {
}

Enchant::Enchant(Stats t, int v) : _type(t), _value(v) {
}

Enchant::Enchant(const Enchant& orig) : _type(orig._type), _value(orig._value) {
}

Enchant::~Enchant() {
}


//Accessors
Stats Enchant::getType() {
	return _type;
}

int Enchant::getValue() {
	return _value;
}


//Mutators
void Enchant::setType(Stats nt) {
	_type = nt;
}

void Enchant::setValue(int nv) {
	_value = nv;
}



void Enchant::print() {
	std::cout << "Enchantment Type: " << _type << ", Value: +" << _value << std::endl;
}

std::ostream& operator<<(std::ostream& op, Enchant e) {
	op << "Enchantment Type: " << e.getType() << ", Value: +" << e.getValue() << std::endl;
	return op;
}