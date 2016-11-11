#pragma once

#include "Observer.h"
#include "Character.h"

class CharacterObserver: public Observer {
	public:
		CharacterObserver(Character* chara);
		virtual ~CharacterObserver();
		virtual void update();

	private:
		Character* subject;
};