#include "MapObserver.h"
#include "Map.h"



MapObserver::MapObserver(Map* model) : Observer() {
	_model = model;
	_model->attach(this);
}

MapObserver::~MapObserver() {

}

void MapObserver::update() {
	_model->draw();
}

