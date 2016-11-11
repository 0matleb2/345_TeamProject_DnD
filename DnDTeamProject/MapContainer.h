//! @file
//! @brief header file for container of items as map object
//!
//! this class represents an item container as a map object
#pragma once

#include "ItemContainer.h"

using namespace std;

class MapContainer
{
public:
	// default constructor
	MapContainer();
	// parametrized constructor
	MapContainer(int x, int y, ItemContainer* ele, char sprite);
	// destructor
	~MapContainer();
	// set new container
	void setElement(ItemContainer* ele);
	// return contained container
	ItemContainer* getElement();
	// get width index
	int getX();
	// get height index
	int getY();
	// set width index
	void setX(int x);
	// set height index
	void setY(int y);
	// rescale contained items
	void rescale(int tgt_lvl);
	// print contents of container
	void print();
	// add item to container
	void addItem(Item* it);

	char getSymbol();

	void setSymbol(char ns);

	//serialization
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar & x_pos;
		ar & y_pos;
		ar & element;
		ar & symbol;
	}
private:
	// width index
	int x_pos;
	// height index
	int y_pos;
	// container itself
	ItemContainer* element;
	// symbol representing element
	char symbol;
};