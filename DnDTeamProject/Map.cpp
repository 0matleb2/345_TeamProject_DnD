#include <iostream>
#include <vector>

#include "Map.h"
#include "Observer.h"
#include "MapObserver.h"
#include "Errors.h"


//Default constructer initializes a map of size 16x9
Map::Map() {
	Map(16, 9);
}


//Parameterized constructor creates a map of given dimensions
Map::Map(const int w, const int h) {

	if (w < 3 || h < 3) {
		fatalError("Maps smaller than 3x3 cannot be created!");
	}

	width = w;
	height = h;

	//Cells are instantiated in the grid vector, it is one dimensional for simpilicity
	grid.reserve(w*h);
	for (int i = 0; i < w*h; i++) {
		grid.push_back(Cell(i%w, i / w));
	}

	//Basic map template is set (outer walls + entry + exit)
	for (unsigned int i = 0; i < grid.size(); i++) {
		if ((i%w == 0) || (i%w == w - 1) || (i / w == 0) || (i / w == h - 1)) {
			grid[i].setSprite('#');
		}
		else {
			grid[i].setSprite('.');
		}
	}
	setEntry(0, h / 2);
	setExit(w - 1, h / 2);

	//Link all cells in grid with adjacent cells
	for (int i = 0; i < (int)grid.size() - 1; i++) {
		//Link North
		if (i - width < 0) {
			grid[i].setNorth(nullptr);
		}
		else {
			grid[i].setNorth(&grid[i - width]);
		}
		//Link East
		if (i%width + 1 >(width - 1)) {
			grid[i].setEast(nullptr);
		}
		else {
			grid[i].setEast(&grid[i + 1]);
		}
		//Link South
		if (i + width > (width*height) - 1) {
			grid[i].setSouth(nullptr);
		}
		else {
			grid[i].setSouth(&grid[i + width]);
		}
		//Link West
		if (i%width - 1 < 0) {
			grid[i].setWest(nullptr);
		}
		else {
			grid[i].setWest(&grid[i - 1]);
		}
	}

	displayGrid();
}

//Destructor
Map::~Map()
{
	if (player)
		delete player;

	if (npcs.size() > 0)
	{
		for (int i = 0; i < npcs.size(); i++)
		{
			//delete npcs[i];
			//npcs[i] = nullptr;
		}
		npcs.clear();
	}

	if (loot.size() > 0)
	{
		for (int i = 0; i < loot.size(); i++)
		{
			//delete loot[i];
			//loot[i] = nullptr;
		}
		loot.clear();
	}
}


//Cell Inner class implementations
Map::Cell::Cell() {
	Map::Cell(0, 0);
}

Map::Cell::Cell(int x, int y) : _north(nullptr), _east(nullptr), _south(nullptr), _west(nullptr), _dfsVisited(false), _sprite('.'), _x(x), _y(y) {

}

Map::Cell::~Cell() {

}

char Map::Cell::getSprite() {
	return _sprite;
}
void Map::Cell::setSprite(char c) {
	_sprite = c;
}

int Map::Cell::getX() {
	return _x;
}
int Map::Cell::getY() {
	return _y;
}
void Map::Cell::setX(int x) {
	_x = x;
}
void Map::Cell::setY(int y) {
	_y = y;
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


//Validates the map by checking if a path exists between an entry and an exit
bool Map::validate() {
	return validate(entry);
}

bool Map::validate(Cell* vertex) {
	if (!entry || !exit) {
		return false;
	}
	//Iterative depth-first search algorithm with root: entry and goal: exit
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


//Sets the sprite of a target cell
void Map::setCell(int x, int y, char c) {
	grid[y*width + x].setSprite(c);
	notify();
}


void Map::setEntry(int x, int y) {
	grid[y*width + x].setSprite('/');
	entry = &grid[y*width + x];
}

void Map::setExit(int x, int y) {
	grid[y*width + x].setSprite('\\');
	exit = &grid[y*width + x];
}

//Displays the grid on the console
void Map::displayGrid() {
	int i = 0;
	int j = 0;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			std::cout << grid[(i*width) + j].getSprite();
		}
		std::cout << std::endl;
	}
}

std::vector<Map::Cell>* Map::getGrid() {
	return &grid;
}

void Map::addPC(Character* pc)
{
	if (player)
		delete player;

	player = new MapCharacter(entry->getX(), entry->getY(), pc, 'T');

	setCell(player->getX(), player->getY(), player->getSymbol());
}

MapCharacter* Map::getPC()
{
	return player;
}

void Map::addNPC(Character* npc, int x, int y, char sprite)
{
	if (grid[y*width + x].getSprite() != '.')
	{
		cout << "Failed to add npc. Cell occupied" << endl;
		return;
	}

	npcs.push_back(new MapCharacter(x, y, npc, sprite));

	setCell(x, y, sprite);
}

MapCharacter* Map::getNPC(int x, int y)
{
	if (npcs.size() < 1)
	{
		return nullptr;
	}

	for (int i = 0; i < npcs.size(); i++)
	{
		if (npcs[i]->getX() == x && npcs[i]->getY() == y)
			return npcs[i];
	}

	return nullptr;
}

void Map::printPC()
{
	player->print();
}

void Map::addLoot(ItemContainer* cont, int x, int y, char sprite)
{
	if (grid[y*width + x].getSprite() != '.')
	{
		cout << "Failed to add container. Cell Occupied" << endl;
		return;
	}

	loot.push_back(new MapContainer(x, y, cont, sprite));

	setCell(x, y, sprite);
}

