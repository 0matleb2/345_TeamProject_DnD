#include <conio.h>
#include "MapBuilder.h"
#include "Menu.h"
#include "Names.h"
#include "Dice.h"
#include "CursorObserver.h"
#include "FileIO.h"
#include "CharacterBuilder.h"
#include "ItemBuilder.h"
#include "Chest.h"

MapBuilder::MapBuilder() {
}


MapBuilder::~MapBuilder() {
}

Map * MapBuilder::getMap() {
	return _map;
}

void MapBuilder::construct() {
	std::cout << "Creating a new map..." << std::endl << std::endl;
	buildDimensions();
	buildName();
	buildLayout();
	saveMap(_map);
}

void MapBuilder::buildDimensions() {
	std::cout << "What are the dimensions of the map?" << std::endl;
	std::cout << "Width: ";
	int width = getUserInputInteger();
	std::cout << "Height: ";
	int height = getUserInputInteger();
	std::cout << std::endl;
	_map = new Map(width, height);
	Cursor* editorCursor = new Cursor();
	CursorObserver* cursorObserver = new CursorObserver(editorCursor, _map);
	_map->setCursor(editorCursor);
}

void MapBuilder::buildName() {
	std::string mapName;
	bool choosingRandomName = true;
	std::cout << "What is the map called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			mapName = dungeonNames[Dice::roll("d"+ std::to_string((dungeonNames.size()))) - 1];
			std::cout << "The map is called " << mapName << std::endl << std::endl;
			std::cout << "Are you happy with this map name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				_map->setName(mapName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		_map->setName(getUserInputString());
		std::cout << "The map is called " << _map->getName() << "." << std::endl << std::endl;
		break;
	}
}


