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
		_grid.push_back(Cell(i%w, i / w));
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

	linkGridCells();
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
bool Map::Cell::sameCell(Cell * c2) {
	if (_x == c2->getX() && _y == c2->getY())
		return true;
	return false;
}
int Map::Cell::calcH(Cell * c2) {
	int temp = abs(c2->getX() - _x) + abs(c2->getY() - _y);
	return temp;
}
bool Map::Cell::isIn(std::vector<SearchCell*> v) {
	if (v.size() > 0) {
		for (int i = 0; i < v.size(); i++) {
			if (sameCell(v[i]->getCell()))
				return true;
		}
	}
	return false;
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

std::string Map::getDrawPrefix() {
	return _drawPrefix;
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
	if (_entry)
		_entry->setSprite('#');
	_grid[y*_width + x].setSprite('/');
	_entry = &_grid[y*_width + x];
}
void Map::setExit(int x, int y) {
	if (_exit)
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

void Map::setDrawPrefix(std::string drawPrefix) {
	_drawPrefix = drawPrefix;
}

void Map::setDrawSuffix(std::string drawSuffix) {
	_drawSuffix = drawSuffix;
}

bool Map::isCellOccupied(int x, int y) {
	if (x < 0 || y < 0 || x > getWidth() - 1 || y > getHeight() - 1)
		return true;
	if (getCell(x, y)->getSprite() == '#')
		return true;
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
	for (int i = 0, n = _grid.size(); i < n; ++i) {
		_grid[i].setDfsVisited(false);
	}
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

	//Line of Sight implementation
	if (_isInPlay)
	{
		Cell* current;
		Cell* pcCell;
		int distance;
		
		// scan cells in buffer
		for (int i = 0; i < drawBuffer.size(); i++)
		{		
			// get current cell
			current = indexToCell(i);
			// get cell of player
			pcCell = getCell(_playerCharacter->getX(), _playerCharacter->getY());
			// calculate distance
			distance = current->calcH(pcCell);
			// "4" represents line of sight value. placeholder. dont know if you want an extra field in character or based on other stat
			if (distance > 4)
			{
				// value represents cell out of visual range
				drawBuffer[i] = 'X';
			}
		}

		current = nullptr;
		pcCell = nullptr;
	}

	if (_cursor) {
		drawBuffer[_cursor->getY() * _width + _cursor->getX()] = '_';
	}

	system("cls");

	std::cout << std::endl;
	if (_drawPrefix != "")
		std::cout << _drawPrefix << std::endl << std::endl;
	for (int i = 0; i < _height; ++i) {
		std::cout << "  ";
		for (int j = 0; j < _width; ++j) {
			std::cout << drawBuffer[i*_width + j];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	if (_drawSuffix != "")
		std::cout << _drawSuffix << std::endl << std::endl;
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

void Map::linkGridCells() {
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
}

int Map::smallestF(std::vector<SearchCell*>* v) {
	int indexSmall = 0;
	for (int i = 0; i < v->size(); i++) {
		if (v->at(i)->calcF() < v->at(i)->calcF())
			indexSmall = i;
	}
	//std::cout << "smallest F found!" << std::endl;
	return indexSmall;
}

bool Map::validateA() {
	// gets a path from entry to exit
	std::vector<Map::SearchCell*> path = findPath(_entry, _exit);

	// if path is empty, invalid map
	if (path.size() == 0)
		return false;
	else
		return true;
}

std::vector<Map::SearchCell*> Map::findPath(Cell * start, Cell * end) {
	// open and closed lists
	std::vector<SearchCell*> closed = std::vector<SearchCell*>();
	std::vector<SearchCell*> open = std::vector<SearchCell*>();

	SearchCell* initial = new SearchCell(start, 0, start->calcH(end));

	open.push_back(initial);

	bool found = false;

	//while all nodes in open list have not been exausted
	while (open.size() != 0) {
		int current = smallestF(&open);
		// select a cell with smallest f-value

		// put selected cell in closed list
		closed.push_back(open[current]);
		// remove it from open list
		open.erase(open.begin() + current);

		// if last cell added to closed is destination
		if (closed.back()->getCell()->sameCell(end)) {
			found = true;
			break;
		}
		else //add neighbord to open list
		{
			//SearchCell tmp;

			if (closed.back()->getCell()->getNorth()) {
				// not already in closed list
				if (!closed.back()->getCell()->getNorth()->isIn(closed)) {
					// not a wall
					if (closed.back()->getCell()->getNorth()->getSprite() != '#') {
						// if already in open list
						if (closed.back()->getCell()->getNorth()->isIn(open))
						{
							// working on complete solution
							
							for (int i = 0; i < open.size(); i++)
							{
								// find same cell
								if (closed.back()->getCell()->getNorth()->sameCell(open[i]->getCell()))
								{
									// if new path is faster, change current cell in path
									if (open[i]->getG() > closed.back()->getG() + 1)
									{
										open[i]->setG(closed.back()->getG() + 1);
										open[i]->setParent(closed.back());
									}
								}
							}
							
							
						}
						else
						{
							open.push_back(new SearchCell(closed.back()->getCell()->getNorth(), closed.back(),
								closed.back()->getG() + 1, closed.back()->getCell()->getNorth()->calcH(_exit)));
						}
					}
				}
			}

			// repeat for all other directions
			// west cell exists
			if (closed.back()->getCell()->getWest()) {
				// not already in closed list
				if (!closed.back()->getCell()->getWest()->isIn(closed)) {
					// not a wall
					if (closed.back()->getCell()->getWest()->getSprite() != '#') {
						// if already in open list
						if (closed.back()->getCell()->getWest()->isIn(open))
						{
							for (int i = 0; i < open.size(); i++)
							{
								// find same cell
								if (closed.back()->getCell()->getWest()->sameCell(open[i]->getCell()))
								{
									// if new path is faster, change current cell in path
									if (open[i]->getG() > closed.back()->getG() + 1)
									{
										open[i]->setG(closed.back()->getG() + 1);
										open[i]->setParent(closed.back());
									}
								}
							}
						}
						else
						{
							open.push_back(new SearchCell(closed.back()->getCell()->getWest(), closed.back(),
								closed.back()->getG() + 1, closed.back()->getCell()->getWest()->calcH(_exit)));
						}
					}
				}
			}

			// east cell exists
			if (closed.back()->getCell()->getEast()) {
				// not already in closed list
				if (!closed.back()->getCell()->getEast()->isIn(closed)) {
					// not a wall
					if (closed.back()->getCell()->getEast()->getSprite() != '#') {
						// if already in open list
						if (closed.back()->getCell()->getEast()->isIn(open))
						{
							for (int i = 0; i < open.size(); i++)
							{
								// find same cell
								if (closed.back()->getCell()->getEast()->sameCell(open[i]->getCell()))
								{
									// if new path is faster, change current cell in path
									if (open[i]->getG() > closed.back()->getG() + 1)
									{
										open[i]->setG(closed.back()->getG() + 1);
										open[i]->setParent(closed.back());
									}
								}
							}
						}
						else
						{
							open.push_back(new SearchCell(closed.back()->getCell()->getEast(), closed.back(),
								closed.back()->getG() + 1, closed.back()->getCell()->getEast()->calcH(_exit)));
						}
					}
				}
			}

			// south cell exists
			if (closed.back()->getCell()->getSouth()) {
				// not already in closed list
				if (!closed.back()->getCell()->getSouth()->isIn(closed)) {
					// not a wall
					if (closed.back()->getCell()->getSouth()->getSprite() != '#') {
						// if already in open list
						if (closed.back()->getCell()->getSouth()->isIn(open))
						{
							for (int i = 0; i < open.size(); i++)
							{
								// find same cell
								if (closed.back()->getCell()->getSouth()->sameCell(open[i]->getCell()))
								{
									// if new path is faster, change current cell in path
									if (open[i]->getG() > closed.back()->getG() + 1)
									{
										open[i]->setG(closed.back()->getG() + 1);
										open[i]->setParent(closed.back());
									}
								}
							}
						}
						else
						{
							open.push_back(new SearchCell(closed.back()->getCell()->getSouth(), closed.back(),
								closed.back()->getG() + 1, closed.back()->getCell()->getWest()->calcH(_exit)));
						}
					}
				}
			}
		}
	}

	if (found) {
		// returns the closed vector, containing the path
		return closed;
	}
	else {
		// no valid path, returns an empty vector.
		return std::vector<SearchCell*>();
	}
}

bool Map::inRange(Cell * actor, Cell * target, int range) {
	//check for a path to the cell
	std::vector<Map::SearchCell*> path = findPath(actor, target);

	// no valid path, return false
	if (path.size() == 0)
		return false;
	else {
		// get G-value (total no of moves)
		int tgtR = path.back()->getG();

		// if g exceeds range, then target is not in range
		if (tgtR > range)
			return false;
		else
			return true;
	}
}

Map::Cell* Map::nextMove(Cell * start, Cell * end) {
	std::vector<Map::SearchCell*> path = findPath(start, end);

	SearchCell* temp = path.back();
	SearchCell* temp2;

	while (true) {
		// if parent of cell is start, stop
		if (temp->getParent()->getCell()->sameCell(start))
			break;

		temp2 = temp->getParent();
		temp = temp2;

	}

	// return first cell in path
	return temp->getCell();;
}

void Map::printPath(std::vector<SearchCell*>* path) {
	// if empty vector given, no valid path
	if (path->size() == 0) {
		std::cout << "No path available" << std::endl;
	}
	else {
		SearchCell* temp = path->back();

		SearchCell* temp2;

		std::cout << "Path: " << std::endl;

		// follow parent links back to start, stop when start is reached
		while (temp->getParent()) {
			std::cout << "cell x = " << temp->getCell()->getX() << " y = " << temp->getCell()->getY() << std::endl;

			temp2 = temp->getParent();

			temp = temp2;
		}

		temp = nullptr;
		temp2 = nullptr;
	}
}

void Map::printVectorValidate(std::vector<SearchCell>* v, bool isopen) {
	if (isopen)
		std::cout << "OPEN vector:" << std::endl;
	else
		std::cout << "CLOSED vector" << std::endl;

	if (v->size() == 0)
		std::cout << "Empty" << std::endl;
	else {
		for (int i = 0; i < v->size(); i++) {
			std::cout << "Coords: x - " << v->at(i).getCell()->getX()
				<< " y - " << v->at(i).getCell()->getY() << std::endl;
		}
	}
}

void Map::printCellNeighbors(int x, int y) {
	Cell* temp = getCell(x, y);
	std::cout << "Cell: x - " << temp->getX() << " y - " << temp->getY() << std::endl;
	std::cout << "North: x -" << temp->getNorth()->getX() << " y - " << temp->getNorth()->getY() << std::endl;
}

//! return cell corresponding to given index number
Map::Cell* Map::indexToCell(int index)
{
	int x = index % _width;
	int y = index / _width;

	return getCell(x, y);
}

void Map::setPlay(bool choice)
{
	_isInPlay = choice;
}

Map::SearchCell::SearchCell() {
}

Map::SearchCell::SearchCell(Cell * c, int gv, int hv) : _cell(c), _parent(nullptr), _gValue(gv), _hValue(hv) {

}

Map::SearchCell::SearchCell(Cell * c, SearchCell * p, int gv, int hv) : _cell(c), _parent(p), _gValue(gv), _hValue(hv) {
}

Map::SearchCell::~SearchCell() {
}

Map::Cell* Map::SearchCell::getCell() {
	return _cell;
}

Map::SearchCell* Map::SearchCell::getParent() {
	return _parent;
}

int Map::SearchCell::getG() {
	return _gValue;
}

int Map::SearchCell::getH() {
	return _hValue;
}

int Map::SearchCell::calcF() {
	return _gValue + _hValue;
}

void Map::SearchCell::setParent(SearchCell* np)
{
	_parent = np;
}

void Map::SearchCell::setG(int newg)
{
	_gValue = newg;
}
