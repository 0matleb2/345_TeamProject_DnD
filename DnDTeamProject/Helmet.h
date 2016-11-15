#pragma once
#include "Item.h"



class Helmet : public Item {

public:

	Helmet();
	~Helmet();

	int getArmorClass();
	int getIntelligenceBonus();
	int getWisdomBonus();

	void setArmorClass(int armorClass);
	void setIntelligenceBonus(int intelligenceBonus);
	void setWisdomBonus(int wisdomBonus);

	void randomBonuses();

private:

	int _armorClass;
	int _intelligenceBonus;
	int _wisdomBonus;

};

