#pragma once
#include "Item.h"
#include "Types.h"



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
	ItemType getItemType();

	std::string toString();


private:

	int _armorClass;
	int _intelligenceBonus;
	int _wisdomBonus;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _armorClass;
		ar & _intelligenceBonus;
		ar & _wisdomBonus;
	}

};

