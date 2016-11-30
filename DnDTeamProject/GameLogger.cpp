#include "GameLogger.h"

#include "GameDirector.h"

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
	if (!_loggedNPCs)
		return;

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
	setNPCs(&map->getNpcCharacters());
}

CharacterLogger* GameLogger::getPC()
{
	if (_loggedPC)
		return _loggedPC;
}

void GameLogger::loggingPC(bool choice)
{
	if (_loggedPC)
		_loggedPC->logging(choice);
}

void GameLogger::loggingNPCs(bool choice)
{
	if (_loggedNPCs)
	{
		if (_loggedNPCs->size() != 0)
		{
			for (int i = 0; i < _loggedNPCs->size(); i++)
			{
				_loggedNPCs->at(i)->logging(choice);
			}
		}
	}
}

void GameLogger::loggingMap(bool choice)
{
	if (_loggedMap)
		_loggedMap->logging(choice);
}

void GameLogger::loggingDice(bool choice)
{
	Dice::logging(choice);
}

void GameLogger::loggingAll(bool choice)
{
	loggingPC(choice);
	loggingNPCs(choice);
	loggingMap(choice);
	loggingDice(choice);
	loggingDir(choice);
}

void GameLogger::setFile(std::string fileName)
{
	_destination = fileName;

	if (_loggedPC)
		_loggedPC->setFile(fileName);

	if (_loggedNPCs)
	{
		for (int i = 0; i < _loggedNPCs->size(); i++)
		{
			_loggedNPCs->at(i)->setFile(fileName);
		}
	}

	if (_loggedMap)
		_loggedMap->setFile(fileName);

	Dice::setFile(fileName);

	if (_loggedDir)
		_loggedDir->setFile(fileName);
}

void GameLogger::setFile()
{
	if (_loggedDir)
	{
		setFile(_loggedDir->getFile());
	}
}

std::string GameLogger::getFile()
{
	return _destination;
}

void GameLogger::printLog()
{
	readLog(_destination);
}

void GameLogger::setDir(GameDirector* dir)
{
	_loggedDir = dir;
}

void GameLogger::loggingDir(bool choice)
{
	if (_loggedDir)
		_loggedDir->logDir(choice);
}