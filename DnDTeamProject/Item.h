#pragma once
#include <string>
#include "Types.h"
#include "boost\serialization\access.hpp"



class Item {

public:

	Item();
	Item(std::string name);
	virtual ~Item();

	std::string getName();
	ItemType getItemType();


	void setName(std::string);
	void setType(ItemType itemType);
	virtual std::string toString();
	virtual void randomBonuses() = 0;

	bool operator ==(const Item& item) const; //Needed for std::find()

protected:

	static int _sNextId;

	const int _id;
	std::string _name;
	ItemType _itemType;


	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _name;
	}

};
