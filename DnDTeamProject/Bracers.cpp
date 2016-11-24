#include "Bracers.h"
#include "Dice.h"
#include "Names.h"



Bracers::Bracers() : _armorClass(0), _strengthBonus(0) {
	_itemType = ItemType::BRACERS;
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

//Randoms a magical bonus modifier of between 1 and 5 for the item and applies the bonus, split randomly, into the items stat bonuses
void Bracers::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[2] = { 0, 0 };
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
		s += ", Armor class: " + std::to_string(getArmorClass());
	if (getStrengthBonus() != 0)
		s += ", Strength bonus: " + std::to_string(getStrengthBonus());
	return s;
}
