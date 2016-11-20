#pragma once
#include "Item.h"
#include "Types.h"


class Ring : public Item {

public:

	Ring();
	~Ring();

	int getArmorClass();
	int getStrengthBonus();
	int getConstitutionBonus();
	int getWisdomBonus();
	int getCharismaBonus();

	void setArmorClass(int armorClass);
	void setStrengthBonus(int strengthBonus);
	void setConstitutionBonus(int constitutionBonus);
	void setWisdomBonus(int wisdomBonus);
	void setCharismaBonus(int charismaBonus);

	void randomBonuses();
	ItemType getItemType();

	std::string toString();

private:

	int _armorClass;
	int _strengthBonus;
	int _constitutionBonus;
	int _wisdomBonus;
	int _charismaBonus;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _armorClass;
		ar & _strengthBonus;
		ar & _constitutionBonus;
		ar & _wisdomBonus;
		ar & _charismaBonus;
	}

};

