#pragma once

#include "Character.h"
#include "Observer.h"

#include "FileIO.h"

class CharacterLogger : public Observer
{
public:
	CharacterLogger(Character* c);
	~CharacterLogger();

	// update
	void update();

	// turn logging on/off
	void logging(bool choice);

	// set logging destination
	void setFile(std::string fileName);
private:
	Character* _model;
	bool _isLogging = true;
	std::string _destination;
};