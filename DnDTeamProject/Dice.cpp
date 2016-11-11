#include <iostream>
#include <time.h>
#include <regex>
#include <set>
#include "dice.h"

bool Dice::isSeeded = false;

void Dice::seed()
{
	srand((unsigned)time(NULL));
	Dice::isSeeded = true;
}

int Dice::roll(const std::string input)
{
	//std::cout << "Rolling \"" << input << "\"" << std::endl;

	// Rolling the pseudorandom number generator
	if (!isSeeded) { seed(); }

	std::regex rgx("^([0-9]+)?[dD]([0-9]+)([+-][0-9]+)?$");
	std::smatch match;

	if (regex_search(input.begin(), input.end(), match, rgx))
	{
		// Get number of dice from input match results, 1 if omitted in input
		int numDice = (match[1] == "") ? 1 : stoi(match[1]);

		// Get dice type from match results
		int diceType = stoi(match[2]);

		// Validate dice type
		std::set<int> validDice = { 4,6,8,10,12,20,100 };
		if (!(validDice.find(diceType) != validDice.end()))
		{
			//std::cout << "Invalid dice type" << std::endl;
			return -1;
		}

		// Get modifier from input match results, 0 if omitted, negative modifiers allowed
		int modifier = (match[3] == "") ? 0 : stoi(match[3]);

		// Sum individual dice rolls and modifier
		int sum = modifier;
		for (int i = 0; i < numDice; i++) {
			int roll = rand() % diceType + 1;
			//std::cout << "[Roll #" << i + 1 << ": " << roll << "] ";
			sum += roll;
		}

		// Return the total modified roll, 0 if negative
		//std::cout << "[Total Modified Roll: " << sum << "]" << std::endl;
		return (sum > 0) ? sum : 0;
	}
	else
	{
		//std::cout << "Invalid dice roll" << std::endl;
		return -1;
	}
}

/*int Dice::statRoll(std::string name, std::string attribute) {
	std::cout << "Rolling for character " << name << "'s " << attribute << " attribute." << std::endl;
	int roll_1 = roll("1d6");
	int roll_2 = roll("1d6");
	int roll_3 = roll("1d6");
	int highestThree[3] = { roll_1, roll_2, roll_3 };
	int lastRoll = roll("1d6");
	for (int i = 0; i < 2; i++) {
		if (lastRoll > highestThree[i]) {
			highestThree[i] = lastRoll;
			break;
		}
	}
	std::cout << "The best 3 rolls are " << highestThree[0] << ", " << highestThree[1] << ", and " << highestThree[2] << ", for a total of: "
		<< (highestThree[0] + highestThree[1] + highestThree[2]) << std::endl;
	return (highestThree[0] + highestThree[1] + highestThree[2]);
}*/