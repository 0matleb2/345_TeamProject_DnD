#include <algorithm>    // std::sort
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "CharacterObserver.h"
#include "Dice.h"
#include "Equipment.h"
#include "Item.h"
#include "ItemContainer.h"
#include "Map.h"
#include "MapObserver.h"
#include "Weapon.h"


void main_menu();
void start_game();
void creator_mode();

//std::vectors holding "saved" objects

std::vector<Map> savedMaps;

std::vector<ItemContainer*> savedContainers;

std::vector<Character*> savedCharacters;




// std::vectors for characters
static std::vector<Character*> player_characters, hostile_characters, friendly_characters;

//character creation & editing
void characterMakerMainMenu();
void playable_character_creation(std::vector<Character*>& playableCharacters);
void npc_creation(std::vector<Character*>& nonPlayerCharacters, bool friendly);
void displayAllCharacters(std::vector<Character*>& characterList);
void displayDetailedInfo(std::vector<Character*>& characterList, int index);
void displayCharacterDetails(std::vector<Character*>& characterList);
void enemy_npc_creation(std::vector<Character*>& hostileCharacters);
void friendly_npc_creation(std::vector<Character*>& friendlyCharacters);
void editCharacterAtIndex(std::vector<Character*>& characterList, bool hasPlayerCharaValidationCond);
void deleteCharacterAtIndex(std::vector<Character*>& characterList);
void character_edit_mode(std::vector<Character*>& characterList, std::string characterTypeCap, std::string characterType, bool hasPlayerCharaValidationCond);
void characterMakerMainMenu(std::vector<Character*>& playableCharacters, std::vector<Character*>& hostileCharacters, std::vector<Character*>& friendlyCharacters);

//item creation & editing
void itemMakerMenu();
void itemCreator();
void itemEditor();
void itemContainerCreator();
void itemContainerEditor();
void EnchantAdd(Item* ic);

void editEquipment(std::vector<Equipment*>& equipmentList, std::string equipmentTypeC, std::string equipmentType);
void editWeapons(std::vector<Weapon*>& weaponList, std::string WeaponTypeC, std::string WeaponType, bool isMelee);
void editEnchantments_e(std::vector<Equipment*>& equipmentList, int index);
void editEnchantments_w(std::vector<Weapon*>& equipmentList, int index);

//static std::vector storing items
static std::vector<Weapon*> rangedWeaponList;
static std::vector<Weapon*> meleeWeaponList;
static std::vector<Equipment*> armorList;
static std::vector<Equipment*> shieldList;
static std::vector<Equipment*> helmetList;
static std::vector<Equipment*> ringList;
static std::vector<Equipment*> bootsList;
static std::vector<Equipment*> beltList;
static std::vector<Item*> otherItemList;
static std::vector<ItemContainer*> itemContainerList;
void equipmentList_display(std::vector<Equipment*>& equipmentType, std::string equipmentTypeNameC, std::string equipmentTypeName);
void weaponList_display(bool isMelee);
void itemContainerList_display();

//map creation
void mapMakerMenu();
void mapCreator();
void mapAddObjects(Map& m, int width, int height);
void mapDoorEditor(Map& m, int width, int height);

// used during game play
void mapMode(Map& m, Character* c);
void examineMode(Map& m);
void characterMode(Character* c);



/*
int main() {
	main_menu();
	return 0;
}
*/



void main_menu() {
	int selection;
	while (true) {
		std::cout << "====================" << std::endl;
		std::cout << "DUNGEONS AND DRAGONS" << std::endl;
		std::cout << "====================" << std::endl;
		std::cout << "1. PLAY GAME" << std::endl;
		std::cout << "2. CREATOR MODE" << std::endl;
		std::cout << "3. EXIT" << std::endl;

		std::cin >> selection;
		switch (selection) {
		case 1:
			start_game();
			break;
		case 2:
			creator_mode();
			break;
		case 3:
			std::cout << "Goodbye" << std::endl;
			return;
		default:
			std::cout << "Invalid command. Please enter a number from 1 to 3." << std::endl;
			std::cin.clear();
			fflush(stdin);
			break;
		}
	}
}


void start_game() {
	std::cout << "Please select your character (select by index):" << std::endl;
	for (int i = 0; i < savedMaps.size(); i++) {
		std::cout << "Player Charcter #" << i << std::endl;
		player_characters[i]->printStats();
		std::cout << std::endl;
	}
	int playerCharacChoice;
	bool validPCCHoice = false;
	while (!validPCCHoice) {
		std::cin >> playerCharacChoice;
		if ((playerCharacChoice < 0) || (playerCharacChoice > (player_characters.size() + 1))) {
			std::cout << "Invalid choice." << std::endl;
			std::cin.clear();
			fflush(stdin);
		}
		else break;
	}

	std::cout << "Please choose one of the maps below (select by index):" << std::endl;
	for (int i = 0; i < savedMaps.size(); i++) {
		std::cout << i << ". Map #" << (i + 1) << ":" << std::endl;
		savedMaps[i].Map::displayGrid();
	}
	int mapChoice;
	bool validMapChoice = false;
	while (!validMapChoice) {
		std::cin >> mapChoice;
		if ((mapChoice < 0) || (mapChoice > (savedMaps.size() + 1))) {
			std::cout << "Invalid choice." << std::endl;
			std::cin.clear();
			fflush(stdin);
		}
		else break;
	}
	mapMode(savedMaps[mapChoice], player_characters[playerCharacChoice]);
}

void creator_mode() {
	int choice;
	while (true) {
		std::cout << "==================================" << std::endl;
		std::cout << "DUNGEONS AND DRAGONS: CREATOR MODE" << std::endl;
		std::cout << "==================================" << std::endl;
		std::cout << "1. Character Maker" << std::endl;
		std::cout << "2. Item Maker" << std::endl;
		std::cout << "3. Map Maker" << std::endl;
		std::cout << "4. Return to main menu" << std::endl;

		std::cin >> choice;

		switch (choice) {
		case 1:
			characterMakerMainMenu(player_characters, hostile_characters, friendly_characters);
			break;
		case 2:
			itemMakerMenu();
			break;
		case 3:
			mapMakerMenu();
			break;
		case 4:
			std::cout << "Returning to main menu..." << std::endl;
			return;
			break;
		case 5:
			std::cout << "Invalid choice. Please enter a number from 1 to 4." << std::endl;
			std::cin.clear();
			fflush(stdin);
			break;
		}
		std::cin.clear();
		fflush(stdin);
	}
}









void mapMode(Map& m, Character* c)
{
	// attach observer to map
	MapObserver mapObs(&m);

	// attach observer to player character
	CharacterObserver charObs(c);

	// rescale map to player character's level
	m.rescale(c->getLevel());

	// add player to map
	m.addPC(c);

	bool exitMenu = false;

	while (!exitMenu)
	{
		std::cout << "Please enter an action: " << std::endl
			<< "n - move north, w - move west, e - move east, s - move south, q - exit" << std::endl
			<< "x - enter examine mode, c - enter character mode" << std::endl;

		char choice;

		std::cin >> choice;

		switch (choice)
		{
		case 'n':
			m.moveCharacter(m.getPC(), 'n');
			break;
		case 'w':
			m.moveCharacter(m.getPC(), 'w');
			break;
		case 'e':
			m.moveCharacter(m.getPC(), 'e');
			break;
		case 's':
			m.moveCharacter(m.getPC(), 's');
			break;
		case 'q':
			std::cout << "Leaving map mode." << std::endl;
			exitMenu = true;
			break;
		case 'x':
			examineMode(m);
			break;
		case 'c':
			characterMode(m.getPC()->getCharacter());
			m.notify();
			break;
		default:
			break;
		}

		if (m.exitReached())
		{
			m.setCell(m.getPC()->getX(), m.getPC()->getY(), '\\');
			std::cout << "EXIT Reached!" << std::endl;
			exitMenu = true;
		}
	}
}

void examineMode(Map& m)
{
	bool exitMenu = false;

	while (!exitMenu)
	{
		std::cout << "Examine menu: enter a character and ENTER to select an action: " << std::endl
			<< "n - examine north, s - examine south, e - examine east, w - examine west" << std::endl
			<< "q - quit examine mode" << std::endl;

		char choiceX;

		std::cin >> choiceX;

		switch (choiceX)
		{
		case 'n':
			m.examine('n');
			break;
		case 's':
			m.examine('s');
			break;
		case 'e':
			m.examine('e');
			break;
		case 'w':
			m.examine('w');
			break;
		case 'q':
			std::cout << "Leaving examine mode." << std::endl;
			exitMenu = true;
			break;
		}
	}
}

