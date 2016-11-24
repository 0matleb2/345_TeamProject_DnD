#pragma once
#include "Item.h"
#include "Types.h"


class Shield : public Item {

public:

	Shield();
	Shield(ShieldType shieldType);
	~Shield();

	int getArmorClass();
	int getArmorClassBonus();
	ShieldType getShieldType();

	void setArmorClass(int armorClass);
	void setArmorClassBonus(int armorClassBonus);
	void setShieldType(ShieldType shieldType);

	void randomBonuses();

	std::string toString();

private:

	int _armorClass;
	int _armorClassBonus;
	ShieldType _shieldType;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _armorClass;
		ar & _armorClassBonus;
		ar & _shieldType;
	}
};

