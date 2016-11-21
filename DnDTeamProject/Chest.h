#pragma once
#include "ItemContainer.h"



class Chest : public ItemContainer {

public:

	Chest();
	Chest(int x, int y, int capacity = 9);
	~Chest();

	int getX();
	int getY();

	void setX(int x);
	void setY(int y);

private:

	int _x;
	int _y;

};

