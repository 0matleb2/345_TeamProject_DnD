#include "GameLogger.h"

GameLogger* GameLogger::_loggerInstance = new GameLogger();

GameLogger::GameLogger()
{

}

GameLogger::~GameLogger()
{

}

GameLogger* GameLogger::instance()
{
	if (!_loggerInstance)
		_loggerInstance = new GameLogger();

	return _loggerInstance;
}

void GameLogger::setPC(Character* pc)
{
	_loggedPC = new CharacterLogger(pc);
}

void GameLogger::setNPCs(std::vector<Character*>* npcs)
{
	if (npcs->size() != 0)
	{
		// add logger for all npcs in vector
		for (int i = 0; i < npcs->size(); i++)
		{
			_loggedNPCs->push_back(new CharacterLogger(npcs->at(i)));
		}
	}
}

void GameLogger::clearNPCs()
{
	_loggedNPCs->clear();
}

void GameLogger::setMap(Map* map)
{
	_loggedMap = new MapLogger(map);
}

//! given a map, sets the map, held pc and held npcs
void GameLogger::setAll(Map* map)
{
	setMap(map);
	setPC(map->getPlayerCharacter());
	//setNPCs(&map->getNpcCharacters());
}

void GameLogger::loggingPC(bool choice)
{
	_loggedPC->logging(choice);
}

void GameLogger::loggingNPCs(bool choice)
{
	if (_loggedNPCs->size() != 0)
	{
		for (int i = 0; i < _loggedNPCs->size(); i++)
		{
			_loggedNPCs->at(i)->logging(choice);
		}
	}
}

void GameLogger::loggingMap(bool choice)
{
	_loggedMap->logging(choice);
}

void GameLogger::loggingDice(bool choice)
{
	Dice::logging(choice);
}

void GameLogger::loggingAll(bool choice)
{
	loggingPC(choice);
	//loggingNPCs(choice);
	loggingMap(choice);
	loggingDice(choice);
}

void GameLogger::setFile(std::string fileName)
{
	_destination = fileName;

	_loggedPC->setFile(fileName);

	/*
	for (int i = 0; i < _loggedNPCs->size(); i++)
	{
		_loggedNPCs->at(i)->setFile(fileName);
	}
	*/
	_loggedMap->setFile(fileName);

	Dice::setFile(fileName);
}

std::string GameLogger::getFile()
{
	return _destination;
}

void GameLogger::printLog()
{
	readLog(_destination);
}