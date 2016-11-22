#include <iostream>
#include <vector>

#include "Map.h"
#include "Observer.h"
#include "MapObserver.h"
#include "Errors.h"


Map::Map() {
}


Map::Map(const int w, const int h) {

	if (w < 3 || h < 3) {
		fatalError("Maps smaller than 3x3 cannot be created!");
	}

	_width = w;
	_height = h;

	//Cells are instantiated in the _grid vector, it is one dimensional for simpilicity
	_grid.reserve(w*h);
	for (int i = 0; i < w*h; i++) {
		_grid.push_back(Cell(i%w, i/w));
	}

	//Basic map template is set (outer walls + _entry + _exit)
	for (unsigned int i = 0; i < _grid.size(); i++) {
		if ((i%w == 0) || (i%w == w - 1) || (i / w == 0) || (i / w == h - 1)) {
			_grid[i].setSprite('#');
		}
		else {
			_grid[i].setSprite('.');
		}
	}
	setEntry(0, h / 2);
	setExit(w - 1, h / 2);

	//Link all cells in _grid with adjacent cells
	for (int i = 0; i < (int)_grid.size()-1; i++) {
		//Link North
		if (i - _width < 0) {
			_grid[i].setNorth(nullptr);
		}
		else {
			_grid[i].setNorth(&_grid[i - _width]);
		}
		//Link East
		if (i%_width + 1 > (_width - 1)) {
			_grid[i].setEast(nullptr);
		}
		else {
			_grid[i].setEast(&_grid[i + 1]);
		}
		//Link South
		if (i + _width > (_width*_height) - 1) {
			_grid[i].setSouth(nullptr);
		}
		else {
			_grid[i].setSouth(&_grid[i + _width]);
		}
		//Link West
		if (i%_width - 1 < 0) {
			_grid[i].setWest(nullptr);
		}
		else {
			_grid[i].setWest(&_grid[i - 1]);
		}
	}
}

Map::~Map() {
}


//Cell nested class
Map::Cell::Cell() {
}

Map::Cell::Cell(int x, int y) : _north(nullptr), _east(nullptr), _south(nullptr), _west(nullptr), _dfsVisited(false), _sprite('.'), _x(x), _y(y) {
}

Map::Cell::~Cell() {
}


//Cell accessors
char Map::Cell::getSprite() {
	return _sprite;
}
int Map::Cell::getX() {
	return _x;
}
int Map::Cell::getY() {
	return _y;
}
Map::Cell* Map::Cell::getNorth() {
	return _north;
}
Map::Cell* Map::Cell::getEast() {
	return _east;
}
Map::Cell* Map::Cell::getSouth() {
	return _south;
}
Map::Cell* Map::Cell::getWest() {
	return _west;
}
bool Map::Cell::getDfsVisited() {
	return _dfsVisited;
}

//Cell mutators
void Map::Cell::setSprite(char c) {
	_sprite = c;
}
void Map::Cell::setX(int x) {
	_x = x;
}
void Map::Cell::setY(int y) {
	_y = y;
}
void Map::Cell::setNorth(Map::Cell* cell) {
	_north = cell;
}
void Map::Cell::setEast(Map::Cell* cell) {
	_east = cell;
}
void Map::Cell::setSouth(Map::Cell* cell) {
	_south = cell;
}
void Map::Cell::setWest(Map::Cell* cell) {
	_west = cell;
}
void Map::Cell::setDfsVisited(bool b) {
	_dfsVisited = b;
} 
//End of Cell nested class


std::string Map::getName() {
	return _name;
}

int Map::getWidth() {
	return _width;
}

int Map::getHeight() {
	return _height;
}

Map::Cell* Map::getCell(int x, int y) {
	return &_grid[y*_width + x];
}

//Accessors
Map::Cell* Map::getEntry() {
	return _entry;
}
Map::Cell* Map::getExit() {
	return _exit;
}
Cursor * Map::getCursor() {
	return _cursor;
}
Character* Map::getPlayerCharacter() {
	return _playerCharacter;
}
std::vector<Character*> Map::getNpcCharacters() {
	return _npcCharacters;
}
std::vector<Chest*> Map::getChests() {
	return _chests;
}

std::string Map::getDrawSuffix() {
	return _drawSuffix;
}


void Map::setName(std::string name) {
	_name = name;
}

