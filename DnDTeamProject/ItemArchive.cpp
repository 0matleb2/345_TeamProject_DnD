#include "ItemArchive.h"



ItemArchive::ItemArchive() {
}

ItemArchive::ItemArchive(std::vector<Item*> itemArchive) : _itemArchive(itemArchive) {
}


ItemArchive::~ItemArchive() {
}

std::vector<Item*> ItemArchive::getItemArchive() {
	return _itemArchive;
}

void ItemArchive::setItemArchive(std::vector<Item*> itemArchive) {
	_itemArchive = itemArchive;
}

void ItemArchive::addItem(Item * item) {
	_itemArchive.push_back(item);
}
