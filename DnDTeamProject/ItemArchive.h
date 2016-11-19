#pragma once
#include <vector>
#include "Item.h"
#include "Armor.h"
#include "Belt.h"
#include "Boots.h"
#include "Bracers.h"
#include "Helmet.h"
#include "Ring.h"
#include "Shield.h"
#include "Weapon.h"



class ItemArchive {

public:

	ItemArchive();
	ItemArchive(std::vector<Item*> itemArchive);
	~ItemArchive();

	std::vector<Item*> getItemArchive();

	void setItemArchive(std::vector<Item*> itemArchive);
	void addItem(Item* item);
	
private:

	std::vector<Item*> _itemArchive;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar.template register_type<Armor>();
		ar.template register_type<Belt>();
		ar.template register_type<Boots>();
		ar.template register_type<Bracers>();
		ar.template register_type<Helmet>();
		ar.template register_type<Ring>();
		ar.template register_type<Shield>();
		ar.template register_type<Weapon>();
		ar & _itemArchive;
	}
};