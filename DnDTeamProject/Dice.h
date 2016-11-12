#pragma once
#include <string>

class Dice {

public:

	static int roll(const std::string input);

private:

	static bool _isSeeded;

	static void seed();

};