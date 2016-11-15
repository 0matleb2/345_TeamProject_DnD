//! @file
//! @brief Implementation of Item class
//!
#include "Item.h"


Item::Item() : _name("Default"), _type(ItemType::OTHER), _enchants(std::vector<Enchant*>()) {
}

//! parametrized constructor accepting a std::string for item _name, enum for _type, and a std::vector of Enchants
//! @param nm : _name of Item
//! @param tp : _type of Item
//! @param nv : std::vector of Enchants
Item::Item(std::string nm, ItemType tp, std::vector<Enchant*> nv) : _name(nm), _type(tp), _enchants(nv) {
}

Item::Item(const Item& orig) : _name(orig._name), _type(orig._type), _enchants(orig._enchants){
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

std::vector<Enchant*> Item::getEnchants() {
	return _enchants;
}



//Mutators
void Item::setName(std::string nn) {
	_name = nn;
}

void Item::setType(ItemType itp) {
	_type = itp;
}

void Item::addEnchant(Enchant* enchant) {

	// If the enchant stat is applicable to the item type
	if ((_type == ItemType::HELMET &&
		(enchant->getType() == Stat::INT || enchant->getType() != Stat::WIS || enchant->getType() == Stat::AC))
		|| (_type == ItemType::ARMOR &&
		(enchant->getType() == Stat::AC))
		|| (_type == ItemType::SHIELD &&
		(enchant->getType() == Stat::AC))
		|| (_type == ItemType::RING &&
		(enchant->getType() == Stat::AC || enchant->getType() == Stat::STR || enchant->getType() == Stat::CON || enchant->getType() == Stat::WIS || enchant->getType() == Stat::CHA))
		|| (_type == ItemType::BELT &&
		(enchant->getType() == Stat::CON || enchant->getType() == Stat::STR))
		|| (_type == ItemType::BOOTS &&
		(enchant->getType() == Stat::AC || enchant->getType() == Stat::DEX))
		|| (_type == ItemType::WEAPON &&
		(enchant->getType() == Stat::ATK || enchant->getType() == Stat::DMG))) {

		for (int i = 0, n = _enchants.size(); i < n; ++i) {
			if (_enchants[i]->getType() == enchant->getType()) {
				std::cout << "Cannot add enchant. Item is already enchanted with an enchant of that type!" << std::endl;
				return;
			}
		}
		_enchants.push_back(enchant);
	}
}
			

void Item::removeEnchant(Stat enchantType) {
	for (int i = 0, n = _enchants.size(); i < n; ++i) {
		if (_enchants[i]->getType() == enchantType) {
			_enchants.erase(_enchants.begin() + i);
		}
	}
}





//! abstract print method meant to be overridden in child classes
//! decided to resort to print as I could not make it work with an operator overload
void Item::print() { 
}

//! for use in scaling method, takes an item _type and stat and checks if _enchantsant would be valid
//! @param tgt__type : item _type 
//! @param tgt_stat : stat boosted
//! @return : valid or no _enchantsant
bool Item::validEnch(ItemType tgt__type, Stat tgt_stat) {
	switch (tgt__type) {
	case ItemType::HELMET:
		if (tgt_stat != Stat::WIS && tgt_stat != Stat::INT && tgt_stat != Stat::AC)
			return false;
		break;
	case ItemType::ARMOR:
		if (tgt_stat != Stat::AC)
			return false;
		break;
	case ItemType::SHIELD:
		if (tgt_stat != Stat::AC)
			return false;
		break;
	case ItemType::RING:
		if (tgt_stat != Stat::AC && tgt_stat != Stat::STR && tgt_stat != Stat::CON
			&& tgt_stat != Stat::WIS && tgt_stat != Stat::CHA)
			return false;
		break;
	case ItemType::BELT:
		if (tgt_stat != Stat::CON && tgt_stat != Stat::STR)
			return false;
		break;
	case ItemType::BOOTS:
		if (tgt_stat != Stat::AC && tgt_stat != Stat::DEX)
			return false;
		break;
	case ItemType::WEAPON:
		if (tgt_stat != Stat::ATK && tgt_stat != Stat::DMG)
			return false;
		break;
	default:
		break;
	}
	return true;
}


//! generates a random, valid _enchantsant for the item with the specified value
//! @param value : value of new _enchantsant
//! @return : new, valid _enchantsant
Enchant Item::RandomEnch(int value) {
	bool valid_creation = false;
	while (!valid_creation)	{
		int stat_select = rand() % 9 + 1;
		Stat selected;
		switch (stat_select) {
		case 1:
			selected = Stat::STR;
			break;
		case 2:
			selected = Stat::DEX;
			break;
		case 3:
			selected = Stat::CON;
			break;
		case 4:
			selected = Stat::INT;
			break;
		case 5:
			selected = Stat::WIS;
			break;
		case 6:
			selected = Stat::CHA;
			break;
		case 7:
			selected = Stat::AC;
			break;
		case 8:
			selected = Stat::ATK;
			break;
		case 9:
			selected = Stat::DMG;
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
	_enchants.clear();
	// one new +5 _enchantsant for every 5 levels
	int no_fullEnch = tgt_lvl / 5;
	// mod 5 of lvl for last _enchantsant's value
	int last__enchants = tgt_lvl % 5;
	if (no_fullEnch > 0) {
		for (int i = 0; i < no_fullEnch; i++) {
			Enchant tempE = this->RandomEnch(5);
			this->addEnchant(&tempE);
		}
	}
	if (last__enchants != 0)	{
		Enchant tempE2 = this->RandomEnch(last__enchants);
		this->addEnchant(&tempE2);
	}
}

std::ostream& operator<<(std::ostream& op, Item it) {
	op << it.getName() << ", [" << it.getType() << "] " << std::endl;
	for (int i = 0, n = it.getEnchants().size(); i < n; i++) {
		op << it.getEnchants()[i];
	}
	return op;
}
