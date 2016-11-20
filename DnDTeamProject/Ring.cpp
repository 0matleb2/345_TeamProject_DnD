#include "Ring.h"
#include "Dice.h"
#include "Names.h"



Ring::Ring() : _armorClass(0), _strengthBonus(0), _constitutionBonus(0), _wisdomBonus(0), _charismaBonus(0) {
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


//Randoms a magical bonus modifier of between 1 and 5 for the item and applies the bonus, split randomly, into the items stat bonuses
void Ring::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[5] = { 0, 0, 0, 0, 0 };
	for (int i = 0; i < totalBonus; ++i) {
		++statBonuses[Dice::roll("1d5-1")];
	}
	setArmorClass(statBonuses[0]);
	setStrengthBonus(statBonuses[1]);
	setConstitutionBonus(statBonuses[2]);
	setWisdomBonus(statBonuses[3]);
	setCharismaBonus(statBonuses[4]);
}

ItemType Ring::getItemType() {
	return ItemType::RING;
}

std::string Ring::toString() {
	std::string s;
	s = Item::toString();
	if (getArmorClass() != 0)
		s += ", Armor class: " + std::to_string(getArmorClass());
	if (getStrengthBonus() != 0)
		s += ", Strength bonus: " + std::to_string(getStrengthBonus());
	if (getConstitutionBonus() != 0)
		s += ", Constitution bonus: " + std::to_string(getConstitutionBonus());
	if (getWisdomBonus() != 0)
		s += ", Wisdom bonus: " + std::to_string(getWisdomBonus());
	if (getCharismaBonus() != 0)
		s += ", Charisma bonus: " + std::to_string(getCharismaBonus());
	return s;
}
