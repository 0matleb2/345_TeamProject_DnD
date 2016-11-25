#pragma once
#include "Character.h"


class CharacterEditor {

public:

	CharacterEditor();
	~CharacterEditor();

	Character* getCharacter();

	void setCharacter(Character* character);

	void editCharacter();
	void loadCharacter();
	void deleteCharacter();


private:

	Character* _character;
	std::vector<Character*> _loadedCharacters;

};

