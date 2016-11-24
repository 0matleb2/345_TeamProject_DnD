#include "Helmet.h"
#include "Dice.h"
#include "Names.h"



Helmet::Helmet() : _armorClass(0), _intelligenceBonus(0), _wisdomBonus(0) {
	_itemType = ItemType::HELMET;
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


//Randoms a magical bonus modifier of between 1 and 5 for the item and applies the bonus, split randomly, into the items stat bonuses
void Helmet::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[3] = { 0, 0, 0 };
	for (int i = 0; i < totalBonus; ++i) {
		statBonuses[Dice::roll("1d3-1")]++;
	}
	setArmorClass(statBonuses[0]);
	setIntelligenceBonus(statBonuses[1]);
	setWisdomBonus(statBonuses[2]);
}

std::string Helmet::toString() {
	std::string s;
	s = Item::toString();
	if (getArmorClass() != 0)
		s += ", Armor class: " + std::to_string(getArmorClass());
	if (getIntelligenceBonus() != 0)
		s += ", Intelligence bonus: " + std::to_string(getIntelligenceBonus());
	if (getWisdomBonus() != 0)
		s += ", Wisdom bonus: " + std::to_string(getWisdomBonus());
	return s;
}
