//! @file
//! @brief Implementation of Item class
//!
#include "Item.h"


Item::Item() : _id(++_sNextId) {
}

Item::Item(std::string name) : _name(name), _id(++_sNextId){
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
	return getName();
}