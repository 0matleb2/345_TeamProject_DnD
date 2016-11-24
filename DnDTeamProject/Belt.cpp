#include "Belt.h"
#include "Dice.h"
#include "Names.h"



Belt::Belt() : _strengthBonus(0), _constitutionBonus(0) {
	_itemType = ItemType::BELT;
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


//Randoms a magical bonus modifier of between 1 and 5 for the item and applies the bonus, split randomly, into the items stat bonuses
void Belt::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[2] = { 0, 0 };
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
		s += ", Constitution bonus: " + std::to_string(getConstitutionBonus());
	if (getStrengthBonus() != 0)
		s += ", Strength bonus: " + std::to_string(getStrengthBonus());
	return s;
}