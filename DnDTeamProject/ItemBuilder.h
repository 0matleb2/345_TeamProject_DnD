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

	void buildIdentity();
	void buildStats();

};

