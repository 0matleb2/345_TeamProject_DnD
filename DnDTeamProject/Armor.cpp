#include "Armor.h"
#include "Dice.h"
#include "Names.h"



Armor::Armor() {
	setName(armorNames[Dice::roll("1d100-1")]);
	randomBonuses();
}

Armor::~Armor() {
}



//Accessors
ArmorType Armor::getArmorType() {
	return _armorType;
}

int Armor::getArmorClass() {
	return _armorClass;
}




//Mutators
void Armor::setArmorType(ArmorType armorType) {
	_armorType = armorType;
}

void Armor::setArmorClass(int armorClass) {
	_armorClass = armorClass;
}




//Randoms a magical bonus modifier of between 1 and 5 for the item and applies the bonus, split randomly into the item's stat bonuses 
void Armor::randomBonuses() {
	setArmorClass(Dice::roll("1d5"));
}


std::string Armor::toString() {
	std::string s;
	s = Item::toString();
	if (getArmorType() != ArmorType::DEFAULT)
		s += ", Armor Type: " + armorTypeInfo[getArmorType()];
	if (getArmorClass() != 0)
		s += ", Armor Class: " + getArmorClass();
	return s;
}

