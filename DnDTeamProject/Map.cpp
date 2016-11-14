#include <iostream>
#include <vector>

#include "Map.h"
#include "Observer.h"
#include "MapObserver.h"
#include "Errors.h"

//[$] Start of Cell nested class
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

//! calculate H-value, used for A*
int Map::Cell::calcH(Cell* c2)
{
	int temp = abs(c2->getX() - _x) + abs(c2->getY() - _y);

	return temp;
}

bool Map::Cell::sameCell(Cell* c2)
{
	if (_x == c2->getX() && _y == c2->getY())
		return true;

	return false;
}

bool Map::Cell::isIn(std::vector<Map::SearchCell>& v)
{
	if (v.size() > 0)
	{
		for (int i = 0; i < v.size(); i++)
		{
			if (sameCell(v[i].getCell()))
				return true;
		}
	}

	return false;
}


//[X] End of Cell nested class

//[$] Start of SearchCell nested class

Map::SearchCell::SearchCell()
{

}

// used for start
Map::SearchCell::SearchCell(Cell* c, int gv, int hv) : _cell(c), _parent(nullptr), _gValue(gv), _hValue(hv)
{
	
}

// for all nodes except start
Map::SearchCell::SearchCell(Cell* c, SearchCell* p, int gv, int hv) : _cell(c), _parent(p), _gValue(gv), _hValue(hv)
{

}

Map::SearchCell::~SearchCell()
{

}

// getters

Map::Cell* Map::SearchCell::getCell()
{
	return _cell;
}

Map::SearchCell* Map::SearchCell::getParent()
{
	return _parent;
}

int Map::SearchCell::getG()
{
	return _gValue;
}

int Map::SearchCell::getH()
{
	return _hValue;
}

//! calculate F-value of cell
int Map::SearchCell::calcF()
{
	return (_gValue + _hValue);
}



//[X] End of SearchCell nested class


Map::Map() {
}

