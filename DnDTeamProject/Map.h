#pragma once
#include <vector>
#include "Observable.h"
#include "MapCharacter.h"
#include "MapContainer.h"

class Observer;

class Map : public Observable {
public:

	Map();
	Map(int w, int h);
	~Map();

	class Cell
	{
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

		// serialization

		friend class boost::serialization::access;

		template<class Archive> void serialize(Archive & ar, const unsigned int version)
		{
			ar & _sprite;
			ar & _x;
			ar & _y;

			ar & _north;
			ar & _south;
			ar & _east;
			ar & _west;
		}


	private:
		char _sprite;

		int _x;
		int _y;

		Cell* _north;
		Cell* _east;
		Cell* _south;
		Cell* _west;

		bool _dfsVisited; //Used by Map::validate()
	};

	bool validate();
	void setCell(int x, int y, char c);
	void setEntry(int x, int y);
	void setExit(int x, int y);
	void displayGrid();

	//reset entrance
	void resetEntrance(int x, int y);
	void resetExit(int x, int y);

	// add playable character
	void addPC(Character* pc);

	// get playable character
	MapCharacter* getPC();

	// print character details
	void printPC();

	// add npc to map
	void addNPC(Character* npc, int x, int y, char sprite);

	// return npc at given coordinates
	MapCharacter* getNPC(int x, int y);

	// add Item container to map
	void addLoot(ItemContainer* cont, int x, int y, char sprite);

	// return Item Container at given coordinates
	MapContainer* getLoot(int x, int y);

	// method to move a character
	void moveChar(MapCharacter* actor, char dir);

	// allows playable character to get information on contents of adjascent tiles
	void examine(char dir);
	void examine(int x, int y);

	//player reaches exit
	bool exitReached();

	// rescale map npcs/containers
	void rescale(int tgt_lvl);

	// get entrance / exit coords
	int EntranceGetX();
	int EntranceGetY();
	int ExitGetX();
	int ExitGetY();



	std::vector<Cell>* getGrid(); //Debugging

	//serialization

	friend class boost::serialization::access;

	template<class Archive> void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Observable>(*this);

		ar & grid;
		ar & width;
		ar & height;

		ar & entry;
		ar & exit;

		ar & player;
		ar & npcs;
		ar & loot;
	}

private:

	std::vector<Cell> grid;
	int width;
	int height;

	bool validate(Cell* vertex);

	Cell* entry;
	Cell* exit;

	// holds player character object, coords and symbol
	MapCharacter* player = nullptr;
	// list of npcs
	vector<MapCharacter*> npcs = vector<MapCharacter*>();
	// list of map loot
	vector<MapContainer*> loot = vector<MapContainer*>();
};
