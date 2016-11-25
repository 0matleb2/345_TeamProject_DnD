#include "CharacterLogger.h"

CharacterLogger::CharacterLogger(Character* model) : Observer()
{
	_model = model;
	_model->attach(this);
}

CharacterLogger::~CharacterLogger()
{

}

void CharacterLogger::update()
{
	// check if logging is on
	if (_isLogging)
	{
		// if action is loggable
		if (_model->getLog() != "none")
		{
			writeLog(_model->getLog(), _destination);
		}
	}
}

//! turn logging on/off
void CharacterLogger::logging(bool choice)
{
	_isLogging = choice;
}

//! set log file destination
void CharacterLogger::setFile(std::string fileName)
{
	_destination = fileName;
}