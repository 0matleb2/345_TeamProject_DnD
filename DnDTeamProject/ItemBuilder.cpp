#include "ItemBuilder.h"



ItemBuilder::ItemBuilder() {
}


ItemBuilder::~ItemBuilder() {
}

Item * ItemBuilder::getItem() {
	return _item;
}

void ItemBuilder::setItem(Item * item) {
	_item = item;
}

void ItemBuilder::construct() {
}

void ItemBuilder::buildIdentity() {
}

void ItemBuilder::buildStats() {
}

