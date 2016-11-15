#include "Boots.h"
#include "Names.h"
#include "Dice.h"



Boots::Boots() {
	setName(bootNames[Dice::roll("1d100-1")]);
	randomBonuses();
}


Boots::~Boots() {
}



//Accessors
int Boots::getArmorClass() {
	return _armorClass;
}
int Boots::getDexterityBonus() {
	return _dexterityBonus;
}



//Mutators
void Boots::setArmorClass(int armorClass) {
	_armorClass = armorClass;
}
void Boots::setDexterityBonus(int dexterityBonus) {
	_dexterityBonus = dexterityBonus;
}


//Randoms a magical bonus modifier of between 1 and 5 for the item and applies the bonus, split randomly, into the items stat bonuses 
void Boots::randomBonuses() {
	int totalBonus = Dice::roll("1d5");
	int statBonuses[2];
	for (int i = 0; i < totalBonus; ++i) {
		statBonuses[Dice::roll("1d2-1")]++;
	}
	setArmorClass(statBonuses[0]);
	setDexterityBonus(statBonuses[1]);
}


std::string Boots::toString() {
	std::string s;
	s = Item::toString();
	if (getArmorClass() != 0)
		s += ", Armor Class: " + getArmorClass();
	if (getDexterityBonus() != 0)
		s += ", Dexterity bonus: " + getDexterityBonus();
	return s;
}