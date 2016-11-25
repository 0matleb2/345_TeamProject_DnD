#pragma once
#include <vector>
#include <boost/serialization/vector.hpp>
#include "Observable.h"
#include "Character.h"
#include "Chest.h"
#include "Cursor.h"

class Observer;

class Map : public Observable {
public:

	Map();
	Map(int w, int h);
	~Map();

	class SearchCell;

	class Cell {

	public:
		Cell();
		Cell(int x, int y);
		~Cell();


		char getSprite();
		int getX();
		int getY();
		Cell* getNorth();
		Cell* getEast();
		Cell* getSouth();
		Cell* getWest();
		bool getDfsVisited();

		void setSprite(char c);
		void setX(int x);
		void setY(int y);
		void setNorth(Cell* cell);
		void setEast(Cell* cell);
		void setSouth(Cell* cell);
		void setWest(Cell* cell);
		void setDfsVisited(bool b);

		// check if cells have same coordinates
		bool sameCell(Cell* c2);

		//used for A* alg
		int calcH(Cell* c2);
		bool isIn(std::vector<SearchCell*> v);

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
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version) {
			ar & _sprite;
			ar & _x;
			ar & _y;
		}

	};

	//! class used in the A* algorithm
	class SearchCell {

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

		// setters
		void setParent(SearchCell* np);
		void setG(int newg);
		

		int calcF();

	private:

		Cell* _cell;
		SearchCell* _parent;
		int _gValue;
		int _hValue;

	};

	std::string getName();
	int getWidth();
	int getHeight();
	Cell* getCell(int x, int y);
	Cell* getEntry();
	Cell* getExit();
	Cursor* getCursor();
	Character* getPlayerCharacter();
	std::vector<Character*> getNpcCharacters();
	std::vector<Chest*> getChests();
	std::string getDrawSuffix();


	void setName(std::string name);
	void setCell(int x, int y, char c);
	void setEntry(int x, int y);
	void setExit(int x, int y);
	void setCursor(Cursor* cursor);
	void setPlayerCharacter(Character*);
	void addNpcCharacter(Character*);
	void removeNpcCharacter(Character*);
	void addChest(Chest*);
	void removeChest(Chest*);
	void setDrawSuffix(std::string drawSuffix);
	bool isCellOccupied(int x, int y);

	bool validate();
	void draw();
	std::string drawToString();

	void linkGridCells();

	// related to pathfinding

	// find smallest f value in a given vector
	int smallestF(std::vector<SearchCell*>* v);

	// validation method using A* pathfinding alg
	bool validateA();

	// return a path from point A to B, if it exists
	std::vector<SearchCell*> findPath(Cell* start, Cell* end);

	// determine if one cell is within a certain range of another
	bool inRange(Cell* actor, Cell* target, int range);

	// return next cell to move to, given a valid (non-empty) path
	Cell* nextMove(Cell* start, Cell* end);

	// print out a path
	void printPath(std::vector<SearchCell*>* path);


	// for debugging
	void printVectorValidate(std::vector<SearchCell>* v, bool isopen);
	void printCellNeighbors(int x, int y);

	//barebones placeholder methods for moving, used to demo game logger
	void charMove(Character* actor);
	

	// getter for line to log
	std::string getLog();

private:

	std::string _name;
	std::vector<Cell> _grid;
	int _width;
	int _height;
	Cell* _entry;
	Cell* _exit;

	Cursor* _cursor = nullptr;
	Character* _playerCharacter = nullptr;
	std::vector<Character*> _npcCharacters;
	std::vector<Chest*> _chests;

	std::string _drawSuffix;

	// line to be logged
	std::string _lastLog = "none";


	bool validate(Cell* vertex);


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & _name;
		ar & _grid;
		ar & _width;
		ar & _height;
		ar & _entry;
		ar & _exit;
		ar & _npcCharacters;
		ar & _chests;
	}
};
