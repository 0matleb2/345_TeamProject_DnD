#include "MapLogger.h"

MapLogger::MapLogger(Map* model) : Observer()
{
	_model = model;
	_model->attach(this);
}

MapLogger::~MapLogger()
{
	_model->detach(this);
}

void MapLogger::logging(bool choice)
{
	_isLogging = choice;
}

void MapLogger::update()
{
	if (_isLogging)
	{
		if (_model->getLog() != "none")
		{
			writeLog(_model->getLog(), _destination);
		}
	}
}

void MapLogger::setFile(std::string fileName)
{
	_destination = fileName;
}
