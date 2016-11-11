/*Header for my less-than-barebones implementation for Dice*/
#pragma once
#ifndef dice_include
#define dice_include
#include <string>

class Dice
{
public:
	static int roll(const std::string input);
	//int statRoll(std::string name, std::string attribute);
private:
	static bool isSeeded;
	static void seed();
};

#endif