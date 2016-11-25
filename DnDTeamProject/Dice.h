#pragma once
#include <string>

#include "Observable.h"
#include "FileIO.h"

class Dice 
{

public:

	static int roll(const std::string input);

	static std::string getLog();

	static void logging(bool choice);

	static void setFile(std::string dest);

private:

	static bool _isSeeded;

	static void seed();

	//holds last line to be logged
	static std::string _lastLog;

	// turn logging on and off
	static bool _isLogging;

	// file to log to
	static std::string _destination;

};