#include "Cursor.h"



Cursor::Cursor() : _x(0), _y(0) {
}


Cursor::~Cursor() {
}

int Cursor::getX() {
	return _x;
}

int Cursor::getY() {
	return _y;
}

void Cursor::setX(int x) {
	_x = x;
	notify();
}

void Cursor::setY(int y) {
	_y = y;
	notify();
}