Map::Map(const int w, const int h) {

	if (w < 3 || h < 3) {
		fatalError("Maps smaller than 3x3 cannot be created!");
	}

	_width = w;
	_height = h;

	//Cells are instantiated in the grid std::vector, it is one dimensional for simpilicity
	_grid.reserve(w*h);
	for (int i = 0; i < w*h; i++) {
		_grid.push_back(Cell(i%w, i / w));
	}

	//Basic map template is set (outer walls with an entry and exit)
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
	for (int i = 0; i < (int)_grid.size() - 1; i++) {
		//Link North
		if (i - _width < 0) {
			_grid[i].setNorth(nullptr);
		}
		else {
			_grid[i].setNorth(&_grid[i - _width]);
		}
		//Link East
		if (i%_width + 1 >(_width - 1)) {
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

	displayGrid();
}

Map::~Map()
{
	if (_player)
		delete _player;

	if (_npcs.size() > 0)
	{
		for (int i = 0; i < _npcs.size(); i++)
		{
			//delete _npcs[i];
			//_npcs[i] = nullptr;
		}
		_npcs.clear();
	}

	if (_itemContainers.size() > 0)
	{
		for (int i = 0; i < _itemContainers.size(); i++)
		{
			//delete _itemContainers[i];
			//_itemContainers[i] = nullptr;
		}
		_itemContainers.clear();
	}
}


//Map accessors
Map::Cell* Map::getEntry() {
	return _entry;
}

Map::Cell* Map::getExit() {
	return _exit;
}

MapCharacter* Map::getPC() {
	return _player;
}

MapCharacter* Map::getNPC(int x, int y)
{
	if (_npcs.size() < 1)
	{
		return nullptr;
	}

	for (int i = 0; i < _npcs.size(); i++)
	{
		if (_npcs[i]->getX() == x && _npcs[i]->getY() == y)
			return _npcs[i];
	}

	return nullptr;
}

MapContainer* Map::getLoot(int x, int y)
{
	if (_itemContainers.size() < 1)
	{
		return nullptr;
	}

	for (int i = 0; i < _itemContainers.size(); i++)
	{
		if (_itemContainers[i]->getX() == x && _itemContainers[i]->getY() == y)
			return _itemContainers[i];
	}

	return nullptr;
}

Map::Cell* Map::getCell(int x, int y)
{
	if (x >= 0 && x < _width && y >= 0 && y < _height)
		return &_grid[y*_width + x];

	return nullptr;
}

//Map mutators
void Map::setCell(int x, int y, char c) {
	_grid[y*_width + x].setSprite(c);
	notify();
}

void Map::setEntry(int x, int y) {
	if (_entry != nullptr) {
		_entry->setSprite('#');
	}
	_grid[y*_width + x].setSprite('/');
	_entry = &_grid[y*_width + x];
	notify();
}

void Map::setExit(int x, int y) {
	if (_exit != nullptr) {
		_exit->setSprite('#');
	}
	_grid[y*_width + x].setSprite('\\');
	_exit = &_grid[y*_width + x];
	notify();
}

void Map::addPC(Character* pc)
{
	if (_player)
		delete _player;

	_player = new MapCharacter(_entry->getX(), _entry->getY(), pc, 'T');

	setCell(_player->getX(), _player->getY(), _player->getSymbol());
}

void Map::addNPC(Character* npc, int x, int y, char sprite)
{
	if (_grid[y*_width + x].getSprite() != '.')
	{
		std::cout << "Failed to add npc. Cell occupied" << std::endl;
		return;
	}

	_npcs.push_back(new MapCharacter(x, y, npc, sprite));

	setCell(x, y, sprite);
}

void Map::addLoot(ItemContainer* cont, int x, int y, char sprite) {
	if (_grid[y*_width + x].getSprite() != '.')
	{
		std::cout << "Failed to add container. Cell Occupied" << std::endl;
		return;
	}

	_itemContainers.push_back(new MapContainer(x, y, cont, sprite));

	setCell(x, y, sprite);
}



void Map::displayGrid() {
	int i = 0;
	int j = 0;
	for (i = 0; i < _height; i++) {
		for (j = 0; j < _width; j++) {
			std::cout << _grid[(i*_width) + j].getSprite();
		}
		std::cout << std::endl;
	}
}

//Validates the map by checking if a path exists between an entry and an exit
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

void Map::printPC() {
	_player->print();
}

void Map::moveCharacter(MapCharacter* actor, char direction) {
	// get current character coordinates
	int x = actor->getX();
	int y = actor->getY();

	Map::Cell* temp = nullptr;

	switch (direction) {

		// up
	case 'n':
		temp = _grid[y*_width + x].getNorth();
		if (temp) {
			// if north is valid to move to
			if (temp->getSprite() == '.' || temp->getSprite() == '\\') {
				// change y coordinate to one north
				actor->setY(y - 1);
				// set char symbol at north
				temp->setSprite(actor->getSymbol());
				// set empty tile at previous location
				if (_entry->getX() == x && _entry->getY() == y)
					_grid[y*_width + x].setSprite('/');
				else
					_grid[y*_width + x].setSprite('.');
			}
		}
		temp = nullptr;
		notify();
		break;

		// left
	case 'w':
		temp = _grid[y*_width + x].getWest();
		if (temp) {
			// if west is valid to move to
			if (temp->getSprite() == '.' || temp->getSprite() == '\\') {
				// change x coordinate to one west
				actor->setX(x - 1);
				// set char symbol at west
				temp->setSprite(actor->getSymbol());
				// set empty tile at previous location
				if (_entry->getX() == x && _entry->getY() == y)
					_grid[y*_width + x].setSprite('/');
				else
					_grid[y*_width + x].setSprite('.');
			}
		}
		temp = nullptr;
		notify();
		break;

		// right
	case 'e':
		temp = _grid[y*_width + x].getEast();
		if (temp) {
			// if east is valid to move to
			if (temp->getSprite() == '.' || temp->getSprite() == '\\') {
				// change x coordinate to one east
				actor->setX(x + 1);
				// set char symbol at east
				temp->setSprite(actor->getSymbol());
				// set empty tile at previous location
				if (_entry->getX() == x && _entry->getY() == y)
					_grid[y*_width + x].setSprite('/');
				else
					_grid[y*_width + x].setSprite('.');
			}
		}
		temp = nullptr;
		notify();
		break;

		// down
	case 's':
		temp = _grid[y*_width + x].getSouth();
		if (temp) {
			// if north is valid to move to
			if (temp->getSprite() == '.' || temp->getSprite() == '\\') {
				// change y coordinate to one north
				actor->setY(y + 1);
				// set char symbol at north
				temp->setSprite(actor->getSymbol());
				// set empty tile at previous location
				if (_entry->getX() == x && _entry->getY() == y)
					_grid[y*_width + x].setSprite('/');
				else
					_grid[y*_width + x].setSprite('.');
			}
		}
		temp = nullptr;
		notify();
		break;
	default:
		break;
	}
}

//! move a character to given coords
void Map::moveChar(MapCharacter* actor, int x, int y)
{
	for (int i = 0; i < _grid.size(); i++)
	{
		if (_grid[i].getX() == x && _grid[i].getY() == y)
		{
			// check if cell is open
			if (_grid[i].getSprite() == '.')
			{
				// set old cell to blank
				setCell(actor->getX(), actor->getY(), '.');

				// set actor's new coords
				actor->setX(x);
				actor->setY(y);

				// set symbol on new cell
				setCell(x, y, actor->getSymbol());
			}
		}
	}
}

void Map::examine(char direction) {

	int x = getPC()->getX();
	int y = getPC()->getY();

	switch (direction) {
	case 'n':
		examine(x, y - 1);
		break;
	case 'w':
		examine(x - 1, y);
		break;
	case 'e':
		examine(x + 1, y);
		break;
	case 's':
		examine(x, y + 1);
		break;
	default:
		break;
	}

	std::cout << "Return to examine menu" << std::endl;
	system("PAUSE");
	notify();
}

void Map::examine(int x, int y) {
	if (x < 0 || y < 0 || x >= _width || y >= _height) {
		std::cout << "Cannot examine. Out of Bounds." << std::endl;
		return;
	}

	char mapSprite = _grid[y * _width + x].getSprite();
	if (mapSprite == '.') {
		std::cout << "There is nothing here" << std::endl;
		return;
	}
	if (mapSprite == '#') {
		std::cout << "This is a normal-looking wall." << std::endl;
		return;
	}
	if (mapSprite == '/') {
		std::cout << "This is the entrance." << std::endl;
		return;
	}
	if (mapSprite == '\\') {
		std::cout << "This is the _exit." << std::endl;
		return;
	}

	//check npc list for possible match
	if (_npcs.size() > 0) {
		for (int i = 0; i < _npcs.size(); i++) {
			if (_npcs[i]->getX() == x && _npcs[i]->getY() == y)	{
				_npcs[i]->print();
				return;
			}
		}
	}

	// check container list for possible match
	if (_itemContainers.size() > 0)	{
		for (int i = 0; i < _itemContainers.size(); i++) {
			if (_itemContainers[i]->getX() == x && _itemContainers[i]->getY() == y)	{
				_itemContainers[i]->print();
				return;
			}
		}
	}

	//no match found
	std::cout << "object unknown" << std::endl;
}

bool Map::exitReached() {
	if (_player->getX() == _exit->getX() && _player->getY() == _exit->getY())
		return true;

	return false;
}

void Map::rescale(int targetLvl) {
	if (_npcs.size() > 0) {
		for (int i = 0; i < _npcs.size(); i++)
			_npcs[i]->rescale(targetLvl);
	}

	if (_itemContainers.size() > 0)
	{
		for (int i = 0; i < _itemContainers.size(); i++)
			_itemContainers[i]->rescale(targetLvl);
	}
}

void Map::advance(MapCharacter* actor, Cell* target)
{
	std::vector<SearchCell> closed = std::vector<SearchCell>();
	std::vector<SearchCell> open = std::vector<SearchCell>();

	Cell* startCell = getCell(actor->getX(), actor->getY());
	SearchCell initial = SearchCell(startCell, 0, startCell->calcH(target));

	open.push_back(initial);
	
	bool found = false;

	/*
	while (open.size() != 0)
	{
		int current = smallestF(&open);

		SearchCell temp
	}
	*/
}

int Map::smallestF(std::vector<Map::SearchCell>* v)
{
	int indexSmall = 0;

	for (int i = 0; i < v->size(); i++)
	{
		if (v->at(i).calcF() < v->at(i).calcF())
			indexSmall = i;
	}

	return indexSmall;
}