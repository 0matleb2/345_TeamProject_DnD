#include "Chest.h"



Chest::Chest() : ItemContainer(), _x(0), _y(0) {

}

Chest::Chest(int x, int y, int capacity) : ItemContainer(capacity), _x(x), _y(y) {
}

Chest::~Chest() {
}

int Chest::getX() {
	return _x;
}

int Chest::getY() {
	return _y;
}

void Chest::setX(int x) {
	_x = x;
}

void Chest::setY(int y) {
	_y = y;
}
