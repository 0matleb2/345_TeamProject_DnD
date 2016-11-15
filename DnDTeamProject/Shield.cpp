#include "Shield.h"
#include "Dice.h"
#include "Names.h"


Shield::Shield() {
	setName(shieldNames[Dice::roll("1d100-1")]);
	randomBonuses();
}

Shield::~Shield() {
}



//Accessors
int Shield::getArmorClass() {
	return _armorClass;
}

ShieldType Shield::getShieldType() {
	return ShieldType();
}



//Mutators
void Shield::setArmorClass(int armorClass) {
	_armorClass = armorClass;
}

void Shield::setShieldType(ShieldType shieldType) {
	_shieldType = shieldType;
}



void Shield::randomBonuses() {
	setArmorClass(Dice::roll("1d5"));
}