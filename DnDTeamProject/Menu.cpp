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

using namespace std;


void main_menu();
void start_game();
void creator_mode();

//vectors holding "saved" objects
vector<Map> savedMaps;
vector<ItemContainer*> savedContainers;
vector<Character*> savedCharacters;




// vectors for characters
static vector<Character*> player_characters, hostile_characters, friendly_characters;

//character creation & editing
void characterMakerMainMenu();
void playable_character_creation(vector<Character*>& playableCharacters);
void npc_creation(vector<Character*>& nonPlayerCharacters, bool friendly);
void displayAllCharacters(vector<Character*>& characterList);
void displayDetailedInfo(vector<Character*>& characterList, int index);
void displayCharacterDetails(vector<Character*>& characterList);
void enemy_npc_creation(vector<Character*>& hostileCharacters);
void friendly_npc_creation(vector<Character*>& friendlyCharacters);
void editCharacterAtIndex(vector<Character*>& characterList, bool hasPlayerCharaValidationCond);
void deleteCharacterAtIndex(vector<Character*>& characterList);
void character_edit_mode(vector<Character*>& characterList, string characterTypeCap, string characterType, bool hasPlayerCharaValidationCond);
void characterMakerMainMenu(vector<Character*>& playableCharacters, vector<Character*>& hostileCharacters, vector<Character*>& friendlyCharacters);

//item creation & editing
void itemMakerMenu();
void itemCreator();
void itemEditor();
void itemContainerCreator();
void itemContainerEditor();
void EnchantAdd(Item* ic);

void editEquipment(vector<Equipment*>& equipmentList, string equipmentTypeC, string equipmentType);
void editWeapons(vector<Weapon*>& weaponList, string weaponTypeC, string weaponType, bool isMelee);
void editEnchantments_e(vector<Equipment*>& equipmentList, int index);
void editEnchantments_w(vector<Weapon*>& equipmentList, int index);

//static vector storing items
static vector<Weapon*> rangedWeaponList;
static vector<Weapon*> meleeWeaponList;
static vector<Equipment*> armorList;
static vector<Equipment*> shieldList;
static vector<Equipment*> helmetList;
static vector<Equipment*> ringList;
static vector<Equipment*> bootsList;
static vector<Equipment*> beltList;
static vector<Item*> otherItemList;
static vector<ItemContainer*> itemContainerList;
void equipmentList_display(vector<Equipment*>& equipmentType, string equipmentTypeNameC, string equipmentTypeName);
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




int main() {
	main_menu();
	return 0;
}




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
		cout << "Please enter an action: " << endl
			<< "n - move north, w - move west, e - move east, s - move south, q - exit" << endl
			<< "x - enter examine mode, c - enter character mode" << endl;

		char choice;

		cin >> choice;

		switch (choice)
		{
		case 'n':
			m.moveChar(m.getPC(), 'n');
			break;
		case 'w':
			m.moveChar(m.getPC(), 'w');
			break;
		case 'e':
			m.moveChar(m.getPC(), 'e');
			break;
		case 's':
			m.moveChar(m.getPC(), 's');
			break;
		case 'q':
			cout << "Leaving map mode." << endl;
			exitMenu = true;
			break;
		case 'x':
			examineMode(m);
			break;
		case 'c':
			characterMode(m.getPC()->getElement());
			m.notify();
			break;
		default:
			break;
		}

		if (m.exitReached())
		{
			m.setCell(m.getPC()->getX(), m.getPC()->getY(), '\\');
			cout << "EXIT Reached!" << endl;
			exitMenu = true;
		}
	}
}