void characterMode(Character* c)
{
	bool exitMenu = false;

	c->printStats();

	while (!exitMenu)
	{
		std::cout << "Character Menu: enter a character and ENTER to select an action" << std::endl
			<< "u - unequip an item, q - quit character menu" << std::endl;

		char choiceC;

		std::cin >> choiceC;

		switch (choiceC)
		{
		case 'q':
			exitMenu = true;
			std::cout << "Leaving character screen..." << std::endl;
			system("PAUSE");
			break;
		case 'u':
			std::cout << "unavailable for now" << std::endl;
			break;
		}
	}
}














/////////////////////////////////////////////////////////
//
//
// MAP-CREATION RELATED FUNCTIONS
//
//
//
/////////////////////////////////////////////////////////

void mapMakerMenu()
{
	bool menuLoop = true;

	while (menuLoop)
	{
		std::cout << "============" << std::endl
			<< " Map Maker" << std::endl
			<< "============" << std::endl;

		std::cout << "select an option:" << std::endl
			<< "a - Map Creator, b - Map Editor, q - Quit" << std::endl;

		char choice;

		std::cin >> choice;

		switch (choice)
		{
		case 'a':
			mapCreator();
			break;
		case 'b':
			std::cout << "Unimplemented. Sorry!" << std::endl;
			break;
		case 'q':
			return;
			break;
		}
	}
}



//! map creation menu
//! has methods to place walls and floor tiles, not messing with npcs/loot, as we would need to load from file
//! the map class has methods to insert characters/containers though, so its possible
void mapCreator()
{

	bool step1 = true;

	int width;
	int height;

	char mainChoice;

	std::cout << "Map Creator" << std::endl;
	std::cout << "------------" << std::endl;
	std::cout << "p - proceed, q - quit" << std::endl;

	std::cin >> mainChoice;

	switch (mainChoice)
	{
	case 'q':
		return;
		break;
	case 'p':
		break;
	}


	while (step1)
	{

		std::cout << "please enter the map width" << std::endl
			<< "(between 3 and 20):" << std::endl;

		std::cin >> width;

		std::cout << "please enter the map height" << std::endl
			<< "(between 3 and 20)" << std::endl;

		std::cin >> height;

		std::cout << "selected width/height: " << width << ", " << height << std::endl;

		system("PAUSE");

		step1 = false;

		if (width < 3 || width > 20 || height < 3 || width > 20)
		{
			std::cout << "Invalid Selection!" << std::endl;
			step1 = true;
		}

	}

	Map cMap(width, height);

	MapObserver mObs(&cMap);

	std::cout << "CURRENT MAP" << std::endl;



	char sprite;
	bool addEle = true;

	while (addEle)
	{

		bool step2 = true;
		bool step3 = true;

		while (step2)
		{
			std::cout << "Add an element to the map?" << std::endl
				<< "w - place wall, f - place floor tile" << std::endl
				<< "q - quit" << std::endl;

			char choose;

			std::cin >> choose;

			switch (choose)
			{
			case 'w':
				sprite = '#';
				step2 = false;
				break;
			case 'f':
				sprite = '.';
				step2 = false;
				break;
			case 'q':
				step2 = false;
				step3 = false;
				addEle = false;
				break;
			}
		}

		int eleX;
		int eleY;

		while (step3)
		{
			std::cout << "Set element where?" << std::endl
				<< "Select x coordinate (starting from 0 to width - 1) : " << std::endl;

			std::cin >> eleX;

			std::cout << "Select y coordinate (y increases downwards):" << std::endl;

			std::cin >> eleY;

			if (eleX < 0 || eleX >= width || eleY < 0 || eleY >= height)
			{
				std::cout << "element out of bounds! please try again." << std::endl;
			}
			else if (eleX == cMap.getEntry()->getX() && eleY == cMap.getEntry()->getY())
			{
				std::cout << "cannot place over entrance." << std::endl;
			}
			else if (eleX == cMap.getExit()->getX() && eleY == cMap.getExit()->getY())
			{
				std::cout << "Cannot place over exit." << std::endl;
			}
			else
			{
				std::cout << "Element Added" << std::endl;
				cMap.setCell(eleX, eleY, sprite);
				system("PAUSE");
				step3 = false;
			}

		}
	}

	bool loopB = true;

	while (loopB)
	{
		std::cout << "would you like to change the location of the entrance/exit?" << std::endl
			<< "y - yes, n - no" << std::endl;

		char chEnEx;

		std::cin >> chEnEx;

		switch (chEnEx)
		{
		case 'y':
			mapDoorEditor(cMap, width, height);
			break;
		case 'n':
			loopB = false;
			break;
		}
	}


	std::cout << "Adding Characters and Containers to Map..." << std::endl;

	mapAddObjects(cMap, width, height);

	if (!cMap.validate())
	{
		std::cout << "ERROR: Invalid map. No path to exit." << std::endl;
	}
	else
	{
		std::cout << "Map successfully created" << std::endl;
		savedMaps.push_back(cMap);
		cMap.displayGrid();
	}
}

void mapAddObjects(Map& m, int width, int height)
{
	bool menuLoop = true;

	while (menuLoop)
	{
		bool addCh = false;
		bool addCo = false;

		std::cout << "What would you like to add?" << std::endl
			<< "1 - Character" << std::endl
			<< "2 - Container" << std::endl
			<< "3 - Quit" << std::endl;

		int choice;

		std::cin >> choice;

		switch (choice)
		{
		case 1:
			addCh = true;
			break;
		case 2:
			addCo = true;
			break;
		case 3:
			return;
			break;
		}

		bool addCh2 = false;
		bool addCo2 = false;

		int index;

		// add character, phase 1
		while (addCh)
		{
			if (savedCharacters.size() > 0)
			{
				std::cout << savedCharacters.size() << " saved character found." << std::endl;

				std::cout << "Select a saved character to add (index 0 to " << savedCharacters.size() - 1 << ")" << std::endl;

				std::cin >> index;

				if (index < 0 || index > savedCharacters.size() - 1)
				{
					std::cout << "Invalid index selected." << std::endl;
				}
				else
				{
					savedCharacters[index]->printStats();
					std::cout << "Do you want to add this character?" << std::endl
						<< "y - yes, n - no" << std::endl;

					char choiceA;

					std::cin >> choiceA;

					switch (choiceA)
					{
					case 'y':
						addCh = false;
						addCh2 = true;
						break;
					case 'n':
						addCh = false;
						break;
					}

				}
			}
			else
			{
				std::cout << "No saved characters to load..." << std::endl;
				addCh = false;
			}
		}

		//add container, phase 1
		while (addCo)
		{
			if (savedContainers.size() > 0)
			{
				std::cout << savedContainers.size() << " saved container found." << std::endl;

				std::cout << "Select a saved container to add (index 0 to " << savedContainers.size() - 1 << ")" << std::endl;

				std::cin >> index;

				if (index < 0 || index > savedContainers.size() - 1)
				{
					std::cout << "Invalid index selected." << std::endl;
				}
				else
				{
					savedContainers[index]->printContents();
					std::cout << "Do you want to add this container?" << std::endl
						<< "y - yes, n - no" << std::endl;

					char choiceA;

					std::cin >> choiceA;

					switch (choiceA)
					{
					case 'y':
						addCo = false;
						addCo2 = true;
						break;
					case 'n':
						addCo = false;
						break;
					}

				}
			}
			else
			{
				std::cout << "No saved containers to load..." << std::endl;
				addCo = false;
			}
		}

		// add character, phase 2
		while (addCh2)
		{
			m.displayGrid();
			std::cout << "Where would you like to add the element?" << std::endl
				<< "Set x coordinate:" << std::endl;

			int coorX;
			int coorY;

			std::cin >> coorX;

			std::cout << "Set y coordinate" << std::endl;

			std::cin >> coorY;

			if (coorX < 0 || coorY < 0 || coorX >= width || coorY >= height)
			{
				std::cout << "Out of bounds! Please select another location." << std::endl;
			}
			else
			{
				std::cout << "Adding Character..." << std::endl;
				m.addNPC(savedCharacters[index], coorX, coorY, 'N');
				addCh2 = false;
			}

		}

		// add container, phase 2
		while (addCo2)
		{
			m.displayGrid();
			std::cout << "Where would you like to add the element?" << std::endl
				<< "Set x coordinate:" << std::endl;

			int coorX;
			int coorY;

			std::cin >> coorX;

			std::cout << "Set y coordinate" << std::endl;

			std::cin >> coorY;

			if (coorX < 0 || coorY < 0 || coorX >= width || coorY >= height)
			{
				std::cout << "Out of bounds! Please select another location." << std::endl;
			}
			else
			{
				std::cout << "Adding Container..." << std::endl;
				m.addLoot(savedContainers[index], coorX, coorY, 'H');
				addCo2 = false;
			}


		}
	}
}

