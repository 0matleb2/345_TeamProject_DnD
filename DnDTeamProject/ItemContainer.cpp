#include <algorithm>
#include <iostream>
#include "ItemContainer.h"



ItemContainer::ItemContainer() {

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
	for (int i = 0; i < _quantity; ++i) {
		s += "\n" + _contents[i]->toString();
	}
	return s;
}
