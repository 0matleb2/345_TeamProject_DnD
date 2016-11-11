//! @file
//! @brief Implementation file for character as map element
//!
//! This object represents a character as a map element, it contains the elements coordinates and a pointer to the object itself

#include "MapCharacter.h"

//! default constructor
MapCharacter::MapCharacter() : x_pos(0), y_pos(0), element(new Character())
{

}

//! parametrized constructor
//! @param x : width index
//! @param y : height index
//! @param ele : pointer to character object
MapCharacter::MapCharacter(int x, int y, Character* ele, char sym) : x_pos(x), y_pos(y), element(ele), symbol(sym)
{

}

//! destructor
MapCharacter::~MapCharacter()
{
	//delete element;
}

//! accessor for character proper
//! @return character itself
Character* MapCharacter::getElement()
{
	return element;
}

//! mutator for contained character
//! @param ele : new character to set
void MapCharacter::setElement(Character* ele)
{
	element = ele;
}

//! accessor for width index
//! @return element's width index
int MapCharacter::getX()
{
	return x_pos;
}

//! mutator for width index
//! @param x : new width index
void MapCharacter::setX(int x)
{
	x_pos = x;
}

//! accessor for height index
//! @return element's height index
int MapCharacter::getY()
{
	return y_pos;
}

//! mutator for height index
//! @param y : new height index
void MapCharacter::setY(int y)
{
	y_pos = y;
}

char MapCharacter::getSymbol()
{
	return symbol;
}

void MapCharacter::setSymbol(char ns)
{
	symbol = ns;
}

//! rescale character to desired level
//! @param tgt_lvl : target level to rescale to
void MapCharacter::rescale(int tgt_lvl)
{
	element->rescale(tgt_lvl);
}

//! print character and position
void MapCharacter::print()
{
	cout << "Character element at position: (" << x_pos << ", " << y_pos << ")" << endl;
	cout << "Details:" << endl;
	element->printStats();
}