#pragma once
#include <vector>
#include "Observable.h"
#include "Character.h"
#include "Chest.h"
#include "Cursor.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>

class Observer;

class Map: public Observable {
public:
	
	Map();
	Map(int w, int h);
	~Map();

	class Cell	{

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
			}

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


private:
	
	std::string _name;
	std::vector<Cell> _grid;
	int _width;
	int _height;
	Cell* _entry;
	Cell* _exit;

	Cursor* _cursor;
	Character* _playerCharacter;
	std::vector<Character*> _npcCharacters;
	std::vector<Chest*> _chests;

	std::string _drawSuffix;


	bool validate(Cell* vertex);


	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & _grid;
		ar & _width;
		ar & _height;
		ar & _entry;
		ar & _exit;
	}
};
