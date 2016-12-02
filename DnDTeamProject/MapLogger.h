#pragma once

#include <fstream>
#include "Map.h"
#include "Observer.h"

#include "FileIO.h"


class MapLogger : public Observer
{
public:
	MapLogger(Map* model);
	~MapLogger();

	void update();

	void logging(bool choice);

	void setFile(std::string fileName);

private:
	Map* _model;
	bool _isLogging = true;
	std::string _destination;
};
