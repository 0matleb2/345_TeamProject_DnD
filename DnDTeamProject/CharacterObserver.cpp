#include "CharacterObserver.h"
#include <iostream>

//! constructor
//! @param chara: Character object that will attach a CharacterObserver to it
CharacterObserver::CharacterObserver(Character* chara) {
	subject = chara;
	subject->attach(this);
}

//! destructor
CharacterObserver::~CharacterObserver() {
	subject->detach(this);
	subject = NULL;
}

//! prints a character sheet with every update (called upon by the notify() function from Observable.cpp)
void CharacterObserver::update() {
		subject->printStats();
		
}