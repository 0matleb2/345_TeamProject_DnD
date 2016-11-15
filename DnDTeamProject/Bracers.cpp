#include "Bracers.h"
#include "Dice.h"
#include "Names.h"


Bracers::Bracers() {
	setName(bracerNames[Dice::roll("1d100-1")]);
	randomBonuses();
}

Bracers::~Bracers() {
}



//Accessors
int Bracers::getArmorClass() {
	return _armorClass;
}

int Bracers::getStrengthBonus() {
	return _strengthBonus;
}



//Mutators
void Bracers::setArmorClass(int armorClass) {
	_armorClass = armorClass;
}

void Bracers::setStrengthBonus(int strengthBonus) {
	_strengthBonus = strengthBonus;
}

void Bracers::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[2];
	for (int i = 0; i < totalBonus; ++i) {
		statBonuses[Dice::roll("1d2-1")]++;
	}
	setArmorClass(statBonuses[0]);
	setStrengthBonus(statBonuses[1]);
}

std::string Bracers::toString() {
	std::string s;
	s = Item::toString();
	if (getArmorClass() != 0)
		s += ", Armor Class: " + getArmorClass();
	if (getStrengthBonus() != 0)
		s += ", Strength bonus: " + getStrengthBonus();
	return s;
}
