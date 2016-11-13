//! @file
//! @brief header file for container of items as map object
//!
//! this class represents an item container as a map object
#pragma once

#include "ItemContainer.h"



class MapContainer {

public:

	MapContainer();
	MapContainer(int x, int y, ItemContainer* ele, char sprite);
	~MapContainer();

	int getX();
	int getY();
	ItemContainer* getItemContainer();
	char getSymbol();

	void setX(int);
	void setY(int);
	void setItemContainer(ItemContainer*);
	void setSymbol(char);

	void rescale(int targetLvl);
	void print();



private:

	int _x;
	int _y;
	ItemContainer* _itemContainer;
	char _symbol;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _x;
		ar & _y;
		ar & _itemContainer;
		ar & _symbol;
	}

};