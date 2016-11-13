//! @file
//! @brief Header file for Character as map element
//!
//! this represents a character as a map element, has a pointer to a character and its coordinates
#pragma once

#include "Character.h"



class MapCharacter {

public:

	MapCharacter();
	MapCharacter(int x, int y, Character* ele, char sym);
	~MapCharacter();

		
	int getX();
	int getY();
	char getSymbol();
	Character* getCharacter();


	void setCharacter(Character*);
	void setX(int);
	void setY(int);
	void setSymbol(char);

	void rescale(int targetLvl);
	void print();


private:

	int _x;
	int _y;
	Character* _character;
	char _symbol;

	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _x;
		ar & _y;
		ar & _character;
		ar & _symbol;
	}

};