#pragma once
#include <vector>
#include "Observable.h"
#include "MapCharacter.h"
#include "MapContainer.h"

class Observer;

class Map : public Observable {
public:
	// forward declaration
	class SearchCell;

	class Cell {

		public:
			Cell();
			Cell(int x, int y);
			~Cell();

			char getSprite();
			void setSprite(char c);

			int getX();
			int getY();
			void setX(int x);
			void setY(int y);

			// check if cells have same coordinates
			bool sameCell(Cell* c2);

			//used for A* alg
			int calcH(Cell* c2);
			bool isIn(std::vector<SearchCell>& v);

			Cell* getNorth();
			Cell* getEast();
			Cell* getSouth();
			Cell* getWest();
			bool getDfsVisited();
			void setNorth(Cell* cell);
			void setEast(Cell* cell);
			void setSouth(Cell* cell);
			void setWest(Cell* cell);
			void setDfsVisited(bool b);

		private:
			char _sprite;
			int _x;
			int _y;
			Cell* _north;
			Cell* _east;
			Cell* _south;
			Cell* _west;

			bool _dfsVisited; //Used by Map::validate()

			friend class boost::serialization::access;
			template<class Archive> void serialize(Archive & ar, const unsigned int version) {
				ar & _sprite;
			}
	};

	//! class used in the A* algorithm
	class SearchCell
	{
	public:
		SearchCell();
		// start node (no parent)
		SearchCell(Cell* c, int gv, int hv);
		// with parent
		SearchCell(Cell* c, SearchCell* p, int gv, int hv);
		~SearchCell();

		// getters
		Cell* getCell();
		SearchCell* getParent();
		int getG();
		int getH();

		int calcF();

		

	private:
		Cell* _cell;
		SearchCell* _parent;
		int _gValue;
		int _hValue;
	};

	Map();
	Map(int w, int h);
	~Map();

	Map::Cell* getEntry();
	Map::Cell* getExit();
	MapCharacter* getPC();
	MapCharacter* getNPC(int x, int y);
	MapContainer* getLoot(int x, int y);

	// get cell at (x, y)
	Map::Cell* getCell(int x, int y);

	void setCell(int x, int y, char c);
	void setEntry(int x, int y);
	void setExit(int x, int y);
	void addPC(Character* pc);
	void addNPC(Character* npc, int x, int y, char sprite);
	void addLoot(ItemContainer* cont, int x, int y, char sprite);

	void displayGrid();
	bool validate();
	void printPC();
	void moveCharacter(MapCharacter* actor, char direction);
	void moveChar(MapCharacter* actor, int x, int y);
	// allows playable character to get information on contents of adjacent tiles
	void examine(char dir);
	void examine(int x, int y);
	bool exitReached();
	void rescale(int tgt_lvl);

	// related to pathfinding

	// find smallest f value in a given vector
	int smallestF(std::vector<SearchCell>* v);
	
	//move npc 1 square towards target
	void advance(MapCharacter* actor, Cell* target);

private:

	std::vector<Cell> _grid;
	int _width;
	int _height;
	Cell* _entry;
	Cell* _exit;
	MapCharacter* _player;
	std::vector<MapCharacter*> _npcs;
	std::vector<MapContainer*> _itemContainers;


	bool validate(Cell* vertex);
	friend class boost::serialization::access;
	template<class Archive> void serialize(Archive & ar, const unsigned int version) {
		ar & _grid;
		ar & _width;
		ar & _height;
		ar & _entry;
		ar & _exit;
		ar & player;
		ar & npcs;
		ar & loot;
	}
};
