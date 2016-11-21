#pragma once
#include "Observer.h"
#include "Character.h"
#include "Map.h"



class CharacterObserver : public Observer {
	
	public:

		CharacterObserver(Character* model, Map* context);
		~CharacterObserver();

		void update();

	private:
		
		Character* _model;
		Map* _context;

};