MapContainer* Map::getLoot(int x, int y)
{
	if (loot.size() < 1)
	{
		return nullptr;
	}

	for (int i = 0; i < loot.size(); i++)
	{
		if (loot[i]->getX() == x && loot[i]->getY() == y)
			return loot[i];
	}

	return nullptr;
}

//! player has reached exit
bool Map::exitReached()
{
	if (player->getX() == exit->getX() && player->getY() == exit->getY())
		return true;

	return false;
}

void Map::examine(char dir)
{

	int x = getPC()->getX();
	int y = getPC()->getY();

	switch (dir)
	{
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

	cout << "Return to examine menu" << endl;
	system("PAUSE");
	notify();
}



void Map::rescale(int tgt_lvl)
{
	if (npcs.size() > 0)
	{
		for (int i = 0; i < npcs.size(); i++)
			npcs[i]->rescale(tgt_lvl);
	}

	if (loot.size() > 0)
	{
		for (int i = 0; i < loot.size(); i++)
			loot[i]->rescale(tgt_lvl);
	}
}

int Map::EntranceGetX()
{
	return entry->getX();
}

int Map::EntranceGetY()
{
	return entry->getY();
}

int Map::ExitGetX()
{
	return exit->getX();
}

int Map::ExitGetY()
{
	return exit->getY();
}

//! reset entrance
void Map::resetEntrance(int x, int y)
{
	entry->setSprite('#');
	setEntry(x, y);
	notify();
}

//! reset exit
void Map::resetExit(int x, int y)
{
	exit->setSprite('#');
	setExit(x, y);
	notify();
}

void Map::examine(int x, int y)
{
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		cout << "Cannot examine. Out of Bounds." << endl;
		return;
	}

	char mapSprite = grid[y*width + x].getSprite();
	// is it an empty floor tile?
	if (mapSprite == '.')
	{
		cout << "There is nothing here" << endl;
		return;
	}
	// is it a wall?
	if (mapSprite == '#')
	{
		cout << "This is a normal-looking wall." << endl;
		return;
	}
	//is it the entrance?
	if (mapSprite == '/')
	{
		cout << "This is the entrance." << endl;
		return;
	}
	// is it the exit?
	if (mapSprite == '\\')
	{
		cout << "This is the exit." << endl;
		return;
	}

	//check npc list for possible match
	if (npcs.size() > 0)
	{
		for (int i = 0; i < npcs.size(); i++)
		{
			if (npcs[i]->getX() == x && npcs[i]->getY() == y)
			{
				npcs[i]->print();
				return;
			}
		}
	}

	// check container list for possible match
	if (loot.size() > 0)
	{
		for (int i = 0; i < loot.size(); i++)
		{
			if (loot[i]->getX() == x && loot[i]->getY() == y)
			{
				loot[i]->print();
				return;
			}
		}
	}

	//no match found
	cout << "object unknown" << endl;
}

//! moves a character (playable or no) in desired direction
void Map::moveChar(MapCharacter* actor, char dir)
{
	// get current character coordinates
	int x = actor->getX();
	int y = actor->getY();

	Cell* temp = nullptr;

	switch (dir)
	{
		// up
	case 'n':
		// get north cell
		temp = grid[y*width + x].getNorth();

		// if north exists
		if (temp)
		{
			// if north is valid to move to
			if (temp->getSprite() == '.' || temp->getSprite() == '\\')
			{
				// change y coordinate to one north
				actor->setY(y - 1);
				// set char symbol at north
				temp->setSprite(actor->getSymbol());
				// set empty tile at previous location
				if (entry->getX() == x && entry->getY() == y)
					grid[y*width + x].setSprite('/');
				else
					grid[y*width + x].setSprite('.');
			}

		}

		// temp set to null after use
		temp = nullptr;

		notify();

		break;
		// left
	case 'w':
		// get west cell
		temp = grid[y*width + x].getWest();

		// if west exists
		if (temp)
		{
			// if west is valid to move to
			if (temp->getSprite() == '.' || temp->getSprite() == '\\')
			{
				// change x coordinate to one west
				actor->setX(x - 1);
				// set char symbol at west
				temp->setSprite(actor->getSymbol());
				// set empty tile at previous location
				if (entry->getX() == x && entry->getY() == y)
					grid[y*width + x].setSprite('/');
				else
					grid[y*width + x].setSprite('.');
			}

		}

		// temp set to null after use
		temp = nullptr;
		// update map
		notify();
		break;
		// right
	case 'e':
		// get east cell
		temp = grid[y*width + x].getEast();

		// if east exists
		if (temp)
		{
			// if east is valid to move to
			if (temp->getSprite() == '.' || temp->getSprite() == '\\')
			{
				// change x coordinate to one east
				actor->setX(x + 1);
				// set char symbol at east
				temp->setSprite(actor->getSymbol());
				// set empty tile at previous location
				if (entry->getX() == x && entry->getY() == y)
					grid[y*width + x].setSprite('/');
				else
					grid[y*width + x].setSprite('.');
			}

		}

		// temp set to null after use
		temp = nullptr;

		notify();
		break;
		// down
	case 's':
		// get south cell 
		temp = grid[y*width + x].getSouth();

		// if north exists
		if (temp)
		{
			// if north is valid to move to
			if (temp->getSprite() == '.' || temp->getSprite() == '\\')
			{
				// change y coordinate to one north
				actor->setY(y + 1);
				// set char symbol at north
				temp->setSprite(actor->getSymbol());
				// set empty tile at previous location
				if (entry->getX() == x && entry->getY() == y)
					grid[y*width + x].setSprite('/');
				else
					grid[y*width + x].setSprite('.');
			}

		}

		// temp set to null after use
		temp = nullptr;

		notify();
		break;
	default:
		break;
	}
}