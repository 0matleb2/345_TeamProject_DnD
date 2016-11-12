#include "MapObserver.h"
#include "Map.h"



MapObserver::MapObserver(Map* subject) : Observer() {
	
	_subject = subject;
	_subject->attach(this);
	
}

MapObserver::~MapObserver() {

}

void MapObserver::update() {
	_subject->displayGrid();
}

