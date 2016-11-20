#pragma once
#include "Item.h"
#include "Types.h"



class Bracers :	public Item {

public:

	Bracers();
	~Bracers();

	int getArmorClass();
	int getStrengthBonus();

	void setArmorClass(int armorClass);
	void setStrengthBonus(int strengthBonus);

	void randomBonuses();
	ItemType getItemType();

	std::string toString();

private:

	int _armorClass;
	int _strengthBonus;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _armorClass;
		ar & _strengthBonus;
	}

};