void mapDoorEditor(Map& m, int width, int height)
{
	bool menuLoop = true;

	while (menuLoop)
	{
		std::cout << "Edit location of Exit or Entrance?" << std::endl
			<< "n - entrance, x - exit, q - quit" << std::endl;

		char choice1;

		std::cin >> choice1;

		bool editEn = false;
		bool editEx = false;

		switch (choice1)
		{
		case 'n':
			editEn = true;
			break;
		case 'x':
			editEx = true;
			break;
		case 'q':
			menuLoop = false;
			break;
		}

		while (editEn)
		{
			m.displayGrid();

			std::cout << "Select a location for the new entrance..." << std::endl
				<< "select an x-coordinate:" << std::endl;

			int chx;

			std::cin >> chx;

			std::cout << "select a y-coordinate:" << std::endl;

			int chy;

			std::cin >> chy;

			std::cout << "Selected: " << chx << ", " << chy << std::endl;

			// index is walls of map
			if (chx == 0 || chx == width - 1 || chy == 0 || chy == height - 1)
			{
				// corner selected
				if ((chx == 0 && chy == 0) || (chx == width - 1 && chy == 0)
					|| (chx == 0 && chy == height - 1) || (chx == width - 1 && chy == height - 1))
				{
					std::cout << "Cannot place at corner" << std::endl;
				}
				else if (chx == m.getExit()->getX() && chy == m.getExit()->getY())
				{
					std::cout << "Cannot place here. Exit present." << std::endl;
				}
				else
				{
					m.setEntry(chx, chy);
					editEn = false;
				}

			}
			else
			{
				std::cout << "Entrance must be placed on the side of the map." << std::endl;
			}
		}

		while (editEx)
		{
			m.displayGrid();

			std::cout << "Select a location for the new exit..." << std::endl
				<< "select an x-coordinate:" << std::endl;

			int chx;

			std::cin >> chx;

			std::cout << "select a y-coordinate:" << std::endl;

			int chy;

			std::cin >> chy;

			std::cout << "Selected: " << chx << ", " << chy << std::endl;

			// index is walls of map
			if (chx == 0 || chx == width - 1 || chy == 0 || chy == height - 1)
			{
				// corner selected
				if ((chx == 0 && chy == 0) || (chx == width - 1 && chy == 0)
					|| (chx == 0 && chy == height - 1) || (chx == width - 1 && chy == height - 1))
				{
					std::cout << "Cannot place at corner" << std::endl;
				}
				else if (chx == m.getEntry()->getX() && chy == m.getEntry()->getY())
				{
					std::cout << "Cannot place here. Entrance present." << std::endl;
				}
				else
				{
					m.setExit(chx, chy);
					editEx = false;
				}

			}
			else
			{
				std::cout << "Entrance must be placed on the side of the map." << std::endl;
			}
		}
	}
}

















/////////////////////////////////////////////////////////
//
//
// ITEM-CREATION RELATED FUNCTIONS
//
//
//
/////////////////////////////////////////////////////////

void itemMakerMenu()
{
	bool menuLoop = true;

	while (menuLoop)
	{
		std::cout << "==========" << std::endl
			<< "Item Maker" << std::endl
			<< "==========" << std::endl;

		std::cout << "Select an option: " << std::endl
			<< "  Create/Edit" << std::endl
			<< "a - create new item, b - edit saved item," << std::endl
			<< "  Display" << std::endl
			<< "c - melee weapons list, d - ranged weapons list," << std::endl
			<< "e - armor list, f - shield list" << std::endl
			<< "g - helmet list, h - ring list" << std::endl
			<< "i - boots list, j - belt list" << std::endl
			<< "  Other" << std::endl
			<< "q - quit" << std::endl;

		char choice;

		std::cin >> choice;

		switch (choice)
		{
		case 'a':
			itemCreator();
			break;
		case 'b':
			itemEditor();
			break;
		case 'c':
			weaponList_display(true);		// isMelee = true
			break;
		case 'd':
			weaponList_display(false);		// isMelee = false
			break;
		case 'e':
			equipmentList_display(armorList, "Armor", "armor");
			break;
		case 'f':
			equipmentList_display(shieldList, "Shield", "shield");
			break;
		case 'g':
			equipmentList_display(helmetList, "Helmet", "helmet");
			break;
		case 'h':
			equipmentList_display(ringList, "Ring", "ring");
			break;
		case 'i':
			equipmentList_display(bootsList, "Boots", "boots");
			break;
		case 'j':
			equipmentList_display(beltList, "Belt", "belt");
			break;
		case 'q':
			std::cout << "Leaving Item Maker..." << std::endl;
			menuLoop = false;
			break;
		}
	}
}


std::string legalEnchants(ItemType it)
{
	switch (it)
	{
	case ItemType::HELMET:
		return "Intelligence, Wisdom, Armor Class";
		break;
	case ItemType::ARMOR:
		return "Armor Class";
		break;
	case ItemType::SHIELD:
		return "Armor Class";
		break;
	case ItemType::RING:
		return "Armor Class, Strength, Constitution, Wisdom, Charisma";
		break;
	case ItemType::BELT:
		return "Constitution, Strength";
		break;
	case ItemType::BOOTS:
		return "Armor Class, Dexterity";
		break;
	case ItemType::WEAPON:
		return "Attack Bonus, Damage Bonus";
		break;
	default:
		return "None";
		break;
	}
}

void itemCreator()
{
	bool menuLoop = true;

	while (menuLoop)
	{
		std::cout << "Item Creator" << std::endl
			<< "-------------" << std::endl;

		bool step1 = true;
		bool step2 = false;
		bool step3 = false;

		ItemType cType;
		WeaponType cSub;

		while (step1)
		{
			std::cout << "What type of item would you like to make?" << std::endl
				<< "h - helmet, s - shield, a - armor, r - ring" << std::endl
				<< "b - belt, o - boots, m - melee weapon, w - ranged weapon" << std::endl
				<< "q - quit" << std::endl;

			char choice1;

			std::cin >> choice1;

			switch (choice1)
			{
			case 'h':
				cType = ItemType::HELMET;
				std::cout << cType << " selected" << std::endl;
				step1 = false;
				step2 = true;
				break;
			case 's':
				cType = ItemType::SHIELD;
				std::cout << cType << " selected" << std::endl;
				step1 = false;
				step2 = true;
				break;
			case 'a':
				cType = ItemType::ARMOR;
				std::cout << cType << " selected" << std::endl;
				step1 = false;
				step2 = true;
				break;
			case 'r':
				cType = ItemType::RING;
				std::cout << cType << " selected" << std::endl;
				step1 = false;
				step2 = true;
				break;
			case 'b':
				cType = ItemType::BELT;
				std::cout << cType << " selected" << std::endl;
				step1 = false;
				step2 = true;
				break;
			case 'o':
				cType = ItemType::BOOTS;
				std::cout << cType << " selected" << std::endl;
				step1 = false;
				step2 = true;
				break;
			case 'm':
				cType = ItemType::WEAPON;
				cSub = WeaponType::MELEE;
				std::cout << cType << "[ " << cSub << "] " << "selected" << std::endl;
				step1 = false;
				step2 = true;
				break;
			case 'w':
				cType = ItemType::WEAPON;
				cSub = WeaponType::RANGED;
				std::cout << cType << "[ " << cSub << "] " << "selected" << std::endl;
				step1 = false;
				step2 = true;
				break;
			case 'q':
				return;
				break;
			}
		}

		std::string cName;

		while (step2)
		{
			std::cout << "Give your Item a name: " << std::endl;

			std::cin >> cName;

			char confirm;

			std::cout << "Name: " << cName << std::endl
				<< "Is this ok? y - yes, n - no" << std::endl;

			std::cin >> confirm;

			if (confirm == 'y')
				step2 = false;
		}

		Item* cItem;

		if (cType == ItemType::WEAPON)
		{
			if (cSub == WeaponType::RANGED)
				cItem = new Weapon(cName, cType, std::vector<Enchant*>(), 2, cSub);
			else
				cItem = new Weapon(cName, cType, std::vector<Enchant*>(), 0, cSub);
		}
		else
		{
			cItem = new Equipment(cName, cType, std::vector<Enchant*>());
		}

		std::cout << "Created Item: " << std::endl;
		cItem->print();
		system("PAUSE");

		bool add_enchant = true;

		while (add_enchant)
		{
			std::cout << "Would you like to add an Enchant?" << std::endl
				<< "y - yes, n - no" << std::endl;

			char choose;

			std::cin >> choose;

			if (choose == 'y')
				EnchantAdd(cItem);

			if (choose == 'n')
				add_enchant = false;

		}

		std::cout << "Created:" << std::endl;
		cItem->print();

		bool save_item = true;

		while (save_item)
		{
			std::cout << "Would you like to save this item?" << std::endl
				<< "y - yes, n - no" << std::endl;

			char save_choice;
			std::cin >> save_choice;

			if (save_choice == 'y') {
				if ((cItem->getType() == WEAPON)) {
					Weapon* cTypeWeapon = static_cast<Weapon*>(cItem);
					if ((cTypeWeapon->getRange() == 0))
						meleeWeaponList.push_back(static_cast<Weapon*>(cItem));
					else rangedWeaponList.push_back(static_cast<Weapon*>(cItem));
				}
				else if ((cItem->getType() == SHIELD))
					shieldList.push_back(static_cast<Equipment*>(cItem));
				else if ((cItem->getType() == HELMET))
					helmetList.push_back(static_cast<Equipment*>(cItem));
				else if ((cItem->getType() == ARMOR))
					armorList.push_back(static_cast<Equipment*>(cItem));
				else if ((cItem->getType() == BELT))
					beltList.push_back(static_cast<Equipment*>(cItem));
				else if ((cItem->getType() == BOOTS))
					bootsList.push_back(static_cast<Equipment*>(cItem));
				else if ((cItem->getType() == RING))
					ringList.push_back(static_cast<Equipment*>(cItem));

				std::cout << "Item has been saved." << std::endl;
				save_item = false;
			}
			if (save_choice == 'n')
				save_item = false;
		}

		system("PAUSE");
		menuLoop = false;
	}
}

