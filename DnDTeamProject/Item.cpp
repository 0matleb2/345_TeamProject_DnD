#include "Item.h"


Item::Item() : _id(++_sNextId), _name("") {
}

Item::Item(std::string name) : _id(++_sNextId), _name(name)  {
}

Item::~Item() {
}


int Item::_sNextId = 0;


//Accessors
std::string Item::getName() {
	return _name;
}



//Mutators
void Item::setName(std::string name) {
	_name = name;
}



std::string Item::toString() {
	std::string s;
	s += "Name: " + getName();
	return getName();
}