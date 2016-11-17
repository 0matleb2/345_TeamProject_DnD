#pragma once
#include "Character.h"


class CharacterBuilder {


public:

	CharacterBuilder();
	~CharacterBuilder();

	Character* getCharacter();

	void setCharacter(Character* character);

	void construct();


private:

	Character* _character;

	void buildIdentity();
	void buildStats();
	void buildEquippedItems();
	void buildInventory();

	void rollStats(std::string firstPriority, std::string secondPriority, std::string thirdPriority);
	void rollStats();

};


