#pragma once
#include "Observable.h"



class Cursor : public Observable {

public:
	Cursor();
	~Cursor();

	int getX();
	int getY();

	void setX(int x);
	void setY(int y);

private:

	int _x;
	int _y;

};


