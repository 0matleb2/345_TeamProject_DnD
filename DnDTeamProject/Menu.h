#pragma once
#include <vector>
#include <string>



extern int getUserInputInteger();
extern std::string getUserInputString();

extern int menu(std::vector<std::string> options);



static std::vector<std::string> characterBuilderNameOptions = {
	"Random name",
	"Custom name"
};

static std::vector<std::string> characterBuilderStatOptions = {
	"Generalist:\tNo preference",
	"Bully:\t\tStrength\t> Constitution\t> Dexterity",
	"Warrior:\t\tStrength\t> Dexterity\t> Constitution",
	"Berserker:\tDexterity\t> Strength\t> Constitution",
	"Nimble:\t\tDexterity\t> Constitution\t> Strength",
	"Tank:\t\tConstitution\t> Dexterity\t> Strength",
	"Vanguard:\tConstitution\t> Strength\t> Dexterity",
};