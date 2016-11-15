#pragma once
#include "Item.h"



class Belt : public Item {

public:

	Belt();
	~Belt();

	int getConstitutionBonus();
	int getStrengthBonus();

	void setConstitutionBonus(int constitutionBonus);
	void setStrengthBonus(int strengthBonus);

	void randomBonuses();

	std::string toString();

private:

	int _constitutionBonus;
	int _strengthBonus;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & boost::serialization::base_object<Item>(*this);
		ar & _constitutionBonus;
		ar & _strengthBonus;
	}
};