void EnchantAdd(Item* ic)
{
	bool loop1 = true;

	Stats cStat;

	while (loop1)
	{
		std::cout << "Choose an enchant to add: " << std::endl
			<< "s - Strength, w - Wisdom, c - Constitution, i - Intelligence" << std::endl
			<< "d - Dexterity, h - Charisma, a - Armor Class, t - Attack Bonus" << std::endl
			<< "m - damage bonus" << std::endl
			<< "Valid Enchants for your Item: " << legalEnchants(ic->getType()) << std::endl;

		char choice;

		std::cin >> choice;

		switch (choice)
		{
		case 's':
			cStat = Stats::STR;
			loop1 = false;
			break;
		case 'w':
			cStat = Stats::WIS;
			loop1 = false;
			break;
		case 'c':
			cStat = Stats::CON;
			loop1 = false;
			break;
		case 'i':
			cStat = Stats::INT;
			loop1 = false;
			break;
		case 'd':
			cStat = Stats::DEX;
			loop1 = false;
			break;
		case 'h':
			cStat = Stats::CHA;
			loop1 = false;
			break;
		case 'a':
			cStat = Stats::AC;
			loop1 = false;
			break;
		case 't':
			cStat = Stats::ATK;
			loop1 = false;
			break;
		case 'm':
			cStat = Stats::DMG;
			loop1 = false;
			break;
		}

		if (!loop1)
		{
			if (!(ic->validEnch(ic->getType(), cStat)))
			{
				std::cout << "Invalid Enchant!" << std::endl;
				std::cin.clear();
				fflush(stdin);
				loop1 = true;
			}
		}
	}

	bool loop2 = true;

	int enVal;

	while (loop2)
	{
		std::cout << "Enter a value between 1 and 5" << std::endl;

		std::cin >> enVal;

		loop2 = false;

		if (enVal > 5 || enVal < 1)
		{
			std::cout << "Invalid value!" << std::endl;
			std::cin.clear();
			fflush(stdin);
			loop2 = true;
		}
	}

	ic->addEnch(new Enchant(cStat, enVal));
}

void itemEditor() {
	bool loopy1 = true;

	while (loopy1) {
		std::cout << "What kind of item would you like to edit?" << std::endl
			<< "h - helmet, s - shield, a - armor, r - ring" << std::endl
			<< "b - belt, o - boots, m - melee weapon, w - ranged weapon" << std::endl
			<< "q - quit" << std::endl;

		char edit_choice_1;
		int indexOfItem;

		std::cin >> edit_choice_1;

		switch (edit_choice_1) {
		case 'h':
			equipmentList_display(helmetList, "Helmet", "helmet");
			if (helmetList.size() > 0) {
				editEquipment(helmetList, "Helmet", "helmet");
			}
			break;
		case 's':
			equipmentList_display(shieldList, "Shield", "shield");
			if (shieldList.size() > 0) {
				editEquipment(shieldList, "Shield", "shield");
			}
			break;
		case 'a':
			equipmentList_display(armorList, "Armor", "armor");
			if (armorList.size() > 0) {
				editEquipment(armorList, "Armor", "armor");
			}
			break;
		case 'r':
			equipmentList_display(ringList, "Ring", "ring");
			if (ringList.size() > 0) {
				editEquipment(ringList, "Ring", "ring");
			}
			break;
		case 'b':
			equipmentList_display(beltList, "Belt", "belt");
			if (beltList.size() > 0) {
				editEquipment(beltList, "Belt", "belt");
			}
			break;
		case 'o':
			equipmentList_display(bootsList, "Boots", "boots");
			if (bootsList.size() > 0) {
				editEquipment(bootsList, "Boots", "boots");
			}
			break;
		case 'm':
			weaponList_display(true);	//isMelee = true
			if (meleeWeaponList.size() > 0) {
				editWeapons(meleeWeaponList, "Melee weapon", "melee weapon", true);
			}
			break;
		case 'w':
			weaponList_display(false);	//isMelee = false
			if (rangedWeaponList.size() > 0) {
				editWeapons(rangedWeaponList, "Ranged weapon", "ranged weapon", false);
			}
			break;
		case 'q':
			return;
			break;
		}
	}
}

