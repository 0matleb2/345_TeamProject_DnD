#include "CharacterObserver.h"
#include <iostream>

//! constructor
//! @param chara: Character object that will attach a CharacterObserver to it
CharacterObserver::CharacterObserver(Character* character) {
	_subject = character;
	_subject->attach(this);
}

//! destructor
CharacterObserver::~CharacterObserver() {
}

//! prints a character sheet with every update (called upon by the notify() function from Observable.cpp)
void CharacterObserver::update() {
	_subject->printStat();
}