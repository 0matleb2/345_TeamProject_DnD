//! @file
//! @brief Header File for Item Container object
//!
//! This is a class for an Item container. Again, I chose to use std::vectors because they are mutable in size and permit
//! random access. Container has a std::vector of Items acting as its _contents. 
#pragma once
#include <iostream>
#include <vector>

#include "Item.h"


class ItemContainer {

public:

	ItemContainer();
	ItemContainer(const ItemContainer& orig);
	~ItemContainer();

	Item* getItem(int pos);
	int getSize();
	int getItemIndex(Item* it);

	void addItem(Item* i);
	Item* removeItem(int pos);
	void printContents();

	void rescale(int tgt_lvl);


private:
	std::vector<Item*> _contents;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar.register_type(static_cast<Equipment *>(NULL));
		ar.register_type(static_cast<Weapon *>(NULL));
		ar & _contents;
	}
};