void editEquipment(std::vector<Equipment*>& equipmentList, std::string equipmentTypeC, std::string equipmentType) {
	int indexOfItem;

	std::cout << "Please enter the index of the " << equipmentType << " you would like to edit.";

	std::cin >> indexOfItem;
	if ((indexOfItem < 0) || (indexOfItem >(equipmentList.size() - 1))) {
		std::cout << "Invalid item index. Please try again." << std::endl;
		std::cin.clear();
		fflush(stdin);
	}
	else {
		std::cout << "Printing " << equipmentType << " details:" << std::endl;
		equipmentList[indexOfItem]->print();
		std::cout << "What would you like to edit? Enter -1 to cancel." << std::endl;
		std::cout << "1. " << equipmentTypeC << " name" << std::endl;
		std::cout << "2. " << equipmentTypeC << " enchantments" << std::endl;

		int editChoice;
		bool noEditChoice = true;
		std::string newName;
		while (noEditChoice) {
			std::cin >> editChoice;
			switch (editChoice) {
			case 1:
				std::cout << "Please enter what you would like the item to be renamed to: ";
				std::cin >> newName;
				equipmentList[indexOfItem]->setName(newName);
				std::cout << "Item has been renamed to " << newName << "." << std::endl;
				noEditChoice = false;
				break;
			case 2:
				editEnchantments_e(equipmentList, indexOfItem);
				noEditChoice = false;
				break;
			case -1:
				return;
				break;
			default:
				std::cout << "Invalid entry. Please enter either 1 or 2." << std::endl;
				std::cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}

void editWeapons(std::vector<Weapon*>& weaponList, std::string WeaponTypeC, std::string WeaponType, bool isMelee) {
	int indexOfItem;

	std::cout << "Please enter the index of the " << WeaponType << " you would like to edit.";

	std::cin >> indexOfItem;
	if ((indexOfItem < 0) || (indexOfItem >(weaponList.size() - 1))) {
		std::cout << "Invalid item index. Please try again." << std::endl;
		std::cin.clear();
		fflush(stdin);
	}
	else {
		std::cout << "Printing " << WeaponType << " details:" << std::endl;
		weaponList[indexOfItem]->print();
		std::cout << "What would you like to edit? Enter -1 to cancel." << std::endl;
		std::cout << "1. " << WeaponTypeC << " name" << std::endl;
		std::cout << "2. " << WeaponTypeC << " enchantments" << std::endl;
		if (!isMelee)
			std::cout << "3. Weapon range." << std::endl;

		int editChoice;
		bool noEditChoice = true;
		std::string newName;
		while (noEditChoice) {
			std::cin >> editChoice;
			switch (editChoice) {
			case 1:
				std::cout << "Please enter what you would like the item to be renamed to: ";
				std::cin >> newName;
				weaponList[indexOfItem]->setName(newName);
				std::cout << "Item has been renamed to " << newName << "." << std::endl;
				noEditChoice = false;
				break;
			case 2:
				editEnchantments_w(weaponList, indexOfItem);
				noEditChoice = false;
				break;
			case -1:
				return;
				break;
			default:
				std::cout << "Invalid entry. Please enter either 1 or 2." << std::endl;
				std::cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}

void editEnchantments_e(std::vector<Equipment*>& equipmentList, int index) {
	std::cout << "Item " << equipmentList[index]->getName() << "'s list of enchants:" << std::endl;
	for (int i = 0; i < equipmentList[index]->getEnch().size(); i++) {
		std::cout << i << ". ";
		equipmentList[index]->getEnch()[i]->print();
	}
	std::cout << "Enter the index of the enchantment item \"" << equipmentList[index]->getName() << "\" has that you would like to edit." << std::endl;

	int index_of_enchant;
	int newEnchantValue;
	bool loop = true;
	while (loop) {
		std::cin >> index_of_enchant;
		if ((index_of_enchant < 0) || (index_of_enchant >(equipmentList[index]->getEnch().size() - 1))) {
			std::cout << "Invalid index, please try again." << std::endl;
			std::cin.clear();
			fflush(stdin);
		}
		else {
			equipmentList[index]->getEnch()[index_of_enchant]->print();
			std::cout << "What would you like to do? Enter -1 to cancel." << std::endl;
			std::cout << "1. Change enchant value" << std::endl;
			std::cout << "2. Remove the enchant" << std::endl;

			int enchantChoice;
			std::cin >> enchantChoice;
			switch (enchantChoice) {
			case 1:
				std::cout << "Please enter your new value for the enchant." << std::endl;
				std::cin >> newEnchantValue;
				equipmentList[index]->getEnch()[index_of_enchant]->setValue(newEnchantValue);
				std::cout << "Enchant value has been set to " << equipmentList[index]->getEnch()[index_of_enchant]->getValue() << std::endl;

				loop = false;
				break;
			case 2:
				std::cout << "Enchantment has been removed." << std::endl;
				equipmentList[index]->removeEnch(index_of_enchant);
				loop = false;
				break;
			case -1:
				return;
				break;
			default:
				std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
				std::cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}



void editEnchantments_w(std::vector<Weapon*>& weaponList, int index) {
	std::cout << "Item " << weaponList[index]->getName() << "'s list of enchants:" << std::endl;
	for (int i = 0; i < weaponList[index]->getEnch().size(); i++) {
		std::cout << i << ". ";
		weaponList[index]->getEnch()[i]->print();
	}
	std::cout << "Enter the index of the enchantment item \"" << weaponList[index]->getName() << "\" has that you would like to edit." << std::endl;

	int index_of_enchant;
	int newEnchantValue;
	bool loop = true;
	while (loop) {
		std::cin >> index_of_enchant;
		if ((index_of_enchant < 0) || (index_of_enchant >(weaponList[index]->getEnch().size() - 1))) {
			std::cout << "Invalid index, please try again." << std::endl;
			std::cin.clear();
			fflush(stdin);
		}
		else {
			weaponList[index]->getEnch()[index_of_enchant]->print();
			std::cout << "What would you like to do? Enter -1 to cancel." << std::endl;
			std::cout << "1. Change enchant value" << std::endl;
			std::cout << "2. Remove the enchant" << std::endl;

			int enchantChoice;
			std::cin >> enchantChoice;
			switch (enchantChoice) {
			case 1:
				std::cout << "Please enter your new value for the enchant." << std::endl;
				std::cin >> newEnchantValue;
				weaponList[index]->getEnch()[index_of_enchant]->setValue(newEnchantValue);
				std::cout << "Enchant value has been set to " << weaponList[index]->getEnch()[index_of_enchant]->getValue() << std::endl;

				loop = false;
				break;
			case 2:
				std::cout << "Enchantment has been removed." << std::endl;
				weaponList[index]->removeEnch(index_of_enchant);
				loop = false;
				break;
			case -1:
				return;
				break;
			default:
				std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
				std::cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}



//! function for displaying all contents of a std::vector that stores equipments of a certain type
//! @param equipmentList: the std::vector that stores equipments of a specific type
//! @param equipmentTypeC: just the name of the equipment type, capitalized (i.e. Shield, Helmet, etc)
//! @param equipmentType: just the name of the equipment type, not capitalized (i.e. shield, helmet, etc)
void equipmentList_display(std::vector<Equipment*>& equipmentList, std::string equipmentTypeC, std::string equipmentType)
{
	if (equipmentList.size() > 0)
	{
		std::cout << "Displaying stored " << equipmentType << "s: " << std::endl;
		for (int i = 0; i < equipmentList.size(); i++)
		{
			std::cout << i << ". ";
			equipmentList[i]->print();
		}
		std::cout << std::endl;
	}
	else std::cout << equipmentTypeC << " list is empty." << std::endl;
}

void weaponList_display(bool isMelee)
{
	if (isMelee)
	{
		if (meleeWeaponList.size() > 0)
		{
			std::cout << "Displaying stored melee weapons:" << std::endl;
			for (int i = 0; i < meleeWeaponList.size(); i++)
			{
				std::cout << i << ". ";
				meleeWeaponList[i]->print();
			}
			std::cout << std::endl;
		}
		else std::cout << "Melee weapon list is empty." << std::endl;
	}
	else
	{
		if (rangedWeaponList.size() > 0)
		{
			std::cout << "Displaying stored ranged weapons:" << std::endl;
			for (int i = 0; i < rangedWeaponList.size(); i++)
			{
				std::cout << i << ". ";
				rangedWeaponList[i]->print();
			}
			std::cout << std::endl;
		}
		else std::cout << "Ranged weapon list is empty." << std::endl;
	}
}

void itemContainerList_display()
{
	if (itemContainerList.size() > 0)
	{
		std::cout << "Displaying stored item containers:" << std::endl;
		for (int i = 0; i < itemContainerList.size(); i++)
		{
			std::cout << "Item Container at Index #" << i << std::endl;
			itemContainerList[i]->printContents();
		}
		std::cout << std::endl;
	}
	else std::cout << "Item container list is empty." << std::endl;
}






/////////////////////////////////////////////////////////
//
//
// CHARACTER-CREATION RELATED FUNCTIONS
//
//
//
/////////////////////////////////////////////////////////

void playable_character_creation(std::vector<Character*>& playableCharacters) {
	std::cout << "Playable Character Creator" << std::endl
		<< "==========================" << std::endl;

	//variables representing whether or not user wants to continue building characters
	bool wantToKeepMakingCharacters = true;
	while (wantToKeepMakingCharacters) {
		std::cout << "Character Name: ";
		std::string name;
		std::cin >> name;

		std::cout << "Level: ";
		int level;
		std::cin >> level;

		std::cout << "Rolling Stats..." << std::endl;
		std::vector<int> vec;
		std::vector<int> attributes;

		bool didntChooseReroll = false;
		while (!didntChooseReroll) {
			attributes.clear();
			//rolling for initial Stats
			// Rolls 4d20 and keeps the three highest rolls for each ability score
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 4; j++) {
					vec.push_back(Dice::roll("d6"));
				}
				std::sort(vec.begin(), vec.end(), std::greater<int>());
				attributes.push_back(vec[0] + vec[1] + vec[2]);
				vec.clear();
			}
			//sorting Stats;
			std::sort(attributes.begin(), attributes.begin() + 6, std::greater<int>());

			std::cout << "Here are your possible fighter build choices: \n" << std::endl;

			//Bully build: str > con > dex > int > cha > wis
			std::cout << "BULLY:" << std::endl;
			std::cout << "Strength: " << attributes[0] << std::endl;
			std::cout << "Dexterity: " << attributes[2] << std::endl;
			std::cout << "Constitution: " << attributes[1] << std::endl;
			std::cout << "Intelligence: " << attributes[3] << std::endl;
			std::cout << "Wisdom: " << attributes[5] << std::endl;
			std::cout << "Charisma: " << attributes[4] << std::endl;
			std::cout << std::endl;

			//Nimble build: dex > con > str > int > cha > wis
			std::cout << "NIMBLE:" << std::endl;
			std::cout << "Strength: " << attributes[2] << std::endl;
			std::cout << "Dexterity: " << attributes[0] << std::endl;
			std::cout << "Constitution: " << attributes[1] << std::endl;
			std::cout << "Intelligence: " << attributes[3] << std::endl;
			std::cout << "Wisdom: " << attributes[5] << std::endl;
			std::cout << "Charisma: " << attributes[4] << std::endl;
			std::cout << std::endl;

			//Tank build: con > dex > str > int > cha > wis
			std::cout << "TANK:" << std::endl;
			std::cout << "Strength: " << attributes[2] << std::endl;
			std::cout << "Dexterity: " << attributes[1] << std::endl;
			std::cout << "Constitution: " << attributes[0] << std::endl;
			std::cout << "Intelligence: " << attributes[3] << std::endl;
			std::cout << "Wisdom: " << attributes[5] << std::endl;
			std::cout << "Charisma: " << attributes[4] << std::endl;
			std::cout << std::endl;

			std::cout << "Which one of these would you like?" << std::endl;
			std::cout << "1. Bully" << std::endl;
			std::cout << "2. Nimble" << std::endl;
			std::cout << "3. Tank" << std::endl;
			std::cout << "4. I don't like any of them. Re-roll." << std::endl;

			int fighterBuildChoice;
			int str, dex, con, intel, wis, cha;
			Character* createdFighter;
			bool validFighterBuildChoice = false;
			bool skipNewCharacter = false;

			while (!validFighterBuildChoice) {
				bool has_chosen_to_save_or_not = false;
				int save_or_not;

				std::cin >> fighterBuildChoice;
				switch (fighterBuildChoice) {
				case 1:
					std::cout << "Creating bully type fighter class character..." << std::endl;
					str = attributes[0];
					dex = attributes[2];
					con = attributes[1];
					intel = attributes[3];
					wis = attributes[5];
					cha = attributes[4];
					createdFighter = new Character(name, "Fighter", level, str, dex, con, intel, wis, cha);

					//save character? (if validated)
					if (createdFighter->validateNewCharacter()) {
						//print sheet
						createdFighter->printStats();
						std::cout << "Would you like to save this character? (1 = Yes,  2 = No)" << std::endl;
						while (!has_chosen_to_save_or_not) {
							std::cin >> save_or_not;
							switch (save_or_not) {
							case 1:
								playableCharacters.push_back(createdFighter);
								//maybe save to file here?
								std::cout << "New playable character " << playableCharacters[playableCharacters.size() - 1]->getName() << " has been saved." << std::endl;
								has_chosen_to_save_or_not = true;
								break;
							case 2:
								std::cout << "New playable character has not been saved." << std::endl;
								has_chosen_to_save_or_not = true;
								break;
							default:
								std::cout << "Please enter either 1 or 2." << std::endl;
								std::cin.clear();
								fflush(stdin);
								break;
							}
						}
					}
					else std::cout << "New player character could not be validated" << std::endl;

					didntChooseReroll = true;
					validFighterBuildChoice = true;
					break;
				case 2:
					std::cout << "Creating nimble type fighter class character..." << std::endl;
					str = attributes[2];
					dex = attributes[0];
					con = attributes[1];
					intel = attributes[3];
					wis = attributes[5];
					cha = attributes[4];
					createdFighter = new Character(name, "Fighter", level, str, dex, con, intel, wis, cha);

					//save character? (if validated)
					if (createdFighter->validateNewCharacter()) {
						//print sheet
						createdFighter->printStats();
						std::cout << "Would you like to save this character? (1 = Yes,  2 = No)" << std::endl;
						while (!has_chosen_to_save_or_not) {
							std::cin >> save_or_not;
							switch (save_or_not) {
							case 1:
								playableCharacters.push_back(createdFighter);
								//maybe save to file here?
								std::cout << "New playable character " << playableCharacters[playableCharacters.size() - 1]->getName() << " has been saved." << std::endl;
								has_chosen_to_save_or_not = true;
								break;
							case 2:
								std::cout << "New playable character has not been saved." << std::endl;
								has_chosen_to_save_or_not = true;
								break;
							default:
								std::cout << "Please enter either 1 or 2." << std::endl;
								std::cin.clear();
								fflush(stdin);
								break;
							}
						}
					}
					else std::cout << "New player character could not be validated" << std::endl;

					didntChooseReroll = true;
					validFighterBuildChoice = true;
					break;
				case 3:
					std::cout << "Creating tank type fighter class character..." << std::endl;
					str = attributes[2];
					dex = attributes[1];
					con = attributes[0];
					intel = attributes[3];
					wis = attributes[5];
					cha = attributes[4];
					createdFighter = new Character(name, "Fighter", level, str, dex, con, intel, wis, cha);

					//save character? (if validated)
					if (createdFighter->validateNewCharacter()) {
						//print sheet
						createdFighter->printStats();
						std::cout << "Would you like to save this character? (1 = Yes,  2 = No)" << std::endl;
						while (!has_chosen_to_save_or_not) {
							std::cin >> save_or_not;
							switch (save_or_not) {
							case 1:
								playableCharacters.push_back(createdFighter);
								//maybe save to file here?
								std::cout << "New playable character " << playableCharacters[playableCharacters.size() - 1]->getName() << " has been saved." << std::endl;
								has_chosen_to_save_or_not = true;
								break;
							case 2:
								std::cout << "New playable character has not been saved." << std::endl;
								has_chosen_to_save_or_not = true;
								break;
							default:
								std::cout << "Please enter either 1 or 2." << std::endl;
								std::cin.clear();
								fflush(stdin);
								break;
							}
						}
					}
					else std::cout << "New player character could not be validated" << std::endl;

					//ending "fighter build choice" while loop
					didntChooseReroll = true;
					validFighterBuildChoice = true;
					break;
				case 4:
					//re-rolling. coming back to while loop
					std::cout << "\nRe-rolling Stats..." << std::endl;
					//starting roll from scratch, breaking out of inner while loop, but not the outer one
					validFighterBuildChoice = true;
					skipNewCharacter = true;
					break;
				default:
					std::cout << "Invalid choice. Please choose a number between 1 and 4." << std::endl;
					std::cin.clear();
					fflush(stdin);
					break;
				}
			}
			//prompting whether or not the user would like to create a new player character
			if (!skipNewCharacter) {
				std::cout << "Would you like to create another player character? ( 1 = yes, 2 = no)" << std::endl;
				int anotherCharacter;
				bool anotherCharValidChoice = false;
				while (!anotherCharValidChoice) {
					std::cin >> anotherCharacter;
					switch (anotherCharacter) {
					case 1:
						anotherCharValidChoice = true;
						std::cout << "You have chosen to create another player character." << std::endl;
						break;
					case 2:
						wantToKeepMakingCharacters = false;
						anotherCharValidChoice = true;
						std::cout << "Returning to character creation menu." << std::endl;
						break;
					default:
						std::cout << "Please enter either 1 or 2." << std::endl;
						std::cin.clear();
						fflush(stdin);
						break;
					}
				}
			}
		}
	}
}

//! function for NPC creation
//! @param nonPlayerCharacters: one of the two std::vector containing NPCs (hostile or friendly)
//! @param friendly: determines whether a friendly or hostile NPC is being created
void npc_creation(std::vector<Character*>& nonPlayerCharacters, bool friendly) {
	std::cout << "Non-Playable Character Creator " << (friendly ? "(friendly)" : "(hostile)") << std::endl
		<< "=========================================" << std::endl;

	//variables representing whether or not user wants to continue building characters
	bool wantToKeepMakingCharacters = true;
	while (wantToKeepMakingCharacters) {
		std::string name, charaType;
		int lvl, str, dex, con, intel, wis, cha;
		std::cout << "Character Name: ";
		std::cin >> name;
		std::cout << "Character Type: ";
		std::cin >> charaType;
		std::cout << "Level: ";
		std::cin >> lvl;
		std::cin.clear();
		fflush(stdin);
		std::cout << "Strength: ";
		std::cin >> str;
		std::cin.clear();
		fflush(stdin);
		std::cout << "Dexterity: ";
		std::cin >> dex;
		std::cin.clear();
		fflush(stdin);
		std::cout << "Constitution: ";
		std::cin >> con;
		std::cin.clear();
		fflush(stdin);
		std::cout << "Intelligence: ";
		std::cin >> intel;
		std::cin.clear();
		fflush(stdin);
		std::cout << "Wisdom: ";
		std::cin >> wis;
		std::cin.clear();
		fflush(stdin);
		std::cout << "Charisma: ";
		std::cin >> cha;
		std::cin.clear();
		fflush(stdin);

		Character* newChara = new Character(name, charaType, lvl, str, dex, con, intel, wis, cha);

		if (newChara->validateNewNPC()) {
			std::cout << "New " << (friendly ? "friendly" : "hostile") << "character created." << std::endl;
			newChara->printStats();

			std::cout << "Would you like to save this character? (1 = Yes,  2 = No)" << std::endl;
			int save_or_not;
			bool has_chosen_to_save_or_not = false;
			while (!has_chosen_to_save_or_not) {
				std::cin >> save_or_not;
				switch (save_or_not) {
				case 1:
					nonPlayerCharacters.push_back(newChara);
					std::cout << "New " << (friendly ? "friendly" : "hostile") << " character has been saved." << std::endl;
					has_chosen_to_save_or_not = true;
					break;
				case 2:
					std::cout << "New " << (friendly ? "friendly" : "hostile") << " character has not been saved." << std::endl;
					has_chosen_to_save_or_not = true;
					break;
				default:
					std::cout << "Please enter either 1 or 2." << std::endl;
					std::cin.clear();
					fflush(stdin);
					break;
				}
			}
		}
		else std::cout << "New " << (friendly ? "friendly" : "hostile") << " character could not be validated." << std::endl;

		std::cout << "Would you like to keep making " << (friendly ? "friendly" : "hostile") << " NPCs?" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2. No" << std::endl;

		int selection;
		bool validSelection = false;
		while (!validSelection) {
			std::cin >> selection;
			switch (selection) {
			case 1:
				std::cout << "Creating new " << (friendly ? "friendly" : "hostile") << " character..." << std::endl;
				validSelection = true;
				break;
			case 2:
				std::cout << "Returning to character creation menu." << std::endl;
				validSelection = true;
				wantToKeepMakingCharacters = false;
				break;
			default:
				std::cout << "Please select either 1 or 2." << std::endl;
				std::cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}

//! function for displaying all stored characters in a std::vector, along with their respective std::vector indices
//! @param characterList: the list of character to print out
void displayAllCharacters(std::vector<Character*>& characterList) {
	if (characterList.size() == 0) {
		std::cout << "Character list is empty." << std::endl;
		return;
	}
	else {
		std::cout << "Displaying stored characters..." << std::endl;
		for (int i = 0; i < characterList.size(); i++) {
			std::cout << i << ". " << "Name: " << characterList[i]->getName() << " Class: " << characterList[i]->getClass() << " Level: " << characterList[i]->getLevel() << std::endl;
		}
	}
}

void displayDetailedInfo(std::vector<Character*>& characterList, int index) {
	Character* chara = characterList[index];
	std::cout << "Displaying character stored at index " << index << "..." << std::endl;
	std::cout << "NAME: " << chara->getName() << std::endl;
	std::cout << "CLASS: " << chara->getClass() << std::endl;
	std::cout << "LEVEL: " << chara->getLevel() << std::endl;
	std::cout << "EXP: " << chara->getExpPoints() << std::endl;
	std::cout << "CURRENT HIT POINTS: " << chara->getCurrentHitPoints() << std::endl;
	std::cout << "MAX HIT POINTS: " << chara->getMaxHitPoints() << std::endl;
	std::cout << "STR: " << chara->getStrength() << " (modifier: " << chara->getStrengthModifier() << ")" << std::endl;
	std::cout << "DEX: " << chara->getDexterity() << " (modifier: " << chara->getDexterityModifier() << ")" << std::endl;
	std::cout << "CON: " << chara->getConstitution() << " (modifier: " << chara->getConstitutionModifier() << ")" << std::endl;
	std::cout << "INT: " << chara->getIntelligence() << " (modifier: " << chara->getIntelligenceModifier() << ")" << std::endl;
	std::cout << "WIS: " << chara->getWisdom() << " (modifier: " << chara->getWisdomModifier() << ")" << std::endl;
	std::cout << "CHA: " << chara->getCharisma() << " (modifier: " << chara->getCharismaModifier() << ")" << std::endl;
	std::cout << "ARMOR CLASS: " << chara->getArmorClass() << std::endl;
	std::cout << "BASE ATTACK BONUS: " << "+" << chara->getBaseAttackBonus(0);
	if (chara->getLevel() > 5)
		std::cout << "/+" << chara->getBaseAttackBonus(1);
	if (chara->getLevel() > 10)
		std::cout << "/+" << chara->getBaseAttackBonus(2);
	if (chara->getLevel() > 15)
		std::cout << "/+" << chara->getBaseAttackBonus(3);
	std::cout << std::endl;
	//printing attack bonus
	std::cout << "ATTACK BONUS: " << ((chara->getAttackBonus(0) > (-1)) ? "+" : "") << chara->getAttackBonus(0);
	if (chara->getLevel() > 5)
		std::cout << ((chara->getAttackBonus(1) > (-1)) ? "/+" : "/") << chara->getAttackBonus(1);
	if (chara->getLevel() > 10)
		std::cout << ((chara->getAttackBonus(2) > (-1)) ? "/+" : "/") << chara->getAttackBonus(2);
	if (chara->getLevel() > 15)
		std::cout << ((chara->getAttackBonus(3) > (-1)) ? "/+" : "/") << chara->getAttackBonus(3);
	std::cout << std::endl;
	std::cout << "DAMAGE BONUS: " << chara->getDamageBonus() << std::endl;
}

//! function for displaying character info in higher detail, will be prompted to enter a certain index to use to retrieve the character info from the std::vector
//! @param characterList: the list of character from a single character's info is retrieved
void displayCharacterDetails(std::vector<Character*>& characterList) {
	if (characterList.size() == 0) {
		std::cout << "Character list is empty." << std::endl;
		return;
	}
	std::cout << "Please enter the index of the character whose information you would like to see: ";

	bool validIndexSelection = false;
	int index;
	while (!validIndexSelection) {
		std::cin >> index;
		if ((index < 0) || (index >(characterList.size() - 1))) {
			std::cout << "Invalid selection. Please try again." << std::endl;
			std::cin.clear();
			fflush(stdin);
		}
		else {
			validIndexSelection = true;
			displayDetailedInfo(characterList, index);
		}
	}
}

void enemy_npc_creation(std::vector<Character*>& hostileCharacters) {
	npc_creation(hostileCharacters, false);
}

void friendly_npc_creation(std::vector<Character*>& friendlyCharacters) {
	npc_creation(friendlyCharacters, true);
}

void editCharacterAtIndex(std::vector<Character*>& characterList, bool hasPlayerCharaValidationCond) {
	if (characterList.size() == 0) {
		std::cout << "Character list is empty." << std::endl;
		return;
	}
	bool validSelection = false;
	bool quitCharaEdit = false;
	int index, statEdit;
	std::string inString;
	int inInt;

	displayAllCharacters(characterList);
	std::cout << "\nPlease enter the index of the character you would like to edit." << std::endl;

	while (!validSelection) {
		std::cin >> index;
		if ((index < 0) || (index >(characterList.size() - 1))) {
			std::cout << "Invalid selection. Please try again." << std::endl;
			std::cin.clear();
			fflush(stdin);
		}
		else {
			displayDetailedInfo(characterList, index);
			std::cout << "\nPlease select what you would like to edit. Enter -1 to quit character edit mode." << std::endl;
			std::cout << "[1:name] [2:class] [3:level] [4:xp pts] [5:cur hp]" << std::endl;
			std::cout << "[6:str] [7:dex] [8:con] [9:int] [10:wis] [11:char]" << std::endl;
			std::cin >> statEdit;
			switch (statEdit) {
			case -1:
				quitCharaEdit = true;
				validSelection = true;
				break;
			case 1:
				std::cout << "Please enter your new desired character name: ";
				std::cin >> inString;
				std::cout << "Character's name changed from \"" << characterList[index]->getName() << "\" to \"" << inString << "\"." << std::endl;
				characterList[index]->setName(inString);
				std::cout << std::endl;
				std::cout << "Character after edit:" << std::endl;
				std::cout << std::endl;
				displayDetailedInfo(characterList, index);
				validSelection = true;
				break;
			case 2:
				std::cout << "Please enter your new desired character class: ";
				std::cin >> inString;
				if (!hasPlayerCharaValidationCond) {
					std::cout << "Character's class changed from \"" << characterList[index]->getClass() << "\" to \"" << inString << "\"." << std::endl;
					characterList[index]->setClass(inString);
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
				}
				else std::cout << "Player characters may only be of fighter class." << std::endl;
				validSelection = true;
				break;
			case 3:
				std::cout << "Please enter your new desired character level: ";
				std::cin >> statEdit;
				if (statEdit > -1) {
					std::cout << "Character's level changed from \"" << characterList[index]->getLevel() << "\" to \"" << statEdit << "\"." << std::endl;
					characterList[index]->setLevel(statEdit);
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
				}
				else std::cout << "Invalid value." << std::endl;
				validSelection = true;
				break;
			case 4:
				std::cout << "Please enter your new desired character experience points: ";
				std::cin >> statEdit;
				if (statEdit > -1) {
					std::cout << "Character's experience points changed from \"" << characterList[index]->getExpPoints() << "\" to \"";
					characterList[index]->setExpPoints(statEdit);
					std::cout << characterList[index]->getExpPoints() << "\"." << std::endl;
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
				}
				else std::cout << "Invalid value." << std::endl;
				validSelection = true;
				break;
			case 5:
				std::cout << "Please enter your new desired character current hit points: ";
				std::cin >> statEdit;
				std::cout << "Character's current HP has been changed from \"" << characterList[index]->getCurrentHitPoints() << "\" to \"";
				characterList[index]->setCurrentHitPoints(statEdit);
				std::cout << characterList[index]->getCurrentHitPoints() << "\"." << std::endl;
				std::cout << std::endl;
				std::cout << "Character after edit:" << std::endl;
				std::cout << std::endl;
				displayDetailedInfo(characterList, index);
				validSelection = true;
				break;
			case 6:
				std::cout << "Please enter your new desired character strength: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					characterList[index]->setStrength(statEdit);
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				std::cout << "Character's strength has been changed from \"" << characterList[index]->getStrength() << "\" to \"" << statEdit << "\"." << std::endl;
				break;
			case 7:
				std::cout << "Please enter your new desired character dexterity: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's dexterity has been changed from \"" << characterList[index]->getDexterity() << "\" to \"" << statEdit << "\"." << std::endl;
					characterList[index]->setDexterity(statEdit);
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				break;
			case 8:
				std::cout << "Please enter your new desired character constitution: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's constitution has been changed from \"" << characterList[index]->getConstitution() << "\" to \"" << statEdit << "\"." << std::endl;
					characterList[index]->setConstitution(statEdit);
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				break;
			case 9:
				std::cout << "Please enter your new desired character intelligence: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's intelligence has been changed from \"" << characterList[index]->getIntelligence() << "\" to \"" << statEdit << "\"." << std::endl;
					characterList[index]->setIntelligence(statEdit);
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				break;
			case 10:
				std::cout << "Please enter your new desired character wisdom: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's wisdom has been changed from \"" << characterList[index]->getWisdom() << "\" to \"" << statEdit << "\"." << std::endl;
					characterList[index]->setWisdom(statEdit);
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				break;
			case 11:
				std::cout << "Please enter your new desired character charisma: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's charisma has been changed from \"" << characterList[index]->getLevel() << "\" to \"" << statEdit << "\"." << std::endl;
					characterList[index]->setCharisma(statEdit);
					std::cout << std::endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << std::endl;
					displayDetailedInfo(characterList, index);
				}
				else std::cout << "Invalid value." << std::endl;
				validSelection = true;
				break;
			default:
				std::cout << "Please enter either a number from 1 to 11, or -1 to cancel." << std::endl;
				std::cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}

void deleteCharacterAtIndex(std::vector<Character*>& characterList) {
	if (characterList.size() == 0) {
		std::cout << "Character list is empty." << std::endl;
		return;
	}


	std::cout << "Please enter the index number of the character you would like to delete. Enter '-1' (minus quotations) to cancel." << std::endl;

	int index;
	bool validSelection = false;

	while (!validSelection) {
		std::cin >> index;

		if (index == (-1)) {
			std::cout << "Deletion request cancelled." << std::endl;
			return;
		}

		if ((index < (-1)) || (index >(characterList.size() - 1))) {
			std::cout << "Invalid selection. Please try again." << std::endl;
			std::cin.clear();
			fflush(stdin);
		}
		else {
			std::cout << "Character " << characterList[index]->getName() << " has been deleted." << std::endl;
			characterList.erase(characterList.begin() + index);
			return;
		}
	}
}

void character_edit_mode(std::vector<Character*>& characterList, std::string characterTypeCap, std::string characterType, bool hasPlayerCharaValidationCond) {
	std::cout << characterTypeCap << " Character Edit Mode" << std::endl;
	std::cout << "============================" << std::endl;
	std::cout << "What would you like to do?" << std::endl;
	std::cout << "1. Display stored characters" << std::endl;
	std::cout << "2. Detailed display of character stored at specific index" << std::endl;
	std::cout << "3. Edit a character stored at specific index" << std::endl;
	std::cout << "4. Delete a character stored at specific index" << std::endl;
	std::cout << "5. Return to character maker menu\n" << std::endl;

	bool wantToStayInCharaEditMode = true;
	int selection;
	while (wantToStayInCharaEditMode) {
		std::cin >> selection;
		switch (selection) {
		case 1:
			displayAllCharacters(characterList);
			break;
		case 2:
			displayCharacterDetails(characterList);
			break;
		case 3:
			editCharacterAtIndex(characterList, hasPlayerCharaValidationCond);
			break;
		case 4:
			deleteCharacterAtIndex(characterList);
			break;
		case 5:
			std::cout << "Returning to character maker menu." << std::endl;
			wantToStayInCharaEditMode = false;
			break;
		default:
			std::cout << "Please choose a value between 1 and 5" << std::endl;
			std::cin.clear();
			fflush(stdin);
			break;
		}
	}
}

void characterMakerMainMenu(std::vector<Character*>& playableCharacters, std::vector<Character*>& hostileCharacters, std::vector<Character*>& friendlyCharacters) {
	std::cout << "Character Maker" << std::endl
		<< "=================" << std::endl;

	bool wantToQuit = false;
	while (!wantToQuit) {
		std::cout << "What would you like to do?" << std::endl
			<< "1. Create a player character (Fighter only)" << std::endl
			<< "2. Create an enemy non-player character" << std::endl
			<< "3. Create a friendly non-player character" << std::endl
			<< "4. Edit a stored player character" << std::endl
			<< "5. Edit a stored enemy non-player character" << std::endl
			<< "6. Edit a stored friendly non-player character" << std::endl
			<< "7. Exit character creator." << std::endl;

		int charaTypeSelection;
		bool validCharaTypeSelection = false;

		while (!validCharaTypeSelection) {
			std::cin >> charaTypeSelection;

			switch (charaTypeSelection) {
			case 1:
				playable_character_creation(playableCharacters);
				validCharaTypeSelection = true;
				break;
			case 2:
				enemy_npc_creation(hostileCharacters);
				validCharaTypeSelection = true;
				break;
			case 3:
				friendly_npc_creation(friendlyCharacters);
				validCharaTypeSelection = true;
				break;
			case 4:
				character_edit_mode(playableCharacters, "Playable", "playable", true);
				validCharaTypeSelection = true;
				break;
			case 5:
				character_edit_mode(hostileCharacters, "Enemy", "enemy", false);
				validCharaTypeSelection = true;
				break;
			case 6:
				character_edit_mode(friendlyCharacters, "Fristd::endly", "friendly", false);
				validCharaTypeSelection = true;
				break;
			case 7:
				wantToQuit = true;
				validCharaTypeSelection = true;
				std::cout << "Returning to creator mode menu." << std::endl;
				break;
			default:
				std::cout << "Invalid choice. Please choose a number between 1 and 4." << std::endl;
				std::cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}