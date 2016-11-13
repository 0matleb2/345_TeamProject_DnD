//! @file
//! @brief Implementation of Item class
//!
#include "Item.h"


//! default constructor
Item::Item() : name("Default"), type(ItemType::OTHER), ench(std::vector<Enchant*>())
{

}

//! parametrized constructor accepting a std::string for item name, enum for type, and a vector of Enchants
//! @param nm : name of Item
//! @param tp : type of Item
//! @param nv : vector of Enchants
Item::Item(std::string nm, ItemType tp, std::vector<Enchant*> nv) : name(nm), type(tp), ench(nv)
{

}

//! copy constructor
//! @param orig : original Item to be copied
Item::Item(const Item& orig) : name(orig.name), type(orig.type), ench(orig.ench)
{

}

//! accessor for name
//! @return : Item's name
std::string Item::getName()
{
	return name;
}

//! accessor for item type
//! @return : category of item
ItemType Item::getType()
{
	return type;
}

//! accessor for Enchant std::vector
//! @return : std::vector of Item's Enchants
std::vector<Enchant*> Item::getEnch()
{
	return ench;
}

//! mutator for name
//! @param nn : new name to set
void Item::setName(std::string nn)
{
	name = nn;
}

//! mutator for type
//! @param itp : new item type
void Item::setType(ItemType itp)
{
	type = itp;
}

//! mutator for Item's set of Enchants
//! @param ech : Enchant to add
void Item::setEnch(std::vector<Enchant*> ech)
{
	ench = ech;
}

//! check validity of Item
//! @return False if Item posesses an Enchant it is not allowed to have
bool Item::isValid()
{
	// items without enchants are valid
	if (ench.size() == 0)
		return true;

	for (int i = 0; i < ench.size(); i++)
	{
		// check for less than 1
		if (ench[i]->getValue() < 1)
			return false;

		// check for bonus more than 5
		if (ench[i]->getValue() > 5)
			return false;

		// check if each item type lines up with enhanced stat
		switch (type)
		{
		case ItemType::HELMET:
			if (ench[i]->getType() != Stats::INT && ench[i]->getType() != Stats::WIS && ench[i]->getType() != Stats::AC)
				return false;
			break;
		case ItemType::ARMOR:
			if (ench[i]->getType() != Stats::AC)
				return false;
			break;
		case ItemType::SHIELD:
			if (ench[i]->getType() != Stats::AC)
				return false;
			break;
		case ItemType::RING:
			if (ench[i]->getType() != Stats::AC && ench[i]->getType() != Stats::STR && ench[i]->getType() != Stats::CON
				&& ench[i]->getType() != Stats::WIS && ench[i]->getType() != Stats::CHA)
				return false;
			break;
		case ItemType::BELT:
			if (ench[i]->getType() != Stats::CON && ench[i]->getType() != Stats::STR)
				return false;
			break;
		case ItemType::BOOTS:
			if (ench[i]->getType() != Stats::AC && ench[i]->getType() != Stats::DEX)
				return false;
			break;
		case ItemType::WEAPON:
			if (ench[i]->getType() != Stats::ATK && ench[i]->getType() != Stats::DMG)
				return false;
			break;
		default:
			break;
		}
	}

	//valid if all tests passed
	return true;
}

//! add Enchant to item's std::vector
//! @param eh : Enchant object to add
void Item::addEnch(Enchant* eh)
{
	ench.push_back(eh);
}

//! remove Enchant object from Item's std::vector
//! @param pos : position of Enchant to remove
//! @return : removed Enchant
Enchant Item::removeEnch(int pos)
{
	Enchant* temp = ench[pos];

	ench.erase(ench.begin() + pos);

	return *temp;
}

//! destructor
Item::~Item()
{

}

//! clone method. returns a pointer to a newly-created identical object.
Item* Item::clone()
{
	return new Item(*this);
}

//! abstract print method meant to be overridden in child classes
//! decided to resort to print as I could not make it work with an operator overload
void Item::print()
{
 
}

// NEW (11/9)

//! for use in scaling method, takes an item type and stat and checks if enchant would be valid
//! @param tgt_type : item type 
//! @param tgt_stat : stat boosted
//! @return : valid or no enchant
bool Item::validEnch(ItemType tgt_type, Stats tgt_stat)
{
	switch (tgt_type)
	{
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

//! remove all enchants on object
void Item::clearEnch()
{
	ench.clear();
}

//! generates a random, valid enchant for the item with the specified value
//! @param value : value of new enchant
//! @return : new, valid enchant
Enchant Item::RandomEnch(int value)
{
	bool valid_creation = false;

	while (!valid_creation)
	{

		int stat_select = rand() % 9 + 1;

		Stats selected;

		switch (stat_select)
		{
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

		valid_creation = validEnch(this->type, selected);

		if (valid_creation)
			return Enchant(selected, value);
	}
}


//! rescale items to desired level
//! @param tgt_lvl : level to rescale to
void Item::rescale(int tgt_lvl)
{
	this->clearEnch();

	// one new +5 enchant for every 5 levels
	int no_fullEnch = tgt_lvl / 5;

	// mod 5 of lvl for last enchant's value
	int last_ench = tgt_lvl % 5;

	if (no_fullEnch > 0)
	{
		for (int i = 0; i < no_fullEnch; i++)
		{
			Enchant tempE = this->RandomEnch(5);
			this->addEnch(&tempE);
		}
	}
	if (last_ench != 0)
	{
		Enchant tempE2 = this->RandomEnch(last_ench);
		this->addEnch(&tempE2);
	}

}


std::ostream& operator<<(std::ostream& op, Item it)
{
	op << it.getName() << ", [" << it.getType() << "] " << std::endl;

	for (int i = 0; i < it.getEnch().size(); i++)
	{
		op << it.getEnch()[i];
	}

	return op;
}
