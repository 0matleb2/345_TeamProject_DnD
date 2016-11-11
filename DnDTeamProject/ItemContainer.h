//! @file
//! @brief Header File for Item Container object
//!
//! This is a class for an Item container. Again, I chose to use vectors because they are mutable in size and permit
//! random access. Container has a vector of Items acting as its contents. 
#ifndef ItemContainer_h
#define ItemContainer_h

#include <iostream>
#include <vector>

#include "Item.h"



using namespace std;

//! class that implements an item container
class ItemContainer
{
public:
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar.register_type(static_cast<Equipment *>(NULL));
		ar.register_type(static_cast<Weapon *>(NULL));

		ar & contents;
	}

	// default constructor
	ItemContainer();
	// copy constructor
	ItemContainer(const ItemContainer& orig);

	// retrieve item without removing
	Item* getItem(int pos);
	// add item to container
	void addItem(Item* i);
	// remove item from container
	Item* removeItem(int pos);
	// print contents of the container
	void printContents();
	// returns number of items in container
	int getSize();
	//retrieves index of item, if there is any
	int getItemIndex(Item* it);

	//NEW (11/9)
	// rescale all items in container to desired level
	void rescale(int tgt_lvl);

	// destructor
	~ItemContainer();

//private:
	vector<Item*> contents;
};

#endif