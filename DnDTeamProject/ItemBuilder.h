#pragma once
#include "Item.h"


class ItemBuilder {

public:
	ItemBuilder();
	~ItemBuilder();

	Item* getItem();

	void setItem(Item* item);

	void construct();

private:

	Item* _item;

	void buildType();
	void buildIdentity();

	void buildArmor();
	void buildBelt();
	void buildBoots();
	void buildBracers();
	void buildHelmet();
	void buildRing();
	void buildShield();
	void buildWeapon();

};

