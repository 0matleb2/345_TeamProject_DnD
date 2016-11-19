#pragma once
#include <vector>
#include <string>



extern int getUserInputInteger();
extern std::string getUserInputString();

extern int menu(std::vector<std::string> options);



static std::vector<std::string> builderNameOptions = {
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

static std::vector<std::string> itemBuilderTypeOptions = {
	"Armor",
	"Belt",
	"Boots",
	"Bracers",
	"Helmet",
	"Ring",
	"Shield",
	"Weapon"
};

static std::vector<std::string> itemBuilderArmorTypeOptions = {
	"Padded armor",
	"Leather armor",
	"Studded leather armor",
	"Chain shirt",
	"Breastplate",
	"Banded mail armor",
	"Half plate armor",
	"Full plate armor"
};

static std::vector<std::string> itemBuilderShieldTypeOptions = {
	"Buckler",
	"Heavy shield",
	"Tower shield"
};

static std::vector<std::string> itemBuilderWeaponTypeOptions = {
	"Longsword",
	"Longbow"
};

static std::vector<std::string> yesNoOptions = {
	"Yes",
	"No"
};