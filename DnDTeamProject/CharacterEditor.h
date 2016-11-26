#pragma once
#include "Character.h"


class CharacterEditor {

public:

	CharacterEditor();
	~CharacterEditor();

	Character* getCharacter();

	void setCharacter(Character* character);

	void newCharacter();

	void editCharacter();
	bool loadCharacter();

	void rollStats(std::string firstPriority, std::string secondPriority, std::string thirdPriority);

	void rollStats();


private:

	Character* _character;
	std::vector<Character*> _loadedCharacters;

};

