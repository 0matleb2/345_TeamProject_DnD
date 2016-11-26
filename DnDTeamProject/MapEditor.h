#pragma once
#include "Map.h"


class MapEditor {

public:

	MapEditor();
	~MapEditor();

	Map* getMap();

	void setMap(Map* map);

	void newMap();
	void editMap();
	bool loadMap();

private:

	Map* _map;
	std::vector<Map*> _loadedMaps;

};

