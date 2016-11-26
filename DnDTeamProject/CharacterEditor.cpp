#include <conio.h>
#include "CharacterEditor.h"
#include "ItemBuilder.h"
#include "FileIO.h"
#include "Menu.h"
#include "Dice.h"
#include "Names.h"


CharacterEditor::CharacterEditor() : _loadedCharacters(std::vector<Character*>()) {
}


CharacterEditor::~CharacterEditor() {
}

Character * CharacterEditor::getCharacter() {
	return _character;
}

void CharacterEditor::setCharacter(Character * character) {
	_character = character;
}

void CharacterEditor::newCharacter() {

	_character = new Character();

	//Initialize name
	std::string characterName;
	bool choosingRandomName = true;
	switch (menu(builderNameOptions, "What is the character's name?")) {
	case 1:
		while (choosingRandomName) {
			characterName = characterNames[Dice::roll("d" + std::to_string((characterNames.size()))) - 1];
			std::cout << "The character is named " << characterName << std::endl << std::endl;
			if (menu(yesNoOptions, "Are you happy with this character name?") == 1) {
				choosingRandomName = false;
				_character->setName(characterName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		_character->setName(getUserInputString());
		std::cout << "The character is named " << _character->getName() << "." << std::endl << std::endl;
		break;
	}

	//Intialize stats
	switch (menu(characterBuilderStatOptions, "Which attributes does " + _character->getName() + " favor most?")) {
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

	//Initialize health
	_character->setMaxHp(10 + Character::abilityScoreToModifier(_character->getConsitiution()));
	_character->setHp(_character->getMaxHp());

	system("cls");

	editCharacter();
}

void CharacterEditor::editCharacter() {
	bool editingCharacter = true;
	while (editingCharacter) {

		std::cout << _character->toString() << std::endl;
		std::cout << "Editing character..." << std::endl << std::endl;

		std::string characterName;
		bool choosingRandomName = true;
		bool equippingItems = true;
		bool storingItems = true;
		int lvl;
		switch (menu(characterEditorMenuOptions, "What part of " + _character->getName() + " do you want to edit?")) {
		case 1: //Name
			switch (menu(builderNameOptions, "What is the character's name?")) {
			case 1:
				while (choosingRandomName) {
					characterName = characterNames[Dice::roll("d" + std::to_string((characterNames.size()))) - 1];
					std::cout << "The character is named " << characterName << std::endl << std::endl;
					if (menu(yesNoOptions, "Are you happy with this character name?") == 1) {
						choosingRandomName = false;
						_character->setName(characterName);
					}
				}
				break;
			case 2:
				std::cout << "Enter a name: ";
				_character->setName(getUserInputString());
				std::cout << "The character is named " << _character->getName() << "." << std::endl << std::endl;
				break;
			}
			break;
		case 2: //Level
			std::cout << "[?] What level is " << _character->getName() << "?" << std::endl;
			std::cout << "   Level: ";
			lvl = getUserInputInteger();
			std::cout << std::endl;
			_character->setLvl(1);
			_character->setMaxHp(10 + Character::abilityScoreToModifier(_character->getConsitiution()));
			for (int i = 1; i < lvl; ++i) {
				_character->levelUp();
			}
			break;
		case 3: //Worn items
			while (equippingItems) {
				std::vector<std::string> equippedItemsMenuOptions;
				equippedItemsMenuOptions.push_back("Armor:\t\t" + (_character->getArmor() ? _character->getArmor()->toString() : ""));
				equippedItemsMenuOptions.push_back("Belt:\t\t" + (_character->getBelt() ? _character->getBelt()->toString() : ""));
				equippedItemsMenuOptions.push_back("Boots:\t\t" + (_character->getBoots() ? _character->getBoots()->toString() : ""));
				equippedItemsMenuOptions.push_back("Bracers:\t\t" + (_character->getBracers() ? _character->getBracers()->toString() : ""));
				equippedItemsMenuOptions.push_back("Helmet:\t\t" + (_character->getHelmet() ? _character->getHelmet()->toString() : ""));
				equippedItemsMenuOptions.push_back("Ring:\t\t" + (_character->getRing() ? _character->getRing()->toString() : ""));
				equippedItemsMenuOptions.push_back("Shield:\t\t" + (_character->getShield() ? _character->getShield()->toString() : ""));
				equippedItemsMenuOptions.push_back("Weapon:\t\t" + (_character->getWeapon() ? _character->getWeapon()->toString() : ""));
				equippedItemsMenuOptions.push_back("Create a new item");
				equippedItemsMenuOptions.push_back("Finished equipping items");

				ItemBuilder itemBuilder;
				std::vector<Item*> loadedItems = loadItems().getItemArchive();
				std::vector<Item*> loadedArmor, loadedBelts, loadedBoots, loadedBracers, loadedHelmets, loadedRings, loadedShields, loadedWeapons;
				std::vector<std::string> loadedArmorOptionsMenu, loadedBeltsOptionsMenu, loadedBootsOptionsMenu, loadedBracersOptionsMenu,
					loadedHelmetsOptionsMenu, loadedRingsOptionsMenu, loadedShieldsOptionsMenu, loadedWeaponsOptionsMenu;
				switch (menu(equippedItemsMenuOptions, "Equip " + _character->getName() + " with some items.")) {
				case 1: //Armor
					for (int i = 0, n = loadedItems.size(); i < n; ++i) {
						if (loadedItems[i]->getItemType() == ItemType::ARMOR)
							loadedArmor.push_back(loadedItems[i]);
					}
					if (loadedArmor.size() > 0) {
						for (int i = 0, n = loadedArmor.size(); i < n; ++i) {
							loadedArmorOptionsMenu.push_back(loadedArmor[i]->toString());
						}
						_character->setArmor(dynamic_cast<Armor*>(loadedArmor[menu(loadedArmorOptionsMenu, "Which armor do you want to equip?") - 1]));
					}
					else {
						std::cout << "There are no saved armors." << std::endl << std::endl;
					}
					break;
				case 2: //Belt
					for (int i = 0, n = loadedItems.size(); i < n; ++i) {
						if (loadedItems[i]->getItemType() == ItemType::BELT)
							loadedBelts.push_back(loadedItems[i]);
					}
					if (loadedBelts.size() > 0) {
						for (int i = 0, n = loadedBelts.size(); i < n; ++i) {
							loadedBeltsOptionsMenu.push_back(loadedBelts[i]->toString());
						}
						_character->setBelt(dynamic_cast<Belt*>(loadedBelts[menu(loadedBeltsOptionsMenu, "Which belt do you want to equip?") - 1]));
					}
					else {
						std::cout << "There are no saved belts." << std::endl << std::endl;
					}
					break;
				case 3: //Boots
					for (int i = 0, n = loadedItems.size(); i < n; ++i) {
						if (loadedItems[i]->getItemType() == ItemType::BOOTS)
							loadedBoots.push_back(loadedItems[i]);
					}
					if (loadedBoots.size() > 0) {
						for (int i = 0, n = loadedBoots.size(); i < n; ++i) {
							loadedBootsOptionsMenu.push_back(loadedBoots[i]->toString());
						}
						_character->setBoots(dynamic_cast<Boots*>(loadedBoots[menu(loadedBootsOptionsMenu, "Which boots do you want to equip?") - 1]));
					}
					else {
						std::cout << "There are no saved boots." << std::endl << std::endl;
					}
					break;
				case 4: //Bracers
					for (int i = 0, n = loadedItems.size(); i < n; ++i) {
						if (loadedItems[i]->getItemType() == ItemType::BRACERS)
							loadedBracers.push_back(loadedItems[i]);
					}
					if (loadedBracers.size() > 0) {
						for (int i = 0, n = loadedBracers.size(); i < n; ++i) {
							loadedBracersOptionsMenu.push_back(loadedBracers[i]->toString());
						}
						_character->setBracers(dynamic_cast<Bracers*>(loadedBracers[menu(loadedBracersOptionsMenu, "Which bracers do you want to equip?") - 1]));
					}
					else {
						std::cout << "There are no saved bracers." << std::endl << std::endl;
					}
					break;
				case 5: //Helmet
					for (int i = 0, n = loadedItems.size(); i < n; ++i) {
						if (loadedItems[i]->getItemType() == ItemType::HELMET)
							loadedHelmets.push_back(loadedItems[i]);
					}
					if (loadedHelmets.size() > 0) {
						for (int i = 0, n = loadedHelmets.size(); i < n; ++i) {
							loadedHelmetsOptionsMenu.push_back(loadedHelmets[i]->toString());
						}
						_character->setHelmet(dynamic_cast<Helmet*>(loadedHelmets[menu(loadedHelmetsOptionsMenu, "Which helmet do you want to equip?") - 1]));
					}
					else {
						std::cout << "There are no saved helmets." << std::endl << std::endl;
					}
					break;
				case 6: //Ring
					for (int i = 0, n = loadedItems.size(); i < n; ++i) {
						if (loadedItems[i]->getItemType() == ItemType::RING)
							loadedRings.push_back(loadedItems[i]);
					}
					if (loadedRings.size() > 0) {
						for (int i = 0, n = loadedRings.size(); i < n; ++i) {
							loadedRingsOptionsMenu.push_back(loadedRings[i]->toString());
						}
						_character->setRing(dynamic_cast<Ring*>(loadedRings[menu(loadedRingsOptionsMenu, "Which ring do you want to equip?") - 1]));
					}
					else {
						std::cout << "There are no saved rings." << std::endl << std::endl;
					}
					break;
				case 7: //Shield
					for (int i = 0, n = loadedItems.size(); i < n; ++i) {
						if (loadedItems[i]->getItemType() == ItemType::SHIELD)
							loadedShields.push_back(loadedItems[i]);
					}
					if (loadedShields.size() > 0) {
						for (int i = 0, n = loadedShields.size(); i < n; ++i) {
							loadedShieldsOptionsMenu.push_back(loadedShields[i]->toString());
						}
						_character->setShield(dynamic_cast<Shield*>(loadedShields[menu(loadedShieldsOptionsMenu, "Which shield do you want to equip?") - 1]));
					}
					else {
						std::cout << "There are no saved shields." << std::endl << std::endl;
					}
					break;
				case 8: //Weapon
					for (int i = 0, n = loadedItems.size(); i < n; ++i) {
						if (loadedItems[i]->getItemType() == ItemType::WEAPON)
							loadedWeapons.push_back(loadedItems[i]);
					}
					if (loadedWeapons.size() > 0) {
						for (int i = 0, n = loadedWeapons.size(); i < n; ++i) {
							loadedWeaponsOptionsMenu.push_back(loadedWeapons[i]->toString());
						}
						_character->setWeapon(dynamic_cast<Weapon*>(loadedWeapons[menu(loadedWeaponsOptionsMenu, "Which weapon do you want to equip?") - 1]));
					}
					else {
						std::cout << "There are no saved weapons." << std::endl << std::endl;
					}
					break;
				case 9: //Create new item
					itemBuilder.newItem();
					break;
				case 10:
					equippingItems = false;
				}
			}
			break;
		case 4: //Inventory
			while (storingItems) {
				ItemBuilder itemBuilder;
				std::vector<Item*> loadedItems = loadItems().getItemArchive();
				std::vector<Item*> inventoryItems = _character->getInventory()->getContents();
				std::vector<std::string> loadedItemsOptionsMenu;
				std::vector<std::string> inventoryItemsOptionsMenu;
				std::cout << "[INVENTORY]\n" << _character->getInventory()->toString() << std::endl << std::endl;
				switch (menu(characterBuilderInventoryOptions, "Store some items in " + _character->getName() + "'s inventory.")) {
				case 1: //Add an item
					std::cout << "[INVENTORY]\n" << _character->getInventory()->toString() << std::endl << std::endl;
					if (loadedItems.size() > 0) {
						for (int i = 0, n = loadedItems.size(); i < n; ++i) {
							loadedItemsOptionsMenu.push_back(loadedItems[i]->toString());
						}
						_character->getInventory()->depositItem(*loadedItems[menu(loadedItemsOptionsMenu, "Which item do you want to store in " + _character->getName() + "'s inventory?") - 1]);
					}
					else {
						std::cout << "There are no saved items." << std::endl << std::endl;
					}
					break;
				case 2: //Remove an item
					std::cout << "[INVENTORY]\n" << _character->getInventory()->toString() << std::endl << std::endl;
					if (inventoryItems.size() > 0) {
						for (int i = 0, n = inventoryItems.size(); i < n; ++i) {
							inventoryItemsOptionsMenu.push_back(inventoryItems[i]->toString());
						}
						_character->getInventory()->withdrawItem(menu(inventoryItemsOptionsMenu, "Which item do you want to remove from " + _character->getName() + "'s inventory?") - 1);
					}
					else {
						std::cout << "There are no items in " << _character->getName() << "'s inventory." << std::endl << std::endl;
					}
					break;
				case 3: //Create a new item
					itemBuilder.newItem();
					break;
				case 4: //Finished
					storingItems = false;
					break;
				}
			}
			break;
		case 5: //Finished
			editingCharacter = false;
			if (_loadedCharacters.size() > 0)
				saveCharacters(_loadedCharacters);
			else
				saveCharacter(_character);
			system("cls");
			std::cout << _character->getName() << " was saved!" << std::endl << std::endl;
		}
	}
}

bool CharacterEditor::loadCharacter() {
	_loadedCharacters = loadCharacters();
	if (_loadedCharacters.size() > 0) {
		std::vector<std::string> loadedCharacterMenuOptions;
		for (int i = 0, n = _loadedCharacters.size(); i < n; ++i) {
			loadedCharacterMenuOptions.push_back(_loadedCharacters[i]->getName() + ", Level: " + std::to_string(_loadedCharacters[i]->getLvl()));
		}
		loadedCharacterMenuOptions.push_back("Cancel");
		int editIndex = menu(loadedCharacterMenuOptions, "Which character do you want to edit?") - 1;
		if (editIndex == loadedCharacterMenuOptions.size() - 1)
			return false;
		_character = _loadedCharacters[editIndex];
		return true;
	}
	else {
		std::cout << "There are no saved characters to edit!" << std::endl;
		std::cout << "Press any key to continue..." << std::endl;
		_getch();
		system("cls");
		return false;
	}
}


void CharacterEditor::rollStats(std::string firstPriority, std::string secondPriority, std::string thirdPriority) {
	int rerolls = 5;
	bool rolling = true;
	std::vector<int> stats; // { STR, DEX, CONS, INT, WISD, CHA }
	while (rolling) {
		std::cout << "Rolling character stats...\n" << std::endl;
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
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions, "Are you happy with these stats?")) {
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




void CharacterEditor::rollStats() {
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
			std::vector<std::string> rerollOptions;
			rerollOptions.push_back("Yes");
			rerollOptions.push_back("No (" + std::to_string(rerolls) + " rerolls remaining)");
			switch (menu(rerollOptions, "Are you happy with these stats?")) {
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