void examineMode(Map& m)
{
	bool exitMenu = false;

	while (!exitMenu)
	{
		cout << "Examine menu: enter a character and ENTER to select an action: " << endl
			<< "n - examine north, s - examine south, e - examine east, w - examine west" << endl
			<< "q - quit examine mode" << endl;

		char choiceX;

		cin >> choiceX;

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
			cout << "Leaving examine mode." << endl;
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
		cout << "Character Menu: enter a character and ENTER to select an action" << endl
			<< "u - unequip an item, q - quit character menu" << endl;

		char choiceC;

		cin >> choiceC;

		switch (choiceC)
		{
		case 'q':
			exitMenu = true;
			cout << "Leaving character screen..." << endl;
			system("PAUSE");
			break;
		case 'u':
			cout << "unavailable for now" << endl;
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
		cout << "============" << endl
			<< " Map Maker" << endl
			<< "============" << endl;

		cout << "select an option:" << endl
			<< "a - Map Creator, b - Map Editor, q - Quit" << endl;

		char choice;

		cin >> choice;

		switch (choice)
		{
		case 'a':
			mapCreator();
			break;
		case 'b':
			cout << "Unimplemented. Sorry!" << endl;
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

	cout << "Map Creator" << endl;
	cout << "------------" << endl;
	cout << "p - proceed, q - quit" << endl;

	cin >> mainChoice;

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

		cout << "please enter the map width" << endl
			<< "(between 3 and 20):" << endl;

		cin >> width;

		cout << "please enter the map height" << endl
			<< "(between 3 and 20)" << endl;

		cin >> height;

		cout << "selected width/height: " << width << ", " << height << endl;

		system("PAUSE");

		step1 = false;

		if (width < 3 || width > 20 || height < 3 || width > 20)
		{
			cout << "Invalid Selection!" << endl;
			step1 = true;
		}

	}

	Map cMap(width, height);

	MapObserver mObs(&cMap);

	cout << "CURRENT MAP" << endl;



	char sprite;
	bool addEle = true;

	while (addEle)
	{

		bool step2 = true;
		bool step3 = true;

		while (step2)
		{
			cout << "Add an element to the map?" << endl
				<< "w - place wall, f - place floor tile" << endl
				<< "q - quit" << endl;

			char choose;

			cin >> choose;

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
			cout << "Set element where?" << endl
				<< "Select x coordinate (starting from 0 to width - 1) : " << endl;

			cin >> eleX;

			cout << "Select y coordinate (y increases downwards):" << endl;

			cin >> eleY;

			if (eleX < 0 || eleX >= width || eleY < 0 || eleY >= height)
			{
				cout << "element out of bounds! please try again." << endl;
			}
			else if (eleX == cMap.EntranceGetX() && eleY == cMap.EntranceGetY())
			{
				cout << "cannot place over entrance." << endl;
			}
			else if (eleX == cMap.ExitGetX() && eleY == cMap.ExitGetY())
			{
				cout << "Cannot place over exit." << endl;
			}
			else
			{
				cout << "Element Added" << endl;
				cMap.setCell(eleX, eleY, sprite);
				system("PAUSE");
				step3 = false;
			}

		}
	}

	bool loopB = true;

	while (loopB)
	{
		cout << "would you like to change the location of the entrance/exit?" << endl
			<< "y - yes, n - no" << endl;

		char chEnEx;

		cin >> chEnEx;

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


	cout << "Adding Characters and Containers to Map..." << endl;

	mapAddObjects(cMap, width, height);

	if (!cMap.validate())
	{
		cout << "ERROR: Invalid map. No path to exit." << endl;
	}
	else
	{
		cout << "Map successfully created" << endl;
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

		cout << "What would you like to add?" << endl
			<< "1 - Character" << endl
			<< "2 - Container" << endl
			<< "3 - Quit" << endl;

		int choice;

		cin >> choice;

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
				cout << savedCharacters.size() << " saved character found." << endl;

				cout << "Select a saved character to add (index 0 to " << savedCharacters.size() - 1 << ")" << endl;

				cin >> index;

				if (index < 0 || index > savedCharacters.size() - 1)
				{
					cout << "Invalid index selected." << endl;
				}
				else
				{
					savedCharacters[index]->printStats();
					cout << "Do you want to add this character?" << endl
						<< "y - yes, n - no" << endl;

					char choiceA;

					cin >> choiceA;

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
				cout << "No saved characters to load..." << endl;
				addCh = false;
			}
		}

		//add container, phase 1
		while (addCo)
		{
			if (savedContainers.size() > 0)
			{
				cout << savedContainers.size() << " saved container found." << endl;

				cout << "Select a saved container to add (index 0 to " << savedContainers.size() - 1 << ")" << endl;

				cin >> index;

				if (index < 0 || index > savedContainers.size() - 1)
				{
					cout << "Invalid index selected." << endl;
				}
				else
				{
					savedContainers[index]->printContents();
					cout << "Do you want to add this container?" << endl
						<< "y - yes, n - no" << endl;

					char choiceA;

					cin >> choiceA;

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
				cout << "No saved containers to load..." << endl;
				addCo = false;
			}
		}

		// add character, phase 2
		while (addCh2)
		{
			m.displayGrid();
			cout << "Where would you like to add the element?" << endl
				<< "Set x coordinate:" << endl;

			int coorX;
			int coorY;

			cin >> coorX;

			cout << "Set y coordinate" << endl;

			cin >> coorY;

			if (coorX < 0 || coorY < 0 || coorX >= width || coorY >= height)
			{
				cout << "Out of bounds! Please select another location." << endl;
			}
			else
			{
				cout << "Adding Character..." << endl;
				m.addNPC(savedCharacters[index], coorX, coorY, 'N');
				addCh2 = false;
			}

		}

		// add container, phase 2
		while (addCo2)
		{
			m.displayGrid();
			cout << "Where would you like to add the element?" << endl
				<< "Set x coordinate:" << endl;

			int coorX;
			int coorY;

			cin >> coorX;

			cout << "Set y coordinate" << endl;

			cin >> coorY;

			if (coorX < 0 || coorY < 0 || coorX >= width || coorY >= height)
			{
				cout << "Out of bounds! Please select another location." << endl;
			}
			else
			{
				cout << "Adding Container..." << endl;
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
		cout << "Edit location of Exit or Entrance?" << endl
			<< "n - entrance, x - exit, q - quit" << endl;

		char choice1;

		cin >> choice1;

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

			cout << "Select a location for the new entrance..." << endl
				<< "select an x-coordinate:" << endl;

			int chx;

			cin >> chx;

			cout << "select a y-coordinate:" << endl;

			int chy;

			cin >> chy;

			cout << "Selected: " << chx << ", " << chy << endl;

			// index is walls of map
			if (chx == 0 || chx == width - 1 || chy == 0 || chy == height - 1)
			{
				// corner selected
				if ((chx == 0 && chy == 0) || (chx == width - 1 && chy == 0)
					|| (chx == 0 && chy == height - 1) || (chx == width - 1 && chy == height - 1))
				{
					cout << "Cannot place at corner" << endl;
				}
				else if (chx == m.ExitGetX() && chy == m.ExitGetY())
				{
					cout << "Cannot place here. Exit present." << endl;
				}
				else
				{
					m.resetEntrance(chx, chy);
					editEn = false;
				}

			}
			else
			{
				cout << "Entrance must be placed on the side of the map." << endl;
			}
		}

		while (editEx)
		{
			m.displayGrid();

			cout << "Select a location for the new exit..." << endl
				<< "select an x-coordinate:" << endl;

			int chx;

			cin >> chx;

			cout << "select a y-coordinate:" << endl;

			int chy;

			cin >> chy;

			cout << "Selected: " << chx << ", " << chy << endl;

			// index is walls of map
			if (chx == 0 || chx == width - 1 || chy == 0 || chy == height - 1)
			{
				// corner selected
				if ((chx == 0 && chy == 0) || (chx == width - 1 && chy == 0)
					|| (chx == 0 && chy == height - 1) || (chx == width - 1 && chy == height - 1))
				{
					cout << "Cannot place at corner" << endl;
				}
				else if (chx == m.EntranceGetX() && chy == m.EntranceGetY())
				{
					cout << "Cannot place here. Entrance present." << endl;
				}
				else
				{
					m.resetExit(chx, chy);
					editEx = false;
				}

			}
			else
			{
				cout << "Entrance must be placed on the side of the map." << endl;
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
		cout << "==========" << endl
			<< "Item Maker" << endl
			<< "==========" << endl;

		cout << "Select an option: " << endl
			<< "  Create/Edit" << endl
			<< "a - create new item, b - edit saved item," << endl
			<< "  Display" << endl
			<< "c - melee weapons list, d - ranged weapons list," << endl
			<< "e - armor list, f - shield list" << endl
			<< "g - helmet list, h - ring list" << endl
			<< "i - boots list, j - belt list" << endl
			<< "  Other" << endl
			<< "q - quit" << endl;

		char choice;

		cin >> choice;

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
			cout << "Leaving Item Maker..." << endl;
			menuLoop = false;
			break;
		}
	}
}

string legalEnchants(itemType it)
{
	switch (it)
	{
	case itemType::HELMET:
		return "Intelligence, Wisdom, Armor Class";
		break;
	case itemType::ARMOR:
		return "Armor Class";
		break;
	case itemType::SHIELD:
		return "Armor Class";
		break;
	case itemType::RING:
		return "Armor Class, Strength, Constitution, Wisdom, Charisma";
		break;
	case itemType::BELT:
		return "Constitution, Strength";
		break;
	case itemType::BOOTS:
		return "Armor Class, Dexterity";
		break;
	case itemType::WEAPON:
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
		cout << "Item Creator" << endl
			<< "-------------" << endl;

		bool step1 = true;
		bool step2 = false;
		bool step3 = false;

		itemType cType;
		weaponType cSub;

		while (step1)
		{
			cout << "What type of item would you like to make?" << endl
				<< "h - helmet, s - shield, a - armor, r - ring" << endl
				<< "b - belt, o - boots, m - melee weapon, w - ranged weapon" << endl
				<< "q - quit" << endl;

			char choice1;

			cin >> choice1;

			switch (choice1)
			{
			case 'h':
				cType = itemType::HELMET;
				cout << cType << " selected" << endl;
				step1 = false;
				step2 = true;
				break;
			case 's':
				cType = itemType::SHIELD;
				cout << cType << " selected" << endl;
				step1 = false;
				step2 = true;
				break;
			case 'a':
				cType = itemType::ARMOR;
				cout << cType << " selected" << endl;
				step1 = false;
				step2 = true;
				break;
			case 'r':
				cType = itemType::RING;
				cout << cType << " selected" << endl;
				step1 = false;
				step2 = true;
				break;
			case 'b':
				cType = itemType::BELT;
				cout << cType << " selected" << endl;
				step1 = false;
				step2 = true;
				break;
			case 'o':
				cType = itemType::BOOTS;
				cout << cType << " selected" << endl;
				step1 = false;
				step2 = true;
				break;
			case 'm':
				cType = itemType::WEAPON;
				cSub = weaponType::MELEE;
				cout << cType << "[ " << cSub << "] " << "selected" << endl;
				step1 = false;
				step2 = true;
				break;
			case 'w':
				cType = itemType::WEAPON;
				cSub = weaponType::RANGED;
				cout << cType << "[ " << cSub << "] " << "selected" << endl;
				step1 = false;
				step2 = true;
				break;
			case 'q':
				return;
				break;
			}
		}

		string cName;

		while (step2)
		{
			cout << "Give your Item a name: " << endl;

			cin >> cName;

			char confirm;

			cout << "Name: " << cName << endl
				<< "Is this ok? y - yes, n - no" << endl;

			cin >> confirm;

			if (confirm == 'y')
				step2 = false;
		}

		Item* cItem;

		if (cType == itemType::WEAPON)
		{
			if (cSub == weaponType::RANGED)
				cItem = new Weapon(cName, cType, vector<Enchant*>(), 2, cSub);
			else
				cItem = new Weapon(cName, cType, vector<Enchant*>(), 0, cSub);
		}
		else
		{
			cItem = new Equipment(cName, cType, vector<Enchant*>());
		}

		cout << "Created Item: " << endl;
		cItem->print();
		system("PAUSE");

		bool add_enchant = true;

		while (add_enchant)
		{
			cout << "Would you like to add an Enchant?" << endl
				<< "y - yes, n - no" << endl;

			char choose;

			cin >> choose;

			if (choose == 'y')
				EnchantAdd(cItem);

			if (choose == 'n')
				add_enchant = false;

		}

		cout << "Created:" << endl;
		cItem->print();

		bool save_item = true;

		while (save_item)
		{
			cout << "Would you like to save this item?" << endl
				<< "y - yes, n - no" << endl;

			char save_choice;
			cin >> save_choice;

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

				cout << "Item has been saved." << endl;
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

	stats cStat;

	while (loop1)
	{
		cout << "Choose an enchant to add: " << endl
			<< "s - Strength, w - Wisdom, c - Constitution, i - Intelligence" << endl
			<< "d - Dexterity, h - Charisma, a - Armor Class, t - Attack Bonus" << endl
			<< "m - damage bonus" << endl
			<< "Valid Enchants for your Item: " << legalEnchants(ic->getType()) << endl;

		char choice;

		cin >> choice;

		switch (choice)
		{
		case 's':
			cStat = stats::STR;
			loop1 = false;
			break;
		case 'w':
			cStat = stats::WIS;
			loop1 = false;
			break;
		case 'c':
			cStat = stats::CON;
			loop1 = false;
			break;
		case 'i':
			cStat = stats::INT;
			loop1 = false;
			break;
		case 'd':
			cStat = stats::DEX;
			loop1 = false;
			break;
		case 'h':
			cStat = stats::CHA;
			loop1 = false;
			break;
		case 'a':
			cStat = stats::AC;
			loop1 = false;
			break;
		case 't':
			cStat = stats::ATK;
			loop1 = false;
			break;
		case 'm':
			cStat = stats::DMG;
			loop1 = false;
			break;
		}

		if (!loop1)
		{
			if (!(ic->validEnch(ic->getType(), cStat)))
			{
				cout << "Invalid Enchant!" << endl;
				cin.clear();
				fflush(stdin);
				loop1 = true;
			}
		}
	}

	bool loop2 = true;

	int enVal;

	while (loop2)
	{
		cout << "Enter a value between 1 and 5" << endl;

		cin >> enVal;

		loop2 = false;

		if (enVal > 5 || enVal < 1)
		{
			cout << "Invalid value!" << endl;
			cin.clear();
			fflush(stdin);
			loop2 = true;
		}
	}

	ic->addEnch(new Enchant(cStat, enVal));
}

void itemEditor() {
	bool loopy1 = true;

	while (loopy1) {
		cout << "What kind of item would you like to edit?" << endl
			<< "h - helmet, s - shield, a - armor, r - ring" << endl
			<< "b - belt, o - boots, m - melee weapon, w - ranged weapon" << endl
			<< "q - quit" << endl;

		char edit_choice_1;
		int indexOfItem;

		cin >> edit_choice_1;

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

void editEquipment(vector<Equipment*>& equipmentList, string equipmentTypeC, string equipmentType) {
	int indexOfItem;

	cout << "Please enter the index of the " << equipmentType << " you would like to edit.";

	cin >> indexOfItem;
	if ((indexOfItem < 0) || (indexOfItem >(equipmentList.size() - 1))) {
		cout << "Invalid item index. Please try again." << endl;
		cin.clear();
		fflush(stdin);
	}
	else {
		cout << "Printing " << equipmentType << " details:" << endl;
		equipmentList[indexOfItem]->print();
		cout << "What would you like to edit? Enter -1 to cancel." << endl;
		cout << "1. " << equipmentTypeC << " name" << endl;
		cout << "2. " << equipmentTypeC << " enchantments" << endl;

		int editChoice;
		bool noEditChoice = true;
		string newName;
		while (noEditChoice) {
			cin >> editChoice;
			switch (editChoice) {
			case 1:
				cout << "Please enter what you would like the item to be renamed to: ";
				cin >> newName;
				equipmentList[indexOfItem]->setName(newName);
				cout << "Item has been renamed to " << newName << "." << endl;
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
				cout << "Invalid entry. Please enter either 1 or 2." << endl;
				cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}

void editWeapons(vector<Weapon*>& weaponList, string weaponTypeC, string weaponType, bool isMelee) {
	int indexOfItem;

	cout << "Please enter the index of the " << weaponType << " you would like to edit.";

	cin >> indexOfItem;
	if ((indexOfItem < 0) || (indexOfItem >(weaponList.size() - 1))) {
		cout << "Invalid item index. Please try again." << endl;
		cin.clear();
		fflush(stdin);
	}
	else {
		cout << "Printing " << weaponType << " details:" << endl;
		weaponList[indexOfItem]->print();
		cout << "What would you like to edit? Enter -1 to cancel." << endl;
		cout << "1. " << weaponTypeC << " name" << endl;
		cout << "2. " << weaponTypeC << " enchantments" << endl;
		if (!isMelee)
			cout << "3. Weapon range." << endl;

		int editChoice;
		bool noEditChoice = true;
		string newName;
		while (noEditChoice) {
			cin >> editChoice;
			switch (editChoice) {
			case 1:
				cout << "Please enter what you would like the item to be renamed to: ";
				cin >> newName;
				weaponList[indexOfItem]->setName(newName);
				cout << "Item has been renamed to " << newName << "." << endl;
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
				cout << "Invalid entry. Please enter either 1 or 2." << endl;
				cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}

void editEnchantments_e(vector<Equipment*>& equipmentList, int index) {
	cout << "Item " << equipmentList[index]->getName() << "'s list of enchants:" << endl;
	for (int i = 0; i < equipmentList[index]->getEnch().size(); i++) {
		cout << i << ". ";
		equipmentList[index]->getEnch()[i]->print();
	}
	cout << "Enter the index of the enchantment item \"" << equipmentList[index]->getName() << "\" has that you would like to edit." << endl;

	int index_of_enchant;
	int newEnchantValue;
	bool loop = true;
	while (loop) {
		cin >> index_of_enchant;
		if ((index_of_enchant < 0) || (index_of_enchant >(equipmentList[index]->getEnch().size() - 1))) {
			cout << "Invalid index, please try again." << endl;
			cin.clear();
			fflush(stdin);
		}
		else {
			equipmentList[index]->getEnch()[index_of_enchant]->print();
			cout << "What would you like to do? Enter -1 to cancel." << endl;
			cout << "1. Change enchant value" << endl;
			cout << "2. Remove the enchant" << endl;

			int enchantChoice;
			cin >> enchantChoice;
			switch (enchantChoice) {
			case 1:
				cout << "Please enter your new value for the enchant." << endl;
				cin >> newEnchantValue;
				equipmentList[index]->getEnch()[index_of_enchant]->setValue(newEnchantValue);
				cout << "Enchant value has been set to " << equipmentList[index]->getEnch()[index_of_enchant]->getValue() << endl;

				loop = false;
				break;
			case 2:
				cout << "Enchantment has been removed." << endl;
				equipmentList[index]->removeEnch(index_of_enchant);
				loop = false;
				break;
			case -1:
				return;
				break;
			default:
				cout << "Invalid choice. Please enter 1 or 2." << endl;
				cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}



void editEnchantments_w(vector<Weapon*>& weaponList, int index) {
	cout << "Item " << weaponList[index]->getName() << "'s list of enchants:" << endl;
	for (int i = 0; i < weaponList[index]->getEnch().size(); i++) {
		cout << i << ". ";
		weaponList[index]->getEnch()[i]->print();
	}
	cout << "Enter the index of the enchantment item \"" << weaponList[index]->getName() << "\" has that you would like to edit." << endl;

	int index_of_enchant;
	int newEnchantValue;
	bool loop = true;
	while (loop) {
		cin >> index_of_enchant;
		if ((index_of_enchant < 0) || (index_of_enchant >(weaponList[index]->getEnch().size() - 1))) {
			cout << "Invalid index, please try again." << endl;
			cin.clear();
			fflush(stdin);
		}
		else {
			weaponList[index]->getEnch()[index_of_enchant]->print();
			cout << "What would you like to do? Enter -1 to cancel." << endl;
			cout << "1. Change enchant value" << endl;
			cout << "2. Remove the enchant" << endl;

			int enchantChoice;
			cin >> enchantChoice;
			switch (enchantChoice) {
			case 1:
				cout << "Please enter your new value for the enchant." << endl;
				cin >> newEnchantValue;
				weaponList[index]->getEnch()[index_of_enchant]->setValue(newEnchantValue);
				cout << "Enchant value has been set to " << weaponList[index]->getEnch()[index_of_enchant]->getValue() << endl;

				loop = false;
				break;
			case 2:
				cout << "Enchantment has been removed." << endl;
				weaponList[index]->removeEnch(index_of_enchant);
				loop = false;
				break;
			case -1:
				return;
				break;
			default:
				cout << "Invalid choice. Please enter 1 or 2." << endl;
				cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}



//! function for displaying all contents of a vector that stores equipments of a certain type
//! @param equipmentList: the vector that stores equipments of a specific type
//! @param equipmentTypeC: just the name of the equipment type, capitalized (i.e. Shield, Helmet, etc)
//! @param equipmentType: just the name of the equipment type, not capitalized (i.e. shield, helmet, etc)
void equipmentList_display(vector<Equipment*>& equipmentList, string equipmentTypeC, string equipmentType)
{
	if (equipmentList.size() > 0)
	{
		cout << "Displaying stored " << equipmentType << "s: " << endl;
		for (int i = 0; i < equipmentList.size(); i++)
		{
			cout << i << ". ";
			equipmentList[i]->print();
		}
		cout << endl;
	}
	else cout << equipmentTypeC << " list is empty." << endl;
}

void weaponList_display(bool isMelee)
{
	if (isMelee)
	{
		if (meleeWeaponList.size() > 0)
		{
			cout << "Displaying stored melee weapons:" << endl;
			for (int i = 0; i < meleeWeaponList.size(); i++)
			{
				cout << i << ". ";
				meleeWeaponList[i]->print();
			}
			cout << endl;
		}
		else cout << "Melee weapon list is empty." << endl;
	}
	else
	{
		if (rangedWeaponList.size() > 0)
		{
			cout << "Displaying stored ranged weapons:" << endl;
			for (int i = 0; i < rangedWeaponList.size(); i++)
			{
				cout << i << ". ";
				rangedWeaponList[i]->print();
			}
			cout << endl;
		}
		else cout << "Ranged weapon list is empty." << endl;
	}
}

void itemContainerList_display()
{
	if (itemContainerList.size() > 0)
	{
		cout << "Displaying stored item containers:" << endl;
		for (int i = 0; i < itemContainerList.size(); i++)
		{
			cout << "Item Container at Index #" << i << endl;
			itemContainerList[i]->printContents();
		}
		cout << endl;
	}
	else cout << "Item container list is empty." << endl;
}






/////////////////////////////////////////////////////////
//
//
// CHARACTER-CREATION RELATED FUNCTIONS
//
//
//
/////////////////////////////////////////////////////////

void playable_character_creation(vector<Character*>& playableCharacters) {
	cout << "Playable Character Creator" << endl
		<< "==========================" << endl;

	//variables representing whether or not user wants to continue building characters
	bool wantToKeepMakingCharacters = true;
	while (wantToKeepMakingCharacters) {
		cout << "Character Name: ";
		string name;
		std::cin >> name;

		std::cout << "Level: ";
		int level;
		std::cin >> level;

		std::cout << "Rolling stats..." << endl;
		std::vector<int> vec;
		std::vector<int> attributes;

		bool didntChooseReroll = false;
		while (!didntChooseReroll) {
			attributes.clear();
			//rolling for initial stats
			// Rolls 4d20 and keeps the three highest rolls for each ability score
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 4; j++) {
					vec.push_back(Dice::roll("d6"));
				}
				std::sort(vec.begin(), vec.end(), std::greater<int>());
				attributes.push_back(vec[0] + vec[1] + vec[2]);
				vec.clear();
			}
			//sorting stats;
			std::sort(attributes.begin(), attributes.begin() + 6, std::greater<int>());

			cout << "Here are your possible fighter build choices: \n" << endl;

			//Bully build: str > con > dex > int > cha > wis
			cout << "BULLY:" << endl;
			cout << "Strength: " << attributes[0] << endl;
			cout << "Dexterity: " << attributes[2] << endl;
			cout << "Constitution: " << attributes[1] << endl;
			cout << "Intelligence: " << attributes[3] << endl;
			cout << "Wisdom: " << attributes[5] << endl;
			cout << "Charisma: " << attributes[4] << endl;
			cout << endl;

			//Nimble build: dex > con > str > int > cha > wis
			cout << "NIMBLE:" << endl;
			cout << "Strength: " << attributes[2] << endl;
			cout << "Dexterity: " << attributes[0] << endl;
			cout << "Constitution: " << attributes[1] << endl;
			cout << "Intelligence: " << attributes[3] << endl;
			cout << "Wisdom: " << attributes[5] << endl;
			cout << "Charisma: " << attributes[4] << endl;
			cout << endl;

			//Tank build: con > dex > str > int > cha > wis
			cout << "TANK:" << endl;
			cout << "Strength: " << attributes[2] << endl;
			cout << "Dexterity: " << attributes[1] << endl;
			cout << "Constitution: " << attributes[0] << endl;
			cout << "Intelligence: " << attributes[3] << endl;
			cout << "Wisdom: " << attributes[5] << endl;
			cout << "Charisma: " << attributes[4] << endl;
			cout << endl;

			cout << "Which one of these would you like?" << endl;
			cout << "1. Bully" << endl;
			cout << "2. Nimble" << endl;
			cout << "3. Tank" << endl;
			cout << "4. I don't like any of them. Re-roll." << endl;

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
					std::cout << "Creating bully type fighter class character..." << endl;
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
						std::cout << "Would you like to save this character? (1 = Yes,  2 = No)" << endl;
						while (!has_chosen_to_save_or_not) {
							std::cin >> save_or_not;
							switch (save_or_not) {
							case 1:
								playableCharacters.push_back(createdFighter);
								//maybe save to file here?
								std::cout << "New playable character " << playableCharacters[playableCharacters.size() - 1]->getCharacterName() << " has been saved." << endl;
								has_chosen_to_save_or_not = true;
								break;
							case 2:
								std::cout << "New playable character has not been saved." << endl;
								has_chosen_to_save_or_not = true;
								break;
							default:
								std::cout << "Please enter either 1 or 2." << endl;
								cin.clear();
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
					std::cout << "Creating nimble type fighter class character..." << endl;
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
						std::cout << "Would you like to save this character? (1 = Yes,  2 = No)" << endl;
						while (!has_chosen_to_save_or_not) {
							std::cin >> save_or_not;
							switch (save_or_not) {
							case 1:
								playableCharacters.push_back(createdFighter);
								//maybe save to file here?
								std::cout << "New playable character " << playableCharacters[playableCharacters.size() - 1]->getCharacterName() << " has been saved." << endl;
								has_chosen_to_save_or_not = true;
								break;
							case 2:
								std::cout << "New playable character has not been saved." << endl;
								has_chosen_to_save_or_not = true;
								break;
							default:
								std::cout << "Please enter either 1 or 2." << endl;
								cin.clear();
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
					std::cout << "Creating tank type fighter class character..." << endl;
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
						std::cout << "Would you like to save this character? (1 = Yes,  2 = No)" << endl;
						while (!has_chosen_to_save_or_not) {
							std::cin >> save_or_not;
							switch (save_or_not) {
							case 1:
								playableCharacters.push_back(createdFighter);
								//maybe save to file here?
								std::cout << "New playable character " << playableCharacters[playableCharacters.size() - 1]->getCharacterName() << " has been saved." << endl;
								has_chosen_to_save_or_not = true;
								break;
							case 2:
								std::cout << "New playable character has not been saved." << endl;
								has_chosen_to_save_or_not = true;
								break;
							default:
								std::cout << "Please enter either 1 or 2." << endl;
								cin.clear();
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
					cout << "\nRe-rolling stats..." << endl;
					//starting roll from scratch, breaking out of inner while loop, but not the outer one
					validFighterBuildChoice = true;
					skipNewCharacter = true;
					break;
				default:
					cout << "Invalid choice. Please choose a number between 1 and 4." << endl;
					cin.clear();
					fflush(stdin);
					break;
				}
			}
			//prompting whether or not the user would like to create a new player character
			if (!skipNewCharacter) {
				cout << "Would you like to create another player character? ( 1 = yes, 2 = no)" << endl;
				int anotherCharacter;
				bool anotherCharValidChoice = false;
				while (!anotherCharValidChoice) {
					cin >> anotherCharacter;
					switch (anotherCharacter) {
					case 1:
						anotherCharValidChoice = true;
						cout << "You have chosen to create another player character." << endl;
						break;
					case 2:
						wantToKeepMakingCharacters = false;
						anotherCharValidChoice = true;
						cout << "Returning to character creation menu." << endl;
						break;
					default:
						cout << "Please enter either 1 or 2." << endl;
						cin.clear();
						fflush(stdin);
						break;
					}
				}
			}
		}
	}
}

//! function for NPC creation
//! @param nonPlayerCharacters: one of the two vector containing NPCs (hostile or friendly)
//! @param friendly: determines whether a friendly or hostile NPC is being created
void npc_creation(vector<Character*>& nonPlayerCharacters, bool friendly) {
	cout << "Non-Playable Character Creator " << (friendly ? "(friendly)" : "(hostile)") << endl
		<< "=========================================" << endl;

	//variables representing whether or not user wants to continue building characters
	bool wantToKeepMakingCharacters = true;
	while (wantToKeepMakingCharacters) {
		string name, charaType;
		int lvl, str, dex, con, intel, wis, cha;
		cout << "Character Name: ";
		std::cin >> name;
		cout << "Character Type: ";
		std::cin >> charaType;
		std::cout << "Level: ";
		std::cin >> lvl;
		cin.clear();
		fflush(stdin);
		std::cout << "Strength: ";
		std::cin >> str;
		cin.clear();
		fflush(stdin);
		std::cout << "Dexterity: ";
		std::cin >> dex;
		cin.clear();
		fflush(stdin);
		std::cout << "Constitution: ";
		std::cin >> con;
		cin.clear();
		fflush(stdin);
		std::cout << "Intelligence: ";
		std::cin >> intel;
		cin.clear();
		fflush(stdin);
		std::cout << "Wisdom: ";
		std::cin >> wis;
		cin.clear();
		fflush(stdin);
		std::cout << "Charisma: ";
		std::cin >> cha;
		cin.clear();
		fflush(stdin);

		Character* newChara = new Character(name, charaType, lvl, str, dex, con, intel, wis, cha);

		if (newChara->validateNewNPC()) {
			std::cout << "New " << (friendly ? "friendly" : "hostile") << "character created." << endl;
			newChara->printStats();

			std::cout << "Would you like to save this character? (1 = Yes,  2 = No)" << endl;
			int save_or_not;
			bool has_chosen_to_save_or_not = false;
			while (!has_chosen_to_save_or_not) {
				std::cin >> save_or_not;
				switch (save_or_not) {
				case 1:
					nonPlayerCharacters.push_back(newChara);
					std::cout << "New " << (friendly ? "friendly" : "hostile") << " character has been saved." << endl;
					has_chosen_to_save_or_not = true;
					break;
				case 2:
					std::cout << "New " << (friendly ? "friendly" : "hostile") << " character has not been saved." << endl;
					has_chosen_to_save_or_not = true;
					break;
				default:
					std::cout << "Please enter either 1 or 2." << endl;
					cin.clear();
					fflush(stdin);
					break;
				}
			}
		}
		else std::cout << "New " << (friendly ? "friendly" : "hostile") << " character could not be validated." << endl;

		std::cout << "Would you like to keep making " << (friendly ? "friendly" : "hostile") << " NPCs?" << endl;
		std::cout << "1. Yes" << endl;
		std::cout << "2. No" << endl;

		int selection;
		bool validSelection = false;
		while (!validSelection) {
			cin >> selection;
			switch (selection) {
			case 1:
				std::cout << "Creating new " << (friendly ? "friendly" : "hostile") << " character..." << endl;
				validSelection = true;
				break;
			case 2:
				std::cout << "Returning to character creation menu." << endl;
				validSelection = true;
				wantToKeepMakingCharacters = false;
				break;
			default:
				std::cout << "Please select either 1 or 2." << endl;
				cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}

//! function for displaying all stored characters in a vector, along with their respective vector indices
//! @param characterList: the list of character to print out
void displayAllCharacters(vector<Character*>& characterList) {
	if (characterList.size() == 0) {
		std::cout << "Character list is empty." << endl;
		return;
	}
	else {
		std::cout << "Displaying stored characters..." << endl;
		for (int i = 0; i < characterList.size(); i++) {
			std::cout << i << ". " << "Name: " << characterList[i]->getCharacterName() << " Class: " << characterList[i]->getCharacterClass() << " Level: " << characterList[i]->getLevel() << endl;
		}
	}
}

void displayDetailedInfo(vector<Character*>& characterList, int index) {
	Character* chara = characterList[index];
	std::cout << "Displaying character stored at index " << index << "..." << endl;
	std::cout << "NAME: " << chara->getCharacterName() << endl;
	std::cout << "CLASS: " << chara->getCharacterClass() << endl;
	std::cout << "LEVEL: " << chara->getLevel() << endl;
	std::cout << "EXP: " << chara->getExpPoints() << endl;
	std::cout << "CURRENT HIT POINTS: " << chara->getCurrentHitPoints() << endl;
	std::cout << "MAX HIT POINTS: " << chara->getMaxHitPoints() << endl;
	std::cout << "STR: " << chara->getStrength() << " (modifier: " << chara->getStrengthModifier() << ")" << endl;
	std::cout << "DEX: " << chara->getDexterity() << " (modifier: " << chara->getDexterityModifier() << ")" << endl;
	std::cout << "CON: " << chara->getConstitution() << " (modifier: " << chara->getConstitutionModifier() << ")" << endl;
	std::cout << "INT: " << chara->getIntelligence() << " (modifier: " << chara->getIntelligenceModifier() << ")" << endl;
	std::cout << "WIS: " << chara->getWisdom() << " (modifier: " << chara->getWisdomModifier() << ")" << endl;
	std::cout << "CHA: " << chara->getCharisma() << " (modifier: " << chara->getCharismaModifier() << ")" << endl;
	std::cout << "ARMOR CLASS: " << chara->getArmorClass() << endl;
	std::cout << "BASE ATTACK BONUS: " << "+" << chara->getBaseAttackBonus(0);
	if (chara->getLevel() > 5)
		std::cout << "/+" << chara->getBaseAttackBonus(1);
	if (chara->getLevel() > 10)
		std::cout << "/+" << chara->getBaseAttackBonus(2);
	if (chara->getLevel() > 15)
		std::cout << "/+" << chara->getBaseAttackBonus(3);
	std::cout << std::endl;
	//printing attack bonus
	cout << "ATTACK BONUS: " << ((chara->getAttackBonus(0) > (-1)) ? "+" : "") << chara->getAttackBonus(0);
	if (chara->getLevel() > 5)
		cout << ((chara->getAttackBonus(1) > (-1)) ? "/+" : "/") << chara->getAttackBonus(1);
	if (chara->getLevel() > 10)
		cout << ((chara->getAttackBonus(2) > (-1)) ? "/+" : "/") << chara->getAttackBonus(2);
	if (chara->getLevel() > 15)
		cout << ((chara->getAttackBonus(3) > (-1)) ? "/+" : "/") << chara->getAttackBonus(3);
	cout << endl;
	cout << "DAMAGE BONUS: " << chara->getDamageBonus() << endl;
}

//! function for displaying character info in higher detail, will be prompted to enter a certain index to use to retrieve the character info from the vector
//! @param characterList: the list of character from a single character's info is retrieved
void displayCharacterDetails(vector<Character*>& characterList) {
	if (characterList.size() == 0) {
		std::cout << "Character list is empty." << endl;
		return;
	}
	std::cout << "Please enter the index of the character whose information you would like to see: ";

	bool validIndexSelection = false;
	int index;
	while (!validIndexSelection) {
		cin >> index;
		if ((index < 0) || (index >(characterList.size() - 1))) {
			std::cout << "Invalid selection. Please try again." << std::endl;
			cin.clear();
			fflush(stdin);
		}
		else {
			validIndexSelection = true;
			displayDetailedInfo(characterList, index);
		}
	}
}

void enemy_npc_creation(vector<Character*>& hostileCharacters) {
	npc_creation(hostileCharacters, false);
}

void friendly_npc_creation(vector<Character*>& friendlyCharacters) {
	npc_creation(friendlyCharacters, true);
}

void editCharacterAtIndex(vector<Character*>& characterList, bool hasPlayerCharaValidationCond) {
	if (characterList.size() == 0) {
		std::cout << "Character list is empty." << endl;
		return;
	}
	bool validSelection = false;
	bool quitCharaEdit = false;
	int index, statEdit;
	string inString;
	int inInt;

	displayAllCharacters(characterList);
	std::cout << "\nPlease enter the index of the character you would like to edit." << endl;

	while (!validSelection) {
		std::cin >> index;
		if ((index < 0) || (index >(characterList.size() - 1))) {
			std::cout << "Invalid selection. Please try again." << std::endl;
			cin.clear();
			fflush(stdin);
		}
		else {
			displayDetailedInfo(characterList, index);
			std::cout << "\nPlease select what you would like to edit. Enter -1 to quit character edit mode." << endl;
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
				std::cout << "Character's name changed from \"" << characterList[index]->getCharacterName() << "\" to \"" << inString << "\"." << endl;
				characterList[index]->setName(inString);
				std::cout << endl;
				std::cout << "Character after edit:" << std::endl;
				std::cout << endl;
				displayDetailedInfo(characterList, index);
				validSelection = true;
				break;
			case 2:
				std::cout << "Please enter your new desired character class: ";
				std::cin >> inString;
				if (!hasPlayerCharaValidationCond) {
					std::cout << "Character's class changed from \"" << characterList[index]->getCharacterClass() << "\" to \"" << inString << "\"." << endl;
					characterList[index]->setClass(inString);
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
					displayDetailedInfo(characterList, index);
				}
				else std::cout << "Player characters may only be of fighter class." << std::endl;
				validSelection = true;
				break;
			case 3:
				std::cout << "Please enter your new desired character level: ";
				std::cin >> statEdit;
				if (statEdit > -1) {
					std::cout << "Character's level changed from \"" << characterList[index]->getLevel() << "\" to \"" << statEdit << "\"." << endl;
					characterList[index]->setLevel(statEdit);
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
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
					std::cout << characterList[index]->getExpPoints() << "\"." << endl;
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
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
				std::cout << characterList[index]->getCurrentHitPoints() << "\"." << endl;
				std::cout << endl;
				std::cout << "Character after edit:" << std::endl;
				std::cout << endl;
				displayDetailedInfo(characterList, index);
				validSelection = true;
				break;
			case 6:
				std::cout << "Please enter your new desired character strength: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					characterList[index]->setStrength(statEdit);
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				std::cout << "Character's strength has been changed from \"" << characterList[index]->getStrength() << "\" to \"" << statEdit << "\"." << endl;
				break;
			case 7:
				std::cout << "Please enter your new desired character dexterity: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's dexterity has been changed from \"" << characterList[index]->getDexterity() << "\" to \"" << statEdit << "\"." << endl;
					characterList[index]->setDexterity(statEdit);
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				break;
			case 8:
				std::cout << "Please enter your new desired character constitution: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's constitution has been changed from \"" << characterList[index]->getConstitution() << "\" to \"" << statEdit << "\"." << endl;
					characterList[index]->setConstitution(statEdit);
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				break;
			case 9:
				std::cout << "Please enter your new desired character intelligence: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's intelligence has been changed from \"" << characterList[index]->getIntelligence() << "\" to \"" << statEdit << "\"." << endl;
					characterList[index]->setIntelligence(statEdit);
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				break;
			case 10:
				std::cout << "Please enter your new desired character wisdom: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's wisdom has been changed from \"" << characterList[index]->getWisdom() << "\" to \"" << statEdit << "\"." << endl;
					characterList[index]->setWisdom(statEdit);
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
					displayDetailedInfo(characterList, index);
					validSelection = true;
				}
				else std::cout << "Invalid value." << std::endl;
				break;
			case 11:
				std::cout << "Please enter your new desired character charisma: ";
				std::cin >> statEdit;
				if (((!hasPlayerCharaValidationCond) && (statEdit > 0)) || ((hasPlayerCharaValidationCond) && (statEdit > 3) && (statEdit < 18))) {
					std::cout << "Character's charisma has been changed from \"" << characterList[index]->getLevel() << "\" to \"" << statEdit << "\"." << endl;
					characterList[index]->setCharisma(statEdit);
					std::cout << endl;
					std::cout << "Character after edit:" << std::endl;
					std::cout << endl;
					displayDetailedInfo(characterList, index);
				}
				else std::cout << "Invalid value." << std::endl;
				validSelection = true;
				break;
			default:
				std::cout << "Please enter either a number from 1 to 11, or -1 to cancel." << endl;
				cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}

void deleteCharacterAtIndex(vector<Character*>& characterList) {
	if (characterList.size() == 0) {
		std::cout << "Character list is empty." << endl;
		return;
	}


	std::cout << "Please enter the index number of the character you would like to delete. Enter '-1' (minus quotations) to cancel." << std::endl;

	int index;
	bool validSelection = false;

	while (!validSelection) {
		std::cin >> index;

		if (index == (-1)) {
			std::cout << "Deletion request cancelled." << endl;
			return;
		}

		if ((index < (-1)) || (index >(characterList.size() - 1))) {
			std::cout << "Invalid selection. Please try again." << std::endl;
			cin.clear();
			fflush(stdin);
		}
		else {
			std::cout << "Character " << characterList[index]->getCharacterName() << " has been deleted." << endl;
			characterList.erase(characterList.begin() + index);
			return;
		}
	}
}

void character_edit_mode(vector<Character*>& characterList, string characterTypeCap, string characterType, bool hasPlayerCharaValidationCond) {
	std::cout << characterTypeCap << " Character Edit Mode" << std::endl;
	std::cout << "============================" << std::endl;
	std::cout << "What would you like to do?" << std::endl;
	std::cout << "1. Display stored characters" << endl;
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
			cin.clear();
			fflush(stdin);
			break;
		}
	}
}

void characterMakerMainMenu(vector<Character*>& playableCharacters, vector<Character*>& hostileCharacters, vector<Character*>& friendlyCharacters) {
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
				character_edit_mode(friendlyCharacters, "Friendly", "friendly", false);
				validCharaTypeSelection = true;
				break;
			case 7:
				wantToQuit = true;
				validCharaTypeSelection = true;
				cout << "Returning to creator mode menu." << endl;
				break;
			default:
				std::cout << "Invalid choice. Please choose a number between 1 and 4." << endl;
				cin.clear();
				fflush(stdin);
				break;
			}
		}
	}
}