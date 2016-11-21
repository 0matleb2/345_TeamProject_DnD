#include <conio.h>
#include "MapBuilder.h"
#include "Menu.h"
#include "Names.h"
#include "Dice.h"
#include "CursorObserver.h"


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
	buildEntrance();
	buildExit();
	buildLayout();
	buildNPCs();
	buildChests();
}

void MapBuilder::buildDimensions() {
	std::cout << "What are the dimensions of the map?" << std::endl;
	std::cout << "Width: ";
	int width = getUserInputInteger();
	std::cout << "Height: ";
	int height = getUserInputInteger();
	std::cout << std::endl;
	_map = new Map(width, height);
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


void MapBuilder::buildEntrance() {
	std::cout << "Set the map entrance location." << std::endl;
	bool settingEntrance = true;
	Cursor* editorCursor = new Cursor();
	CursorObserver cursorObserver(editorCursor, _map);
	_map->setCursor(editorCursor);
	_map->setDrawSuffix("Setting map entrance...\n\nUse [Arrow keys] or [W,A,S,D] to move the cursor and [Enter] set the map entrance.");
	_map->draw();
	while (settingEntrance) {
		int cursorX = _map->getCursor()->getX();
		int cursorY = _map->getCursor()->getY();
		unsigned char keypress = _getch();
		if (keypress == 0 || keypress == 0xE0) { // Arrow key presses require this first char to be ignored
			keypress = _getch();
		}
		switch (keypress) {
		case 'W':
		case 'w':
		case 72: // Arrow key UP
			if (cursorY > 0)
				_map->getCursor()->setY(cursorY - 1);
			break;
		case 'A':
		case 'a':
		case 75: // Arrow key LEFT
			if (cursorX > 0)
				_map->getCursor()->setX(cursorX - 1);
			break;
		case 'S':
		case 's':
		case 80: // Arrow key DOWN
			if (cursorY < (_map->getHeight() - 1))
				_map->getCursor()->setY(cursorY + 1);
			break;
		case 'D':
		case 'd':
		case 77: // Arrow key RIGHT
			if (cursorX < (_map->getWidth() - 1))
				_map->getCursor()->setX(cursorX + 1);
			break;
		case '\r':
			if ((cursorX == 0 || cursorX == _map->getWidth() - 1 || cursorY == 0 || cursorY == _map->getHeight() - 1) &&
				(_map->getCell(cursorX,cursorY)->getSprite() == '#')) {
				_map->setEntry(cursorX, cursorY);
				settingEntrance = false;
			}
			break;
		}
	}
	_map->setCursor(nullptr);
	_map->draw();
}

void MapBuilder::buildExit() {
	std::cout << "Set the map entrance location." << std::endl;
	bool settingEntrance = true;
	Cursor* editorCursor = new Cursor();
	CursorObserver cursorObserver(editorCursor, _map);
	_map->setCursor(editorCursor);
	_map->setDrawSuffix("Setting map exit...\n\nUse [Arrow keys] or [W,A,S,D] to move the cursor and [Enter] set the map exit.");
	_map->draw();
	while (settingEntrance) {
		int cursorX = _map->getCursor()->getX();
		int cursorY = _map->getCursor()->getY();
		unsigned char keypress = _getch();
		if (keypress == 0 || keypress == 0xE0) { // Arrow key presses require this first char to be ignored
			keypress = _getch();
		}
		switch (keypress) {
		case 'W':
		case 'w':
		case 72: // Arrow key UP
			if (cursorY > 0)
				_map->getCursor()->setY(cursorY - 1);
			break;
		case 'A':
		case 'a':
		case 75: // Arrow key LEFT
			if (cursorX > 0)
				_map->getCursor()->setX(cursorX - 1);
			break;
		case 'S':
		case 's':
		case 80: // Arrow key DOWN
			if (cursorY < (_map->getHeight() - 1))
				_map->getCursor()->setY(cursorY + 1);
			break;
		case 'D':
		case 'd':
		case 77: // Arrow key RIGHT
			if (cursorX < (_map->getWidth() - 1))
				_map->getCursor()->setX(cursorX + 1);
			break;
		case '\r':
			if ((cursorX == 0 || cursorX == _map->getWidth() - 1 || cursorY == 0 || cursorY == _map->getHeight() - 1) &&
				(_map->getCell(cursorX, cursorY)->getSprite() == '#')) {
				_map->setExit(cursorX, cursorY);
				settingEntrance = false;
			}
			break;
		}
	}
	_map->setCursor(nullptr);
	_map->draw();
}

void MapBuilder::buildLayout() {
}

void MapBuilder::buildNPCs() {
}

void MapBuilder::buildChests() {
}
