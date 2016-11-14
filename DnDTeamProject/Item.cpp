//! @file
//! @brief Implementation of Item class
//!
#include "Item.h"


Item::Item() : _name("Default"), _type(ItemType::OTHER), _enchant(std::vector<Enchant*>()) {
}

//! parametrized constructor accepting a std::string for item _name, enum for _type, and a std::vector of Enchants
//! @param nm : _name of Item
//! @param tp : _type of Item
//! @param nv : std::vector of Enchants
Item::Item(std::string nm, ItemType tp, std::vector<Enchant*> nv) : _name(nm), _type(tp), _enchant(nv) {
}

Item::Item(const Item& orig) : _name(orig._name), _type(orig._type), _enchant(orig._enchant){
}

Item::~Item() {
}

Item* Item::clone() {
	return &Item(*this);
}




//Accessors
std::string Item::getName() {
	return _name;
}

ItemType Item::getType() {
	return _type;
}

std::vector<Enchant*> Item::getEnch() {
	return _enchant;
}



//Mutators
void Item::setName(std::string nn) {
	_name = nn;
}

void Item::setType(ItemType itp) {
	_type = itp;
}

void Item::setEnch(std::vector<Enchant*> ech) {
	_enchant = ech;
}

void Item::addEnch(Enchant* eh) {
	_enchant.push_back(eh);
}

Enchant Item::removeEnch(int pos) {
	Enchant* temp = _enchant[pos];
	_enchant.erase(_enchant.begin() + pos);
	return *temp;
}

void Item::clearEnch() {
	_enchant.clear();
}



//! check validity of Item
//! @return False if Item posesses an Enchant it is not allowed to have
bool Item::isValid() {
	// items without _enchantants are valid
	if (_enchant.size() == 0)
		return true;
	for (int i = 0; i < _enchant.size(); i++) {
		// check for less than 1
		if (_enchant[i]->getValue() < 1)
			return false;
		// check for bonus more than 5
		if (_enchant[i]->getValue() > 5)
			return false;
		// check if each item _type lines up with enhanced stat
		switch (_type) {
		case ItemType::HELMET:
			if (_enchant[i]->getType() != Stats::INT && _enchant[i]->getType() != Stats::WIS && _enchant[i]->getType() != Stats::AC)
				return false;
			break;
		case ItemType::ARMOR:
			if (_enchant[i]->getType() != Stats::AC)
				return false;
			break;
		case ItemType::SHIELD:
			if (_enchant[i]->getType() != Stats::AC)
				return false;
			break;
		case ItemType::RING:
			if (_enchant[i]->getType() != Stats::AC && _enchant[i]->getType() != Stats::STR && _enchant[i]->getType() != Stats::CON
				&& _enchant[i]->getType() != Stats::WIS && _enchant[i]->getType() != Stats::CHA)
				return false;
			break;
		case ItemType::BELT:
			if (_enchant[i]->getType() != Stats::CON && _enchant[i]->getType() != Stats::STR)
				return false;
			break;
		case ItemType::BOOTS:
			if (_enchant[i]->getType() != Stats::AC && _enchant[i]->getType() != Stats::DEX)
				return false;
			break;
		case ItemType::WEAPON:
			if (_enchant[i]->getType() != Stats::ATK && _enchant[i]->getType() != Stats::DMG)
				return false;
			break;
		default:
			break;
		}
	}
	return true; //valid if all tests passed
}


//! abstract print method meant to be overridden in child classes
//! decided to resort to print as I could not make it work with an operator overload
void Item::print() { 
}

//! for use in scaling method, takes an item _type and stat and checks if _enchantant would be valid
//! @param tgt__type : item _type 
//! @param tgt_stat : stat boosted
//! @return : valid or no _enchantant
bool Item::validEnch(ItemType tgt__type, Stats tgt_stat) {
	switch (tgt__type) {
	case ItemType::HELMET:
		if (tgt_stat != Stats::WIS && tgt_stat != Stats::INT && tgt_stat != Stats::AC)
			return false;
		break;
	case ItemType::ARMOR:
		if (tgt_stat != Stats::AC)
			return false;
		break;
	case ItemType::SHIELD:
		if (tgt_stat != Stats::AC)
			return false;
		break;
	case ItemType::RING:
		if (tgt_stat != Stats::AC && tgt_stat != Stats::STR && tgt_stat != Stats::CON
			&& tgt_stat != Stats::WIS && tgt_stat != Stats::CHA)
			return false;
		break;
	case ItemType::BELT:
		if (tgt_stat != Stats::CON && tgt_stat != Stats::STR)
			return false;
		break;
	case ItemType::BOOTS:
		if (tgt_stat != Stats::AC && tgt_stat != Stats::DEX)
			return false;
		break;
	case ItemType::WEAPON:
		if (tgt_stat != Stats::ATK && tgt_stat != Stats::DMG)
			return false;
		break;
	default:
		break;
	}
	return true;
}


//! generates a random, valid _enchantant for the item with the specified value
//! @param value : value of new _enchantant
//! @return : new, valid _enchantant
Enchant Item::RandomEnch(int value) {
	bool valid_creation = false;
	while (!valid_creation)	{
		int stat_select = rand() % 9 + 1;
		Stats selected;
		switch (stat_select) {
		case 1:
			selected = Stats::STR;
			break;
		case 2:
			selected = Stats::DEX;
			break;
		case 3:
			selected = Stats::CON;
			break;
		case 4:
			selected = Stats::INT;
			break;
		case 5:
			selected = Stats::WIS;
			break;
		case 6:
			selected = Stats::CHA;
			break;
		case 7:
			selected = Stats::AC;
			break;
		case 8:
			selected = Stats::ATK;
			break;
		case 9:
			selected = Stats::DMG;
			break;
		}
		valid_creation = validEnch(this->_type, selected);
		if (valid_creation)
			return Enchant(selected, value);
	}
}

//! rescale items to desired level
//! @param tgt_lvl : level to rescale to
void Item::rescale(int tgt_lvl) {
	this->clearEnch();
	// one new +5 _enchantant for every 5 levels
	int no_fullEnch = tgt_lvl / 5;
	// mod 5 of lvl for last _enchantant's value
	int last__enchant = tgt_lvl % 5;
	if (no_fullEnch > 0) {
		for (int i = 0; i < no_fullEnch; i++) {
			Enchant tempE = this->RandomEnch(5);
			this->addEnch(&tempE);
		}
	}
	if (last__enchant != 0)	{
		Enchant tempE2 = this->RandomEnch(last__enchant);
		this->addEnch(&tempE2);
	}
}

std::ostream& operator<<(std::ostream& op, Item it) {
	op << it.getName() << ", [" << it.getType() << "] " << std::endl;

	for (int i = 0; i < it.getEnch().size(); i++)
	{
		op << it.getEnch()[i];
	}

	return op;
}
