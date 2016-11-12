//! @file
//! @brief Implementation file for character as map character
//!
//! This object represents a character as a map character, it contains the characters coordinates and a pointer to the object itself

#include "MapCharacter.h"



MapCharacter::MapCharacter() : _x(0), _y(0), _character(&Character()) {
}

MapCharacter::MapCharacter(int x, int y, Character* ele, char sym) : _x(x), _y(y), _character(ele), _symbol(sym) {
}

MapCharacter::~MapCharacter() {
}


//Accessors
int MapCharacter::getX() {
	return _x;
}

int MapCharacter::getY() {
	return _y;
}

char MapCharacter::getSymbol() {
	return _symbol;
}

Character* MapCharacter::getCharacter() {
	return _character;
}


//Mutators
void MapCharacter::setX(int x) {
	_x = x;
}

void MapCharacter::setY(int y) {
	_y = y;
}

void MapCharacter::setSymbol(char symbol) {
	_symbol = symbol;
}

void MapCharacter::setCharacter(Character* ele) {
	_character = ele;
}



void MapCharacter::rescale(int targetLvl) {
	_character->rescale(targetLvl);
}

void MapCharacter::print() {
	cout << "Character _character at position: (" << _x << ", " << _y << ")" << endl;
	cout << "Details:" << endl;
	_character->printStats();
}