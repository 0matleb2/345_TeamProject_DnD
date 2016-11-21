#pragma once
#include "Observer.h"
#include "Map.h"


class CursorObserver : public Observer {

public:

	CursorObserver(Cursor* model, Map* context);
	~CursorObserver();

	void update();

private:

	Cursor* _model;
	Map* _context;

};

