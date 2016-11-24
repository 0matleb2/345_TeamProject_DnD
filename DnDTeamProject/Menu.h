#pragma once
#include <vector>
#include <string>



extern int getUserInputInteger();
extern std::string getUserInputString();

extern int menu(std::vector<std::string> options, std::string title = "");



static std::vector<std::string> builderNameOptions = {
	"Random name",
	"Custom name"
};

static std::vector<std::string> characterBuilderStatOptions = {
	"Generalist:\tNo preference",
	"Bully:\t\tStrength\t> Constitution\t> Dexterity",
	"Warrior:\tStrength\t> Dexterity\t> Constitution",
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

static std::vector<std::string> characterBuilderInventoryOptions = {
	"Add an item",
	"Remove an item",
	"Create a new item",
	"Finished storing items"
};

static std::vector<std::string> characterBuilderReviewOptions = {
	"Change name",
	"Change equipped items",
	"Change inventory contents",
	"Finished building character"
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

static std::vector<std::string> mapBuilderChestOptions {
	"Add a saved item",
	"Add a new item",
	"Remove an item",
	"Finished filling chest"
};

static std::vector<std::string> campaignBuilderOptions {
	"Add a saved map",
	"Add a new map",
	"Remove a map",
	"Finished building campaign"
};

static std::vector<std::string> campaignEditorOptions{
	"Change name",
	"Add a new map",
	"Add a saved map",
	"Edit a map",
	"Remove a map",
	"View campaign",
	"Finished editing"
};

static std::vector<std::string> characterEditorMenuOptions{
	"Name",
	"Level",
	"Worn items",
	"Inventory",
	"Finished editing"
};

static std::vector<std::string> mapEditorMenuOptions{
	"Name",
	"Layout",
	"Finished editing"
};