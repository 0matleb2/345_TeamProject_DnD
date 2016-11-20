#pragma once
#include "Item.h"
#include "Types.h"



class Boots : public Item {

public:

	Boots();
	~Boots();

	int getArmorClass();
	int getDexterityBonus();

	void setArmorClass(int armorClass);
	void setDexterityBonus(int dexterityBonus);
	
	void randomBonuses();

	std::string toString();
	ItemType getItemType();

private:

	int _armorClass;
	int _dexterityBonus;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _armorClass;
		ar & _dexterityBonus;
	}

};

