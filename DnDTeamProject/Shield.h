#pragma once
#include "Item.h"
#include "Types.h"



class Shield : public Item {

public:

	Shield();
	~Shield();

	int getArmorClass();
	ShieldType getShieldType();

	void setArmorClass(int armorClass);
	void setShieldType(ShieldType shieldType);

	void randomBonuses();

private:

	int _armorClass;
	ShieldType _shieldType;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _armorClass;
		ar & _shieldType;
	}
};

