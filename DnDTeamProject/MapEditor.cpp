#include <conio.h>
#include "ItemBuilder.h"
#include "MapEditor.h"
#include "Menu.h"
#include "FileIO.h"
#include "Cursor.h"
#include "CursorObserver.h"
#include "CharacterEditor.h"
#include "Names.h"
#include "Dice.h"



MapEditor::MapEditor() : _loadedMaps(std::vector<Map*>()) {
}


MapEditor::~MapEditor() {
}

Map * MapEditor::getMap() {
	return _map;
}

void MapEditor::setMap(Map * map) {
	_map = map;
}

void MapEditor::newMap() {
	_map = new Map();

   //Initalize dimensions
	bool initializingDimensions = true;
	while (initializingDimensions) {
		std::cout << "Creating a new map..." << std::endl << std::endl;

		std::cout << "[?] What are the dimensions of the map?" << std::endl;
		std::cout << "   Width (3-233): ";
		int width = getUserInputInteger();
		std::cout << "   Height (3-40): ";
		int height = getUserInputInteger();
		if (width >= 3 && width <= 233 && height >= 3 && height <= 40) {
			std::cout << std::endl;
			_map = new Map(width, height);
			initializingDimensions = false;
			system("cls");
		}
		else {
			system("cls");
			std::cout << "Invalid map dimensions!" << std::endl << std::endl;
		}
	}

	//Initialize name
	std::string mapName;
	bool choosingRandomName = true;
	switch (menu(builderNameOptions, "What is the map called?")) {
	case 1:
		while (choosingRandomName) {
			mapName = dungeonNames[Dice::roll("d" + std::to_string((dungeonNames.size()))) - 1];
			std::cout << "The map is called " << mapName << std::endl << std::endl;
			if (menu(yesNoOptions, "Are you happy with this map name?") == 1) {
				choosingRandomName = false;
				_map->setName(mapName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a map name: ";
		_map->setName(getUserInputString());
		std::cout << _map->getName() << " has been created." << std::endl << std::endl;
		break;
	}
	editMap();
}

void MapEditor::editMap() {
	bool editingMap = true;
	bool editingLayout = true;
	bool choosingRandomName = true;
	Chest* editedChest;
	std::string infoSuffix, mapName;
	Cursor* editorCursor;
	CursorObserver* cursorObserver;

	_map->setDrawModeLOS(false);

	while (editingMap) {

		_map->setDrawPrefix("Editing " + _map->getName() + "...");
		_map->draw();
		switch (menu(mapEditorMenuOptions, "What part of " + _map->getName() + " do you want to edit?")) {
		case 1: //Edit name
			switch (menu(builderNameOptions, "What is the map called?")) {
			case 1:
				choosingRandomName = true;
				while (choosingRandomName) {
					mapName = dungeonNames[Dice::roll("d" + std::to_string((dungeonNames.size()))) - 1];
					std::cout << "The map is called " << mapName << std::endl << std::endl;
					if (menu(yesNoOptions, "Are you happy with this map name?") == 1) {
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
			break;

		case 2: //Edit layout
			editorCursor = new Cursor();
			cursorObserver = new CursorObserver(editorCursor, _map);
			_map->setCursor(editorCursor);
			infoSuffix = std::string("Editing map layout...\n\n")
				+ "Use [Arrow keys] or [W, A, S, D] to move the cursor.\n\n"
				+ "Press the following keys to insert objects at the cursor location:\n"
				+ "  [0]\tEmpty space\n"
				+ "  [1]\tWall\n"
				+ "  [2]\tEntrance\n"
				+ "  [3]\tExit\n"
				+ "  [4]\tSaved character\n"
				+ "  [5]\tNew character\n"
				+ "  [6]\tChest\n"
				+ "Press the following keys to interact with characters and chests at the cursor location:\n"
				+ "  [7]\tInspect\n"
				+ "  [8]\tEdit\n"
				+ "  [9]\tRemove\n"
				+ "Press [Enter] to finish editing map layout.\n";
			_map->setDrawSuffix(infoSuffix);
			_map->draw();
			editingLayout = true;
			while (editingLayout) {
				_map->setDrawSuffix(infoSuffix);
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
				case '2': //Insert entrance (valid on edges except corners)
					if ((cursorX == 0 || cursorX == _map->getWidth() - 1 || cursorY == 0 || cursorY == _map->getHeight() - 1) &&
						(_map->getCell(cursorX, cursorY)->getSprite() == '#') && 
						!(cursorX == 0 && cursorY == 0) &&
						!(cursorX == 0 && cursorY == cursorY == _map->getHeight() - 1) &&
						!(cursorX == _map->getWidth() - 1 && cursorY == 0) &&
						!(cursorX == _map->getWidth() - 1 && cursorY == _map->getHeight() - 1) &&
						!(_map->isCellOccupied(cursorX, cursorY))) {

						_map->setEntry(cursorX, cursorY);
						_map->draw();
					}
					break;
				case '3': //Insert exit (valid on edges except corners)
					if ((cursorX == 0 || cursorX == _map->getWidth() - 1 || cursorY == 0 || cursorY == _map->getHeight() - 1) &&
						(_map->getCell(cursorX, cursorY)->getSprite() == '#') &&
						!(cursorX == 0 && cursorY == 0) &&
						!(cursorX == 0 && cursorY == cursorY == _map->getHeight() - 1) &&
						!(cursorX == _map->getWidth() - 1 && cursorY == 0) &&
						!(cursorX == _map->getWidth() - 1 && cursorY == _map->getHeight() - 1) &&
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
							Character* placedCharacter = loadedCharacters[menu(loadedCharactersMenuOptions, "Which character do you want to place here?") - 1];
							placedCharacter->setX(cursorX);
							placedCharacter->setY(cursorY);
							_map->addNpcCharacter(placedCharacter);
							_map->draw();
						}
						else {
							std::string drawSuffix = _map->getDrawSuffix();
							_map->setDrawSuffix(drawSuffix + "\nThere are no saved characters!");
							_map->draw();
						}
					}
					break;
				case '5': //Insert new character
					if ((_map->getCell(cursorX, cursorY)->getSprite() == '.') &&
						!(_map->isCellOccupied(cursorX, cursorY))) {
						system("cls");
						CharacterEditor characterEditor;
						characterEditor.newCharacter();
						Character* placedCharacter = characterEditor.getCharacter();
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
							_map->draw();
							std::vector<Item*> loadedItems, chestItems;
							std::vector<std::string> loadedItemsMenuOptions, chestItemsMenuOptions;
							ItemBuilder itemBuilder;
							switch (menu(mapBuilderChestOptions, "Modifying chest contents...")) {
							case 1: //Add a saved item
								_map->draw();
								loadedItems = loadItems().getItemArchive();
								if (loadedItems.size() > 0) {
									for (int i = 0, n = loadedItems.size(); i < n; ++i) {
										loadedItemsMenuOptions.push_back(loadedItems[i]->toString());
									}
									placedChest->depositItem(*loadedItems[menu(loadedItemsMenuOptions, "Which item do you want to add?") - 1]);
								}
								break;
							case 2: //Add a new item
								itemBuilder.newItem();
								placedChest->depositItem(*itemBuilder.getItem());
								break;
							case 3: //Withdraw an item
								_map->draw();
								if (placedChest->getContents().size() > 0) {
									for (int i = 0, n = placedChest->getContents().size(); i < n; ++i) {
										chestItemsMenuOptions.push_back(placedChest->getContents()[i]->toString());
									}
									chestItemsMenuOptions.push_back("Cancel");
									int choice = menu(chestItemsMenuOptions, "Which item do you want to remove?");
									if (choice != chestItemsMenuOptions.size())
										placedChest->withdrawItem(-1);
								}
								break;
							case 4:
								_map->draw();
								_map->addChest(placedChest);
								fillingChest = false;
								break;
							}
						}
						_map->draw();
					}
					break;
				case '7': //Inspect
					for (int i = 0, n = _map->getNpcCharacters().size(); i < n; ++i) {
						if (_map->getNpcCharacters()[i]->getX() == cursorX && _map->getNpcCharacters()[i]->getY() == cursorY) {
							_map->setDrawSuffix(infoSuffix + "\n" + _map->getNpcCharacters()[i]->toString());
							_map->draw();
						}
					}
					for (int i = 0, n = _map->getChests().size(); i < n; ++i) {
						if (_map->getChests()[i]->getX() == cursorX && _map->getChests()[i]->getY() == cursorY) {
							_map->setDrawSuffix(infoSuffix + "\n" + _map->getChests()[i]->toString());
							_map->draw();
						}
					}
					break;
				case '8': //Edit
					for (int i = 0, n = _map->getNpcCharacters().size(); i < n; ++i) {
						if (_map->getNpcCharacters()[i]->getX() == cursorX && _map->getNpcCharacters()[i]->getY() == cursorY) {
							system("cls");
							CharacterEditor characterEditor;
							characterEditor.setCharacter(_map->getNpcCharacters()[i]);
							characterEditor.editCharacter();
						}
					}
					for (int i = 0, n = _map->getChests().size(); i < n; ++i) {
						if (_map->getChests()[i]->getX() == cursorX && _map->getChests()[i]->getY() == cursorY) {

							system("cls");
							editedChest = _map->getChests()[i];
							bool fillingChest = true;
							while (fillingChest) {
								std::cout << editedChest->toString() << std::endl << std::endl;
								std::vector<Item*> loadedItems, chestItems;
								std::vector<std::string> loadedItemsMenuOptions, chestItemsMenuOptions;
								ItemBuilder itemBuilder;
								switch (menu(mapBuilderChestOptions, "Modifying chest contents...")) {
								case 1: //Add a saved item
									std::cout << editedChest->toString() << std::endl << std::endl;
									loadedItems = loadItems().getItemArchive();
									if (loadedItems.size() > 0) {
										for (int i = 0, n = loadedItems.size(); i < n; ++i) {
											loadedItemsMenuOptions.push_back(loadedItems[i]->toString());
										}
										editedChest->depositItem(*loadedItems[menu(loadedItemsMenuOptions, "Which item do you want to add?") - 1]);
									}
									break;
								case 2: //Add a new item
									itemBuilder.newItem();
									editedChest->depositItem(*itemBuilder.getItem());
									break;
								case 3: //Withdraw an item
									std::cout << editedChest->toString() << std::endl << std::endl;
									if (editedChest->getContents().size() > 0) {
										for (int i = 0, n = editedChest->getContents().size(); i < n; ++i) {
											chestItemsMenuOptions.push_back(editedChest->getContents()[i]->toString());
										}
										chestItemsMenuOptions.push_back("Cancel");
										int choice = menu(chestItemsMenuOptions, "Which item do you want to remove?");
										if (choice != chestItemsMenuOptions.size())
											editedChest->withdrawItem(choice - 1);
									}
									break;
								case 4:
									_map->draw();
									fillingChest = false;
									break;
								}
							}
						}
					}
					_map->draw();
					break;
				case '9': //Remove
					for (int i = 0, n = _map->getNpcCharacters().size(); i < n; ++i) {
						if (_map->getNpcCharacters()[i]->getX() == cursorX && _map->getNpcCharacters()[i]->getY() == cursorY) {
							_map->getNpcCharacters().erase(_map->getNpcCharacters().begin() + i);
						}
					}
					for (int i = 0, n = _map->getChests().size(); i < n; ++i) {
						if (_map->getChests()[i]->getX() == cursorX && _map->getChests()[i]->getY() == cursorY) {
							if (_map->getChests()[i]->getX() == cursorX && _map->getChests()[i]->getY() == cursorY) {
								_map->getChests().erase(_map->getChests().begin() + i);
							}
						}
					}
					break;
				case '\r': //Finished
					if (_map->validateA()) {
						editingLayout = false;
						delete editorCursor;
						delete cursorObserver;
						_map->setCursor(NULL);
						_map->setDrawSuffix("");
						system("cls");
					}
					else {
						std::string drawSuffix = _map->getDrawSuffix();
						_map->setDrawSuffix(drawSuffix + "\nMap is invalid! There must be a clear path from the entrance to the exit.");
						_map->draw();
					}
					break;
				} //END Switch: keypress
			} //END Case: Edit Layout
			break;

		case 3: //Finished
			editingMap = false;
			if (_loadedMaps.size() > 0)
				saveMaps(_loadedMaps);
			else
				saveMap(_map);
			system("cls");
			std::cout << _map->getName() << " was saved!" << std::endl << std::endl;
			break;
		} //END Switch editingMap
	} //END Loop editingMap
}

bool MapEditor::loadMap() {
	_loadedMaps = loadMaps();
	if (_loadedMaps.size() > 0) {
		std::vector<std::string> loadedMapsMenuOptions;
		for (int i = 0, n = _loadedMaps.size(); i < n; ++i) {
			loadedMapsMenuOptions.push_back(_loadedMaps[i]->getName() + "\n" + _loadedMaps[i]->drawToString());
		}
		loadedMapsMenuOptions.push_back("Cancel");
		int editIndex = menu(loadedMapsMenuOptions, "Which map do you want to edit?") - 1;
		if (editIndex == loadedMapsMenuOptions.size() - 1)
			return false;
		_map = _loadedMaps[editIndex];
		return true;
	}
	else {
		std::cout << "There are no saved maps to edit!" << std::endl << std::endl;
		std::cout << "Press any key to continue..." << std::endl;
		_getch();
		system("cls");
		return false;
	}
}
