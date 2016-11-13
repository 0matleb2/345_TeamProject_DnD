#pragma once

#include "Observer.h"
#include "Character.h"

class CharacterObserver: public Observer {

	public:

		CharacterObserver(Character* character);
		~CharacterObserver();

		void update();

	private:

		Character* _subject;
};