#include <algorithm>
#include <iostream>
#include "ItemContainer.h"



ItemContainer::ItemContainer() {
	_contents.reserve(9);
}

ItemContainer::ItemContainer(int capacity) : _capacity(capacity) {
	_contents.reserve(capacity);
}

ItemContainer::~ItemContainer() {
}



//Accessors
std::vector<Item*> ItemContainer::getContents() {
	return _contents;
}
int ItemContainer::getCapacity() {
	return _capacity;
}
int ItemContainer::getQuantity() {
	return _quantity;
}


//Mutators
void ItemContainer::setCapacity(int capacity) {
	_capacity = capacity;
}

void ItemContainer::setQuantity(int quantity) {
	_quantity = quantity;
}



void ItemContainer::depositItem(Item& item) {
	if (_quantity == _capacity) {
		std::cout << "Cannot deposit item to item container. It is full!" << std::endl;
	}
	else if (std::find(_contents.begin(), _contents.end(), &item) != _contents.end()) {
		std::cout << "Cannot deposit item to item container. It already contains that item!" << std::endl;
	}
	else {
		_contents.push_back(&item);
		++_quantity;
	}
}

Item* ItemContainer::withdrawItem(Item& item) {
	std::vector<Item*>::iterator findIterator = std::find(_contents.begin(), _contents.end(), &item);
	if (findIterator != _contents.end()) {
		Item* tmp = *findIterator;
		_contents.erase(findIterator);
		--_quantity;
		return tmp;
	}
	else {
		std::cout << "Cannot withdraw item from item container. It does not contain that item!" << std::endl;
		return nullptr;
	}
}

Item * ItemContainer::withdrawItem(int index) {
	if (index < _quantity) {
		Item* tmp = _contents[index];
		_contents.erase(_contents.begin() + index);
		--_quantity;
		return tmp;
	}
	else {
		std::cout << "Cannot withdraw item from item container. Index is out of bounds!" << std::endl;
		return nullptr;
	}
}



std::string ItemContainer::toString() {
	std::string s;
	if (_contents.size() > 0)
		s += _contents[0]->toString();
	for (int i = 1; i < _quantity; ++i) {
		s += "\n" + _contents[i]->toString();
	}
	return s;
}

bool ItemContainer::operator==(const ItemContainer & itemContainer) const {
	return _contents == itemContainer._contents &&
		_capacity == itemContainer._capacity &&
		_quantity == itemContainer._quantity;
}
