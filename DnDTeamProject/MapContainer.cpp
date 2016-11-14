//! @file
//! @brief implementation file for container as map object
//!
#include "MapContainer.h"



MapContainer::MapContainer() : _x(0), _y(0), _itemContainer(&ItemContainer()), _symbol('H') {
}

MapContainer::MapContainer(int x, int y, ItemContainer* ele, char sprite) : _x(x), _y(y), _itemContainer(ele), _symbol(sprite) {
}

MapContainer::~MapContainer() {
}

void MapContainer::setItemContainer(ItemContainer* itemContainer) {
	_itemContainer = itemContainer;
}

//Accessors
int MapContainer::getX() {
	return _x;
}

int MapContainer::getY() {
	return _y;
}

ItemContainer* MapContainer::getItemContainer() {
	return _itemContainer;
}

char MapContainer::getSymbol() {
	return _symbol;
}

//Mutators
void MapContainer::setX(int x) {
	_x = x;
}

void MapContainer::setY(int y) {
	_y = y;
}

void MapContainer::setSymbol(char symbol) {
	_symbol = symbol;
}



void MapContainer::rescale(int targetLvl) {
	_itemContainer->rescale(targetLvl);
}

void MapContainer::print() { 
	std::cout << "Container _itemContainer at position: (" << _x << ", " << _y << ")" << std::endl;
	std::cout << "Details:" << std::endl;
	_itemContainer->printContents();
}
