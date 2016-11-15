#include "Belt.h"
#include "Dice.h"
#include "Names.h"


Belt::Belt() {
	setName(beltNames[Dice::roll("1d100-1")]);
	randomBonuses();
}

Belt::~Belt() {
}



//Accessors
int Belt::getConstitutionBonus() {
	return _constitutionBonus;
}

int Belt::getStrengthBonus() {
	return _strengthBonus;
}



//Mutators
void Belt::setConstitutionBonus(int constitutionBonus) {
	_constitutionBonus = constitutionBonus;
}

void Belt::setStrengthBonus(int strengthBonus) {
	_strengthBonus = strengthBonus;
}

void Belt::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[2];
	for (int i = 0; i < totalBonus; ++i) {
		statBonuses[Dice::roll("1d2-1")]++;
	}
	setConstitutionBonus(statBonuses[0]);
	setStrengthBonus(statBonuses[1]);
}


std::string Belt::toString() {
	std::string s;
	s = Item::toString();
	if (getConstitutionBonus() != 0)
		s += ", Constitution bonus: " + getConstitutionBonus();
	if (getStrengthBonus() != 0)
		s += ", Strength bonus: " + getStrengthBonus();
	return s;
}