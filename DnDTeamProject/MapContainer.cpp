//! @file
//! @brief implementation file for container as map object
//!
#include "MapContainer.h"

//! default constructor
MapContainer::MapContainer() : x_pos(0), y_pos(0), element(new ItemContainer()), symbol('H')
{

}

//! parametrized constructor
//! @param x : width index
//! @param y : height index
//! @param ele : container element contained
MapContainer::MapContainer(int x, int y, ItemContainer* ele, char sprite) : x_pos(x), y_pos(y), element(ele), symbol(sprite)
{

}

//! destructor
MapContainer::~MapContainer()
{
	//delete element;
}

//! set container element
//! @param ele : pointer to container element
void MapContainer::setElement(ItemContainer* ele)
{
	element = ele;
}

//! return contained container
//! @return container of map element
ItemContainer* MapContainer::getElement()
{
	return element;
}

//! accessor for width index
//! @return width index
int MapContainer::getX()
{
	return x_pos;
}

//! accessor for height index
//! @return height index
int MapContainer::getY()
{
	return y_pos;
}

//! mutator for width index
//! @param x : new width index
void MapContainer::setX(int x)
{
	x_pos = x;
}

//! mutator for height index
//! @param y : new height index
void MapContainer::setY(int y)
{
	y_pos = y;
}

//! rescale items in container to target level
//! @param tgt_lvl : target level to rescale to
void MapContainer::rescale(int tgt_lvl)
{
	element->rescale(tgt_lvl);
}

char MapContainer::getSymbol()
{
	return symbol;
}

void MapContainer::setSymbol(char ns)
{
	symbol = ns;
}

//! print contained container's contents
void MapContainer::print()
{
	cout << "Container element at position: (" << x_pos << ", " << y_pos << ")" << endl;
	cout << "Details:" << endl;
	element->printContents();
}

//! add item to container
//! @param it : pointer of item to add
void MapContainer::addItem(Item* it)
{
	element->addItem(it);
}