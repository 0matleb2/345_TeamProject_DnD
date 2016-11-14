//! @file
//! @brief Implementation file for Item Container class
//!
#include "ItemContainer.h"



ItemContainer::ItemContainer() {
}

ItemContainer::ItemContainer(const ItemContainer& orig) {
	int s = orig._contents.size();
	// iterate through std::vector of original, clone and push into new std::vector.
	for (int i = 0; i < s; i++)	{
		_contents.push_back(orig._contents[i]->clone());
	}
}

ItemContainer::~ItemContainer() {
}



//Accessors
Item* ItemContainer::getItem(int index) {
	return _contents[index];
}

int ItemContainer::getSize() {
	return _contents.size();
}

//! returns the index of an item, if it is present in the ItemContainer, that is
//! @return: index of item in std::vector, returns -1 if there is none to be found
int ItemContainer::getItemIndex(Item* it) {
	int pos = std::find(_contents.begin(), _contents.end(), it) - _contents.begin();
	if (pos >= _contents.size())
		return -1;
	else return pos;
}



//Mutators
void ItemContainer::addItem(Item* item) {
	_contents.push_back(item);
}

Item* ItemContainer::removeItem(int index) {
	Item* item = _contents[index];
	_contents.erase(_contents.begin() + index);
	return item;
}



void ItemContainer::printContents() {
	std::cout << "Contents of Container (" << _contents.size() << " items):" << std::endl;
	int indexno = 0;
	for (int it = 0; it < _contents.size(); it++) {
		std::cout << indexno << ") ";
		_contents[it]->print();
		indexno++;
	}
	std::cout << std::endl;
}

void ItemContainer::rescale(int tgt_lvl) {
	if (_contents.size() == 0)
		return;
	for (int i = 0; i < _contents.size(); i++) {
		_contents[i]->rescale(tgt_lvl);
	}
}

