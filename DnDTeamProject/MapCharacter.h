//! @file
//! @brief Header file for Character as map element
//!
//! this represents a character as a map element, has a pointer to a character and its coordinates
#pragma once

#include "Character.h"

using namespace std;

class MapCharacter
{
public:
	// default constructor
	MapCharacter();
	// parametrized constructor
	MapCharacter(int x, int y, Character* ele, char sym);
	// destructor
	~MapCharacter();
	// return character
	Character* getElement();
	// set character
	void setElement(Character* ele);
	// get width index
	int getX();
	// get height index
	int getY();
	// set width index
	void setX(int x);
	// set height index
	void setY(int y);
	// rescale element to desired level
	void rescale(int tgt_lvl);
	// print character's details
	void print();

	char getSymbol();

	void setSymbol(char ns);

	// serialization
	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar & x_pos;
		ar & y_pos;
		ar & element;
		ar & symbol;
	}

private:
	// x position of element
	int x_pos;
	// y position of element
	int y_pos;
	// element itself
	Character* element;
	//symbol representing element
	char symbol;
};