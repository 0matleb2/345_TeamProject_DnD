#include "Armor.h"
#include "Dice.h"
#include "Names.h"



Armor::Armor() : _armorClass(0), _armorClassBonus(0) {

}

Armor::Armor(ArmorType armorType) : Armor() {
	_armorType = armorType;
	setName(armorNames[Dice::roll("1d100-1")]);
	randomBonuses();
	switch (armorType) {
	case ArmorType::PADDED:
		_armorClass = 1;
		break;
	case ArmorType::LEATHER:
		_armorClass = 2;
		break;
	case ArmorType::STUDDED_LEATHER:
		_armorClass = 3;
		break;
	case ArmorType::CHAIN_SHIRT:
		_armorClass = 4;
		break;
	case ArmorType::BREASTPLATE:
		_armorClass = 5;
		break;
	case ArmorType::BANDED_MAIL:
		_armorClass = 6;
		break;
	case ArmorType::HALF_PLATE:
		_armorClass = 7;
		break;
	case ArmorType::FULL_PLATE:
		_armorClass = 8;
		break;
	}
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

int Armor::getArmorClassBonus() {
	return _armorClassBonus;
}




//Mutators
void Armor::setArmorType(ArmorType armorType) {
	_armorType = armorType;
}

void Armor::setArmorClass(int armorClass) {
	_armorClass = armorClass;
}

void Armor::setArmorClassBonus(int armorClassBonus) {
	_armorClassBonus = armorClassBonus;
}




//Randoms a magical bonus modifier of between 1 and 5 for the item and applies the bonus, split randomly into the item's stat bonuses 
void Armor::randomBonuses() {
	setArmorClassBonus(Dice::roll("1d5"));
}

ItemType Armor::getItemType() {
	return ItemType::ARMOR;
}


std::string Armor::toString() {
	std::string s;
	s = Item::toString();
	if (getArmorType() != ArmorType::DEFAULT)
		s += ", Armor Type: " + armorTypeInfo[getArmorType()];
	if (getArmorClass() != 0)
		s += ", Armor class: " + std::to_string(getArmorClass());
	if (getArmorClassBonus() != 0)
		s += ", Armor class bonus: " + std::to_string(getArmorClassBonus());
	return s;
}

