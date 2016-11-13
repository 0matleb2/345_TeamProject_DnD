#pragma once
#include "Observer.h"
#include "Map.h"



class MapObserver: public Observer {

public:

	MapObserver(Map* model);
	~MapObserver();

	void update();

private:

	Map* _subject;
};

