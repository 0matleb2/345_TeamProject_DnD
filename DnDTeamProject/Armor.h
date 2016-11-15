#pragma once
#include "Item.h"
#include "Types.h"



class Armor : public Item {

public:

	Armor();
	~Armor();

	ArmorType getArmorType();
	int getArmorClass();

	void setArmorType(ArmorType armorType);
	void setArmorClass(int armorClass);

	void randomBonuses();

	std::string toString();

private:

	ArmorType _armorType;
	int _armorClass;
	


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _armorClass;
		ar & _armorType;
	}

};



