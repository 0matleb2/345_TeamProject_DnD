#include "Shield.h"
#include "Dice.h"
#include "Names.h"


Shield::Shield() : _armorClass(0), _armorClassBonus(0) {
	_itemType = ItemType::SHIELD;

}

Shield::Shield(ShieldType shieldType) : Shield() {
	_itemType = ItemType::SHIELD;
	_shieldType = shieldType;
	setName(shieldNames[Dice::roll("1d100-1")]);
	randomBonuses();

	switch (shieldType) {
	case ShieldType::BUCKLER:
		_armorClass = 1;
		break;
	case ShieldType::HEAVY_SHIELD:
		_armorClass = 2;
		break;
	case ShieldType::TOWER_SHIELD:
		_armorClass = 4;
		break;
	}
}

Shield::~Shield() {
}



//Accessors
int Shield::getArmorClass() {
	return _armorClass;
}

int Shield::getArmorClassBonus() {
	return _armorClassBonus;
}

ShieldType Shield::getShieldType() {
	return _shieldType;
}



//Mutators
void Shield::setArmorClass(int armorClass) {
	_armorClass = armorClass;
}

void Shield::setArmorClassBonus(int armorClassBonus) {
	_armorClassBonus = armorClassBonus;
}

void Shield::setShieldType(ShieldType shieldType) {
	_shieldType = shieldType;
}


void Shield::randomBonuses() {
	setArmorClassBonus(Dice::roll("1d5"));
}

std::string Shield::toString() {
	std::string s;
	s = Item::toString();
	if (getShieldType() != ShieldType::DEFAULT)
		s += ", Shield type: " + shieldTypeInfo[getShieldType()];
	if (getArmorClass() != 0)
		s += ", Armor class: " + std::to_string(getArmorClass());
	if (getArmorClassBonus() != 0)
		s += ", Armor class bonus: " + std::to_string(getArmorClassBonus());
	return s;
}
