//! @file
//! @brief Header File for Item class
//!
//! This class handles items. Items have a name, a type, and a number of Enchants, implemented through a vector.
//! I chose to use string as it is suitable for a name, and vector as it is an array of adjustable size that permits random access.
//! Class also has a method to check if the item in question has a legal Enchant. This class is not meant to be initialized
//! the Equipment and Weapon classes are meant to be concrete
#ifndef Item_h
#define Item_h

#include <iostream>
#include <string>
#include <vector>

#include "Enums.h"

#include "Enchant.h"

#include <boost\serialization\vector.hpp>

using namespace std;

//! class for the implementation of items
class Item
{
public:
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar & name;
		ar & type;
		ar & ench;
	}

	// default constructor
	Item();
	// parametrized constructor
	Item(string nm, itemType tp, vector<Enchant*> nv);

	//copy constructor
	Item(const Item& orig);
	// accessor for name
	string getName();
	// accessor for item category
	itemType getType();
	// accessor for list of enchants
	vector<Enchant*> getEnch();
	// mutator for name
	void setName(string nn);
	// mutator for type
	void setType(itemType itp);
	//adds an Enchant to the Item
	void setEnch(vector<Enchant*> ech);
	// checks validity of Item
	bool isValid();
	
	// NEW (11/9)
	
	// compares itemtype and enhanced stat for validity
	bool validEnch(itemType tgt_type, stats tgt_stat);
	// remove all enchants from item
	void clearEnch();
	// generates a random valid enchant for an item
	Enchant RandomEnch(int value);
	// rescale items to desired level
	void rescale(int tgt_lvl);


	//add Enchant to existing vector
	void addEnch(Enchant* eh);
	//remove enchant from vector, by position
	Enchant removeEnch(int pos);
	// returns pointer to identical item
	virtual Item* clone();

	// print item description, implemented in Equipment and Weapon classes
	virtual void print();

	// destructor
	virtual ~Item();

	friend ostream& operator<<(ostream& op, Item it);

private:
	string name;
	itemType type;
	vector<Enchant*> ench;
};

#endif