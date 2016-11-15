#include "Ring.h"
#include "Dice.h"
#include "Names.h"


Ring::Ring() {
	setName(ringNames[Dice::roll("1d100-1")]);
	randomBonuses();
}


Ring::~Ring() {
}



//Accessors
int Ring::getArmorClass() {
	return _armorClass;
}
int Ring::getStrengthBonus() {
	return _strengthBonus;
}
int Ring::getConstitutionBonus() {
	return _constitutionBonus;
}
int Ring::getWisdomBonus() {
	return _wisdomBonus;
}
int Ring::getCharismaBonus() {
	return _charismaBonus;
}



//Mutators
void Ring::setArmorClass(int armorClass) {
	_armorClass = armorClass;
}
void Ring::setStrengthBonus(int strengthBonus) {
	_strengthBonus = strengthBonus;
}
void Ring::setConstitutionBonus(int constitutionBonus) {
	_constitutionBonus = constitutionBonus;
}
void Ring::setWisdomBonus(int wisdomBonus) {
	_wisdomBonus = wisdomBonus;
}
void Ring::setCharismaBonus(int charismaBonus) {
	_charismaBonus = charismaBonus;
}



void Ring::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[5];
	for (int i = 0; i < totalBonus; ++i) {
		statBonuses[Dice::roll("1d5-1")]++;
	}
	setArmorClass(statBonuses[0]);
	setStrengthBonus(statBonuses[1]);
	setConstitutionBonus(statBonuses[2]);
	setWisdomBonus(statBonuses[3]);
	setCharismaBonus(statBonuses[4]);
}