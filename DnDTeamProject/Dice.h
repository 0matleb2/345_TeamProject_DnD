#pragma once
#include <string>

class Dice
{
public:
	static int roll(const std::string input);
private:
	static bool isSeeded;
	static void seed();
};