void MapBuilder::buildLayout() {
	bool editingLayout = true;
	std::string infoSuffix = std::string("Editing map layout...\n\n")
		+ "Use [Arrow keys] or [W, A, S, D] to move the cursor.\n\n"
		+ "Press the following keys to insert objects at the cursor location:\n"
		+ "  [0]\tEmpty space\n"
		+ "  [1]\tWall\n"
		+ "  [2]\tEntrance\n"
		+ "  [3]\tExit\n"
		+ "  [4]\tSaved character\n"
		+ "  [5]\tNew character\n"
		+ "  [6]\tChest\n"
		+ "Press [Enter] to finish editing map layout.\n";
	_map->setDrawSuffix(infoSuffix);
	_map->draw();
	while (editingLayout) {
		int cursorX = _map->getCursor()->getX();
		int cursorY = _map->getCursor()->getY();
		unsigned char keypress = _getch();
		if (keypress == 0 || keypress == 0xE0) { // Arrow key presses require this first char to be ignored
			keypress = _getch();
		}
		switch (keypress) {
		case 'W':
		case 'w':
		case 72: //Arrow key UP
			if (cursorY > 0)
				_map->getCursor()->setY(cursorY - 1);
			break;
		case 'A':
		case 'a':
		case 75: //Arrow key LEFT
			if (cursorX > 0)
				_map->getCursor()->setX(cursorX - 1);
			break;
		case 'S':
		case 's':
		case 80: //Arrow key DOWN
			if (cursorY < (_map->getHeight() - 1))
				_map->getCursor()->setY(cursorY + 1);
			break;
		case 'D':
		case 'd':
		case 77: //Arrow key RIGHT
			if (cursorX < (_map->getWidth() - 1))
				_map->getCursor()->setX(cursorX + 1);
			break;
		case '0': //Insert empty space
			if ((_map->getCell(cursorX, cursorY)->getSprite() != '/') && (_map->getCell(cursorX, cursorY)->getSprite() != '\\') &&
				!(cursorX == 0 || cursorX == _map->getWidth() - 1 || cursorY == 0 || cursorY == _map->getHeight() - 1) &&
				!(_map->isCellOccupied(cursorX, cursorY))) {

				_map->setCell(cursorX, cursorY, '.');
			}
			break;
		case '1': //Insert wall
			if ((_map->getCell(cursorX, cursorY)->getSprite() != '/') && (_map->getCell(cursorX, cursorY)->getSprite() != '\\') &&
				!(cursorX == 0 || cursorX == _map->getWidth() - 1 || cursorY == 0 || cursorY == _map->getHeight() - 1) &&
				!(_map->isCellOccupied(cursorX, cursorY))) {

				_map->setCell(cursorX, cursorY, '#');
			}
			break;
		case '2': //Insert entrance
			if ((cursorX == 0 || cursorX == _map->getWidth() - 1 || cursorY == 0 || cursorY == _map->getHeight() - 1) &&
				(_map->getCell(cursorX, cursorY)->getSprite() == '#') &&
				!(_map->isCellOccupied(cursorX, cursorY))) {

				_map->setEntry(cursorX, cursorY);
				_map->draw();
			}
			break;
		case '3': //Insert exit
			if ((cursorX == 0 || cursorX == _map->getWidth() - 1 || cursorY == 0 || cursorY == _map->getHeight() - 1) &&
				(_map->getCell(cursorX, cursorY)->getSprite() == '#') &&
				!(_map->isCellOccupied(cursorX, cursorY))) {

				_map->setExit(cursorX, cursorY);
				_map->draw();
			}
			break;
		case '4': //Insert saved character
			if ((_map->getCell(cursorX, cursorY)->getSprite() == '.') &&
				!(_map->isCellOccupied(cursorX, cursorY))) {

				std::vector<Character*> loadedCharacters = loadCharacters();
				std::vector<std::string> loadedCharactersMenuOptions;
				if (loadedCharacters.size() > 0) {
					for (int i = 0, n = loadedCharacters.size(); i < n; ++i) {
						loadedCharactersMenuOptions.push_back(loadedCharacters[i]->getName() + ", Level: " + std::to_string(loadedCharacters[i]->getLvl()));
					}
					std::cout << "Which character do you want to place here?" << std::endl;
					Character* placedCharacter = loadedCharacters[menu(loadedCharactersMenuOptions) - 1];
					placedCharacter->setX(cursorX);
					placedCharacter->setY(cursorY);
					_map->addNpcCharacter(placedCharacter);
					_map->draw();
				}
				else {
					std::string drawSuffix = _map->getDrawSuffix();
					_map->setDrawSuffix(drawSuffix + "\nThere are no saved characters!");
					_map->draw();
					_map->setDrawSuffix(drawSuffix);
				}
			}
			break;
		case '5': //Insert new character
			if ((_map->getCell(cursorX, cursorY)->getSprite() == '.') &&
				!(_map->isCellOccupied(cursorX, cursorY))) {

				CharacterBuilder characterBuilder;
				characterBuilder.construct();
				Character* placedCharacter = characterBuilder.getCharacter();
				placedCharacter->setX(cursorX);
				placedCharacter->setY(cursorY);
				_map->addNpcCharacter(placedCharacter);
				_map->draw();
			}
			break;
		case '6': //Insert chest
			if ((_map->getCell(cursorX, cursorY)->getSprite() == '.') &&
				!(_map->isCellOccupied(cursorX, cursorY))) {

				Chest* placedChest = new Chest(cursorX, cursorY);

				bool fillingChest = true;
				while (fillingChest) {
					std::vector<Item*> loadedItems, chestItems;
					std::vector<std::string> loadedItemsMenuOptions, chestItemsMenuOptions;
					ItemBuilder itemBuilder;
					std::cout << "Modifying chest contents..." << std::endl;
					switch (menu(mapBuilderChestOptions)) {
					case 1: //Add a saved item
						loadedItems = loadItems().getItemArchive();
						if (loadedItems.size() > 0) {
							std::cout << "Which item do you want to add?" << std::endl;
							for (int i = 0, n = loadedItems.size(); i < n; ++i) {
								loadedItemsMenuOptions.push_back(loadedItems[i]->toString());
							}
							placedChest->depositItem(*loadedItems[menu(loadedItemsMenuOptions) - 1]);
						}
						break;
					case 2: //Add a new item
						itemBuilder.construct();
						placedChest->depositItem(*itemBuilder.getItem());
						break;
					case 3: //Withdraw an item
						if (placedChest->getContents().size() > 0) {
							std::cout << "Which item do you want to add?" << std::endl;
							for (int i = 0, n = placedChest->getContents().size(); i < n; ++i) {
								chestItemsMenuOptions.push_back(placedChest->getContents()[i]->toString());
							}
							placedChest->withdrawItem(menu(chestItemsMenuOptions) - 1);
						}
						break;
					case 4:
						_map->addChest(placedChest);
						fillingChest = false;
						break;
					}
				}
				_map->draw();
			}
			break;
		case '\r': //Finished
			if (_map->validate()) {
				editingLayout = false;
			}
			else {
				std::string drawSuffix = _map->getDrawSuffix();
				_map->setDrawSuffix(drawSuffix + "\nMap is invalid! There must be a clear path from the entrance to the exit.");
				_map->draw();
				_map->setDrawSuffix(drawSuffix);
			}
			break;
		}
	}
}