//Mutators
void Map::setCell(int x, int y, char c) {
	_grid[y*_width + x].setSprite(c);
	notify();
}
void Map::setEntry(int x, int y) {
	if(_entry)
		_entry->setSprite('#');
	_grid[y*_width + x].setSprite('/');
	_entry = &_grid[y*_width + x];
}
void Map::setExit(int x, int y) {
	if(_exit)
		_exit->setSprite('#');
	_grid[y*_width + x].setSprite('\\');
	_exit = &_grid[y*_width + x];
}
void Map::setCursor(Cursor * cursor) {
	_cursor = cursor;
}
void Map::setPlayerCharacter(Character* character) {
	_playerCharacter = character;
}
void Map::addNpcCharacter(Character* character) {
	if (std::find(_npcCharacters.begin(), _npcCharacters.end(), character) == _npcCharacters.end()) {
		_npcCharacters.push_back(character);
	}
}
void Map::removeNpcCharacter(Character* character) {
	int pos = std::find(_npcCharacters.begin(), _npcCharacters.end(), character) - _npcCharacters.begin();
	_npcCharacters.erase(_npcCharacters.begin() + pos);
}
void Map::addChest(Chest* container) {
	if (std::find(_chests.begin(), _chests.end(), container) == _chests.end()) {
		_chests.push_back(container);
	}
}
void Map::removeChest(Chest* container) {
	int pos = std::find(_chests.begin(), _chests.end(), container) - _chests.begin();
	_chests.erase(_chests.begin() + pos);
}

void Map::setDrawSuffix(std::string drawSuffix) {
	_drawSuffix = drawSuffix;
}

bool Map::isCellOccupied(int x, int y) {
	if (_playerCharacter && _playerCharacter->getX() == x && _playerCharacter->getY() == y)
		return true;
	for (int i = 0, n = _npcCharacters.size(); i < n; ++i) {
		if (_npcCharacters[i]->getX() == x && _npcCharacters[i]->getY() == y)
			return true;
	}
	for (int i = 0, n = _chests.size(); i < n; ++i) {
		if (_chests[i]->getX() == x && _chests[i]->getY() == y)
			return true;
	}
	return false;
}

//Validates the map by checking if a path exists between an _entry and an _exit
bool Map::validate() {
	return validate(_entry);
}
bool Map::validate(Cell* vertex) {
	if (!_entry || !_exit) {
		return false;
	}
	//Iterative depth-first search algorithm with root: _entry and goal: _exit
	std::vector<Cell*> stack;
	stack.push_back(vertex);
	while (!stack.empty()) {
		vertex = stack[stack.size() - 1];
		stack.pop_back();
		if (vertex->getSprite() == '\\') {
			return true;
		}
		if (!vertex->getDfsVisited()) {
			vertex->setDfsVisited(true);
			if (vertex->getNorth() && !vertex->getNorth()->getDfsVisited() && vertex->getSprite() != '#') {
				stack.push_back(vertex->getNorth());
			}
			if (vertex->getSouth() && !vertex->getSouth()->getDfsVisited() && vertex->getSprite() != '#') {
				stack.push_back(vertex->getSouth());
			}
			if (vertex->getWest() && !vertex->getWest()->getDfsVisited() && vertex->getSprite() != '#') {
				stack.push_back(vertex->getWest());
			}
			if (vertex->getEast() && !vertex->getEast()->getDfsVisited() && vertex->getSprite() != '#') {
				stack.push_back(vertex->getEast());
			}
		}
	}
	return false;
}

void Map::draw() {
	std::vector<char> drawBuffer;
	for (int i = 0, n = _grid.size(); i < n; ++i) {
		drawBuffer.push_back(_grid[i].getSprite());
	}
	if (_playerCharacter) {
		drawBuffer[_playerCharacter->getY() * _width + _playerCharacter->getX()] = '@';
	}
	if (_npcCharacters.size() > 0) {
		for (int i = 0, n = _npcCharacters.size(); i < n; ++i) {
			drawBuffer[_npcCharacters[i]->getY() * _width + _npcCharacters[i]->getX()] = '&';
		}
	}
	if (_chests.size() > 0) {
		for (int i = 0, n = _chests.size(); i < n; ++i) {
			drawBuffer[_chests[i]->getY() * _width + _chests[i]->getX()] = 'B';
		}
	}
	if (_cursor) {
		drawBuffer[_cursor->getY() * _width + _cursor->getX()] = '_';
	}

	system("CLS");

	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			std::cout << drawBuffer[i*_width + j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << _drawSuffix << std::endl;
}

std::string Map::drawToString() {
	std::vector<char> drawBuffer;
	for (int i = 0, n = _grid.size(); i < n; ++i) {
		drawBuffer.push_back(_grid[i].getSprite());
	}
	if (_playerCharacter) {
		drawBuffer[_playerCharacter->getY() * _width + _playerCharacter->getX()] = '@';
	}
	if (_npcCharacters.size() > 0) {
		for (int i = 0, n = _npcCharacters.size(); i < n; ++i) {
			drawBuffer[_npcCharacters[i]->getY() * _width + _npcCharacters[i]->getX()] = '&';
		}
	}
	if (_chests.size() > 0) {
		for (int i = 0, n = _chests.size(); i < n; ++i) {
			drawBuffer[_chests[i]->getY() * _width + _chests[i]->getX()] = 'B';
		}
	}

	std::string stringOutput;
	for (int i = 0, n = drawBuffer.size(); i < n; ++i) {
		if (i % _width == 0)
			stringOutput += '\t';
		stringOutput += drawBuffer[i];
		if (i % _width == _width - 1)
			stringOutput += '\n';
	}
	return stringOutput;
}

