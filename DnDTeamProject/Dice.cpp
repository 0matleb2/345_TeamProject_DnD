#include <iostream>
#include <time.h>
#include <regex>
#include <set>
#include <vector>

#include "Errors.h"
#include "dice.h"

bool Dice::isSeeded = false;

void Dice::seed()
{
	srand((unsigned)time(NULL));
	Dice::isSeeded = true;
}

int Dice::roll(const std::string input)
{
	std::cout << "\nRolling \"" << input << "\"" << std::endl;

	if (!isSeeded) { seed(); }

	std::regex rgx("^(\\(([+-]?)([0-9]+)\\))?([0-9]+)?[dD]([0-9]+)([+-][0-9]+)?$");
	std::smatch match;

	if (regex_search(input.begin(), input.end(), match, rgx)) {

		std::cout << "match[0] :" << match[0] << std::endl;
		std::cout << "match[1] :" << match[1] << std::endl;
		std::cout << "match[2] :" << match[2] << std::endl;
		std::cout << "match[3] :" << match[3] << std::endl;
		std::cout << "match[4] :" << match[4] << std::endl;
		std::cout << "match[5] :" << match[5] << std::endl;
		std::cout << "match[6] :" << match[6] << std::endl;
		std::cout << "match[7] :" << match[7] << std::endl;


		std::string advantage = match[2];
		int bestX = (match[3] == "") ? 1 : stoi(match[3]);
		int numDice = (match[4] == "") ? 1 : stoi(match[4]);
		int diceType = stoi(match[5]);
		int modifier = (match[6] == "") ? 0 : stoi(match[6]);

		std::set<int> validDice = { 1,4,6,8,10,12,20,100 };
		if (!(validDice.find(diceType) != validDice.end())) {
			fatalError("Invalid dice type passed to Dice::roll!");
		}
		if (bestX > numDice) {
			fatalError("Cannot take best " + std::to_string(bestX) + " of " + std::to_string(numDice) + " dice!");
		}

		std::vector<int> rolls;
		for (int i = 0; i < numDice; i++) {
			int roll = (rand() % diceType) + 1;
			std::cout << "Roll: " << roll << std::endl;
			rolls.push_back(roll);
		}

		std::sort(rolls.begin(), rolls.end()); //low to high
		if (advantage == "+" || advantage == "") {
			std::reverse(rolls.begin(), rolls.end());
		}

		for each (int i in rolls) {
			std::cout << i << ", ";
		}
		std::cout << std::endl;

		rolls.resize(bestX);

		int sum = modifier;
		for (int i = 0; i < rolls.size(); i++) {
			sum += rolls[i];
		}

		// Return the total modified roll, 0 if negative
		std::cout << "The total modified roll is " << sum << std::endl;
		return (sum > 0) ? sum : 0;
	}
	else {
		fatalError("Invalid string passed to Dice::roll");
		return -1;
	}
}