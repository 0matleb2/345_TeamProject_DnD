#include <time.h>
#include <regex>
#include <vector>

#include "Errors.h"
#include "dice.h"

bool Dice::_isSeeded = false;

int Dice::roll(const std::string input)
{

	if (!_isSeeded)
		seed();

	std::regex rgx("^(\\(([+-]?)([0-9]+)\\))?([0-9]+)?[dD]([0-9]+)([+-][0-9]+)?$");
	std::smatch match;

	if (regex_search(input.begin(), input.end(), match, rgx)) {

		std::string advantage = match[2];
		int bestX = (match[3] == "") ? 1 : stoi(match[3]);
		int numDice = (match[4] == "") ? 1 : stoi(match[4]);
		int diceType = stoi(match[5]);
		int modifier = (match[6] == "") ? 0 : stoi(match[6]);

		if (bestX > numDice) {
			fatalError("Cannot take best " + std::to_string(bestX) + " of " + std::to_string(numDice) + " dice!");
		}

		std::vector<int> rolls;
		for (int i = 0; i < numDice; i++) {
			int roll = (rand() % diceType) + 1;
			rolls.push_back(roll);
		}

		std::sort(rolls.begin(), rolls.end()); //low to high
		if (advantage == "+" || advantage == "") {
			std::reverse(rolls.begin(), rolls.end());
		}

		rolls.resize(bestX);

		int sum = modifier;
		for (int i = 0; i < rolls.size(); i++) {
			sum += rolls[i];
		}

		return (sum > 0) ? sum : 0;
	}
	else {
		fatalError("Invalid std::string passed to Dice::roll");
		return -1;
	}
}

void Dice::seed() {
	srand((unsigned)time(NULL));
	_isSeeded = true;
}