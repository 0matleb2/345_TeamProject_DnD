#include <iostream>
#include <limits>
#include "CharacterBuilder.h"
#include "Names.h"
#include "Dice.h"
#include "Menu.h"








CharacterBuilder::CharacterBuilder() {
}


CharacterBuilder::~CharacterBuilder() {
}



//Accessors
Character* CharacterBuilder::getCharacter() {
	return _character;
}



//Mutators
void CharacterBuilder::setCharacter(Character * character) {
	_character = character;
}




void CharacterBuilder::construct() {
	std::cout << "Creating a new character..." << std::endl << std::endl;
	_character = new Character();
	buildIdentity();
	buildStats();
	buildEquippedItems();
	buildInventory();
}



void CharacterBuilder::buildIdentity() {
	std::cout << "What is the character's name?" << std::endl;
	switch (menu(characterBuilderNameOptions)) {
	case 1:
		_character->setName(characterNames[Dice::roll("d" + std::to_string(characterNames.size()))]);
		std::cout << "The character is named " << _character->getName() << "." << std::endl << std::endl;
		break;
	case 2:
		std::cout << "Enter a name: ";
		_character->setName(getUserInputString());
		std::cout << "The character is named " << _character->getName() << "." << std::endl << std::endl;
		break;
	}
}



void CharacterBuilder::buildStats() {
	std::cout << "Which attributes does the character favor most?" << std::endl;
	switch (menu(characterBuilderStatOptions)) {
	case 1:
		rollStats();
		break;
	case 2:
		rollStats("Strength", "Constitution", "Dexterity");
		break;
	case 3:
		rollStats("Strength", "Dexterity", "Constitution");
		break;
	case 4:
		rollStats("Dexterity", "Strength", "Constitution");
		break;
	case 5:
		rollStats("Dexterity", "Constitution", "Strength");
		break;
	case 6:
		rollStats("Constitution", "Dexterity", "Strength");
		break;
	case 7:
		rollStats("Constitution", "Strength", "Dexterity");
		break;
	}

	std::cout << "What level is the character?" << std::endl;
	int lvl = getUserInputInteger();
	for (int i = 1; i < lvl; ++i) {
		_character->levelUp();
	}

	//LEFT OFF HERE, TODO NEXT: Item Builder, Custom Item datafile.
}



void CharacterBuilder::buildEquippedItems() {

}



void CharacterBuilder::buildInventory() {

}



void CharacterBuilder::rollStats(std::string firstPriority, std::string secondPriority, std::string thirdPriority) {
	int rerolls = 5;
	bool rolling = true;
	std::vector<int> stats; // { STR, DEX, CONS, INT, WISD, CHA }
	while (rolling) {
		std::cout << "Rolling stats...\n" << std::endl;
		std::map<std::string, int> statIndexes = {
			{ "Strength", 0 },{ "Dexterity", 1 },{ "Constitution", 2 },{ "Intelligence", 3 },{ "Wisdom", 4 },{ "Charisma", 5 },
		};

		for (int i = 0; i < 6; ++i) {
			stats.push_back(0);
		}
		std::vector<int> rolls;
		for (int i = 0; i < 6; ++i) {
			rolls.push_back(Dice::roll("(3)4d6"));
		}
		std::sort(rolls.begin(), rolls.end()); // low-high
		stats[statIndexes[firstPriority]] = rolls[5];
		stats[statIndexes[secondPriority]] = rolls[4];
		stats[statIndexes[thirdPriority]] = rolls[3];
		rolls.resize(3);
		for (int i = 0; i < 6; ++i) {
			if (stats[i] == 0) {
				int randomIndex = Dice::roll("d" + std::to_string(rolls.size())) - 1;
				stats[i] = rolls[randomIndex];
				rolls.erase(rolls.begin() + randomIndex);
			}
		}
		std::cout << "Strength:\t" << stats[0] << "\tDexterity:\t" << stats[1] << "\nConstitution:\t" << stats[2]
			<< "\tIntelligence:\t" << stats[3] << "\nWisdom:\t\t" << stats[4] << "\tCharisma:\t" << stats[5] << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with these stats?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}
	_character->setStrength(stats[0]);
	_character->setDexterity(stats[1]);
	_character->setConsitiution(stats[2]);
	_character->setIntelligence(stats[3]);
	_character->setWisdom(stats[4]);
	_character->setCharisma(stats[5]);
}




void CharacterBuilder::rollStats() {
	int rerolls = 5;
	bool rolling = true;
	std::vector<int> stats;
	while (rolling) {
		std::cout << "Rolling stats...\n" << std::endl;
		stats.clear();
		for (int i = 0; i < 6; ++i) {
			stats.push_back(Dice::roll("(3)4d6"));
		}
		std::cout << "Strength:\t" << stats[0] << "\tDexterity:\t" << stats[1] << "\nConstitution:\t" << stats[2]
			<< "\tIntelligence:\t" << stats[3] << "\nWisdom:\t\t" << stats[4] << "\tCharisma:\t" << stats[5] << std::endl << std::endl;
		if (rerolls > 0) {
			std::cout << "Are you happy with these stats?" << std::endl;
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions)) {
			case 1:
				rolling = false;
				break;
			case 2:
				--rerolls;
				break;
			}
		}
		else {
			rolling = false;
		}
	}
	_character->setStrength(stats[0]);
	_character->setDexterity(stats[1]);
	_character->setConsitiution(stats[2]);
	_character->setIntelligence(stats[3]);
	_character->setWisdom(stats[4]);
	_character->setCharisma(stats[5]);
}

