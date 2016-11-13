#pragma once
#include <vector>
#include "Observable.h"
#include "MapCharacter.h"
#include "MapContainer.h"

class Observer;

class Map : public Observable {
public:

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

	Map();
	Map(int w, int h);
	~Map();

	Map::Cell* getEntry();
	Map::Cell* getExit();
	MapCharacter* getPC();
	MapCharacter* getNPC(int x, int y);
	MapContainer* getLoot(int x, int y);

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
	// allows playable character to get information on contents of adjacent tiles
	void examine(char dir);
	void examine(int x, int y);
	bool exitReached();
	void rescale(int tgt_lvl);

private:

	std::vector<Cell> _grid;
	int _width;
	int _height;
	Cell* _entry;
	Cell* _exit;
	MapCharacter* _player;
	vector<MapCharacter*> _npcs;
	vector<MapContainer*> _itemContainers;


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
