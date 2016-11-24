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

bool Map::Cell::isIn(std::vector<Map::SearchCell*> v)
{
	if (v.size() > 0)
	{
		for (int i = 0; i < v.size(); i++)
		{
			if (sameCell(v[i]->getCell()))
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

//! new validate method based on A* algorithm
bool Map::validateA()
{
	// gets a path from entry to exit
	std::vector<Map::SearchCell*> path = findPath(_entry, _exit);
	
	// if path is empty, invalid map
	if (path.size() == 0)
		return false;
	else
		return true;
}


//! returns the index of the smallest F value in a given vector, for use in A*
int Map::smallestF(std::vector<Map::SearchCell*>* v)
{
	int indexSmall = 0;

	for (int i = 0; i < v->size(); i++)
	{
		if (v->at(i)->calcF() < v->at(i)->calcF())
			indexSmall = i;
	}

	//std::cout << "smallest F found!" << std::endl;

	return indexSmall;
}

//! debugging: just prints the contents of a given A* open/closed list
void Map::printVectorValidate(std::vector<SearchCell>* v, bool isopen)
{
	
	if (isopen)
		std::cout << "OPEN vector:" << std::endl;
	else
		std::cout << "CLOSED vector" << std::endl;

	if (v->size() == 0)
		std::cout << "Empty" << std::endl;
	else
	{
		for (int i = 0; i < v->size(); i++)
		{
			std::cout << "Coords: x - " << v->at(i).getCell()->getX()
				<< " y - " << v->at(i).getCell()->getY() << std::endl;
		}
	}
}

//! debugging: prints out the coords of a cell's neighbors, incomplete, as i fixed my issue before finishing this
void Map::printCellNeighbors(int x, int y)
{
	Cell* temp = getCell(x, y);

	std::cout << "Cell: x - " << temp->getX() << " y - " << temp->getY() << std::endl;

	std::cout << "North: x -" << temp->getNorth()->getX() << " y - " << temp->getNorth()->getY() << std::endl;
}

//! pathfinding algorithm returns a path in the form of a vector, follow parent links from end to start
std::vector<Map::SearchCell*> Map::findPath(Cell* start, Cell* end)
{
	// open and closed lists
	std::vector<SearchCell*> closed = std::vector<SearchCell*>();
	std::vector<SearchCell*> open = std::vector<SearchCell*>();

	SearchCell* initial = new SearchCell(start, 0, start->calcH(end));

	open.push_back(initial);

	bool found = false;

	//while all nodes in open list have not been exausted
	while (open.size() != 0)
	{
		int current = smallestF(&open);
		// select a cell with smallest f-value
		
		// put selected cell in closed list
		closed.push_back(open[current]);
		// remove it from open list
		open.erase(open.begin() + current);

		// if last cell added to closed is destination
		if (closed.back()->getCell()->sameCell(end))
		{
			found = true;
			break;
		}
		else //add neighbord to open list
		{
			//SearchCell tmp;

			if (closed.back()->getCell()->getNorth())
			{
				// not already in closed list
				if (!closed.back()->getCell()->getNorth()->isIn(closed))
				{
					// not a wall
					if (closed.back()->getCell()->getNorth()->getSprite() != '#')
					{
						open.push_back(new SearchCell(closed.back()->getCell()->getNorth(), closed.back(),
							closed.back()->getG() + 1, closed.back()->getCell()->calcH(_exit)));

					}
				}
			}

			// repeat for all other directions
			// west cell exists
			if (closed.back()->getCell()->getWest())
			{
				// not already in closed list
				if (!closed.back()->getCell()->getWest()->isIn(closed))
				{
					// not a wall
					if (closed.back()->getCell()->getWest()->getSprite() != '#')
					{

						open.push_back(new SearchCell(closed.back()->getCell()->getWest(), closed.back(),
							closed.back()->getG() + 1, closed.back()->getCell()->calcH(_exit)));
					}
				}
			}

			// east cell exists
			if (closed.back()->getCell()->getEast())
			{
				// not already in closed list
				if (!closed.back()->getCell()->getEast()->isIn(closed))
				{
					// not a wall
					if (closed.back()->getCell()->getEast()->getSprite() != '#')
					{
						open.push_back(new SearchCell(closed.back()->getCell()->getEast(), closed.back(),
							closed.back()->getG() + 1, closed.back()->getCell()->calcH(_exit)));
					}
				}
			}

			// south cell exists
			if (closed.back()->getCell()->getSouth())
			{
				// not already in closed list
				if (!closed.back()->getCell()->getSouth()->isIn(closed))
				{
					// not a wall
					if (closed.back()->getCell()->getSouth()->getSprite() != '#')
					{


						// push into open list
						open.push_back(new SearchCell(closed.back()->getCell()->getSouth(), closed.back(),
							closed.back()->getG() + 1, closed.back()->getCell()->calcH(_exit)));
					}
				}
			}
		}
	}

	if (found)
	{
		// returns the closed vector, containing the path
		return closed;
	}
	else
	{
		// no valid path, returns an empty vector.
		return std::vector<SearchCell*>();
	}
}

//! for debugging, just prints out a path in reverse order
void Map::printPath(std::vector<Map::SearchCell*>* path)
{
	// if empty vector given, no valid path
	if (path->size() == 0)
	{
		std::cout << "No path available" << std::endl;
	}
	else
	{
		SearchCell* temp = path->back();

		SearchCell* temp2;

		std::cout << "Path: " << std::endl;

		// follow parent links back to start, stop when start is reached
		while (temp->getParent())
		{
			std::cout << "cell x = " << temp->getCell()->getX() << " y = " << temp->getCell()->getY() << std::endl;

			temp2 = temp->getParent();

			temp = temp2;
		}
		
		temp = nullptr;
		temp2 = nullptr;
	}
}

//! check if a certain cell is within a certain range of another
bool Map::inRange(Cell* actor, Cell* target, int range)
{
	//check for a path to the cell
	std::vector<Map::SearchCell*> path = findPath(actor, target);

	// no valid path, return false
	if (path.size() == 0)
		return false;
	else
	{
		// get G-value (total no of moves)
		int tgtR = path.back()->getG();

		// if g exceeds range, then target is not in range
		if (tgtR > range)
			return false;
		else
			return true;
	}
}

//! given a valid path, returns next cell to move to
//! for use with npcs, move to this cell to advance by 1
Map::Cell* Map::nextMove(Cell* start, Cell* end)
{
	std::vector<Map::SearchCell*> path = findPath(start, end);

	SearchCell* temp = path.back();
	SearchCell* temp2;

	while (true)
	{
		// if parent of cell is start, stop
		if (temp->getParent()->getCell()->sameCell(start))
			break;

		temp2 = temp->getParent();
		temp = temp2;
		
	}

	// return first cell in path
	return temp->getCell();
}