#include "Helmet.h"
#include "Dice.h"
#include "Names.h"


Helmet::Helmet() {
	setName(helmetNames[Dice::roll("1d100-1")]);
	randomBonuses();
}

Helmet::~Helmet() {
}



//Accessors
int Helmet::getArmorClass() {
	return _armorClass;
}

int Helmet::getIntelligenceBonus() {
	return _intelligenceBonus;
}

int Helmet::getWisdomBonus() {
	return _wisdomBonus;
}



//Mutators
void Helmet::setArmorClass(int armorClass) {
	_armorClass = armorClass;
}

void Helmet::setIntelligenceBonus(int intelligenceBonus) {
	_intelligenceBonus = intelligenceBonus;
}

void Helmet::setWisdomBonus(int wisdomBonus) {
	_wisdomBonus = wisdomBonus;
}



void Helmet::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[3];
	for (int i = 0; i < totalBonus; ++i) {
		statBonuses[Dice::roll("1d3-1")]++;
	}
	setArmorClass(statBonuses[0]);
	setIntelligenceBonus(statBonuses[1]);
	setWisdomBonus(statBonuses[2]);
}