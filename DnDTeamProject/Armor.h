#pragma once
#include "Item.h"
#include "Types.h"



class Armor : public Item {

public:

	Armor();
	Armor(ArmorType armorType);
	~Armor();

	ArmorType getArmorType();
	int getArmorClass();
	int getArmorClassBonus();

	void setArmorType(ArmorType armorType);
	void setArmorClass(int armorClass);
	void setArmorClassBonus(int armorClassBonus);

	void randomBonuses();
	ItemType getItemType();

	std::string toString();

private:

	ArmorType _armorType;
	int _armorClass;
	int _armorClassBonus;
	


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _armorClass;
		ar & _armorClassBonus;
		ar & _armorType;
	}

};