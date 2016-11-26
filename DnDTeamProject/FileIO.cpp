#include <fstream>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "FileIO.h"
#include "Menu.h"
#include "ItemArchive.h"
#include <conio.h>



//Load
std::vector<Character*> loadCharacters() {
	std::vector<Character*> characters;
	std::ifstream infilestream("saved_characters.txt");
	if (!(infilestream.peek() == std::ifstream::traits_type::eof())) {
		boost::archive::text_iarchive inarchive(infilestream);
		inarchive >> characters;
	}
	return characters;
}

ItemArchive loadItems() {
	ItemArchive loadedItems;
	std::ifstream infilestream("saved_items.txt");
	if (!(infilestream.peek() == std::ifstream::traits_type::eof())) {
		boost::archive::text_iarchive inarchive(infilestream);
		inarchive >> loadedItems;
	}
	return loadedItems;
}

std::vector<Map*> loadMaps() {
	std::vector<Map*> loadedMaps;
	std::ifstream infilestream("saved_maps.txt");
	if (!(infilestream.peek() == std::ifstream::traits_type::eof())) {
		boost::archive::text_iarchive inarchive(infilestream);
		inarchive >> loadedMaps;
	}
	for (int i = 0, n = loadedMaps.size(); i < n; ++i) {
		loadedMaps[i]->linkGridCells();
	}
	return loadedMaps;
}

std::vector<Campaign*> loadCampaigns() {
	std::vector<Campaign*> loadedCampaigns;
	std::ifstream infilestream("saved_campaigns.txt");
	if (!(infilestream.peek() == std::ifstream::traits_type::eof())) {
		boost::archive::text_iarchive inarchive(infilestream);
		inarchive >> loadedCampaigns;
	}
	for (int i = 0, n = loadedCampaigns.size(); i < n; ++i) {
		for (int j = 0, k = loadedCampaigns[i]->getCampaign().size(); j < k; ++j) {
			loadedCampaigns[i]->getCampaign()[j]->linkGridCells();
		}
	}
	return loadedCampaigns;
}



//Delete
void deleteCampaign() {
	std::vector<Campaign*> loadedCampaigns = loadCampaigns();
	if (loadedCampaigns.size() > 0) {
		std::vector<std::string> loadedCampaignsMenuOptions;
		for (int i = 0, n = loadedCampaigns.size(); i < n; ++i) {
			loadedCampaignsMenuOptions.push_back(loadedCampaigns[i]->getName() + ", " + std::to_string(loadedCampaigns[i]->getCampaign().size()) + " levels");
		}
		loadedCampaignsMenuOptions.push_back("Cancel");
		int deleteIndex = menu(loadedCampaignsMenuOptions, "Which campaign do you want to delete?") - 1;
		if (deleteIndex == loadedCampaignsMenuOptions.size() - 1)
			return;
		switch (menu(yesNoOptions, "Are you sure you want to delete " + loadedCampaigns[deleteIndex]->getName() + "?")) {
		case 1:
			loadedCampaigns.erase(loadedCampaigns.begin() + deleteIndex);
			saveCampaigns(loadedCampaigns);
			break;
		case 2:
			break;
		}
	}
	else {
		std::cout << "There are no saved campaigns to delete!" << std::endl << std::endl;
		std::cout << "Press any key to contimue..." << std::endl;
		_getch();
		system("cls");
	}
}


void deleteMap() {
	std::vector<Map*> loadedMaps = loadMaps();
	if (loadedMaps.size() > 0) {
		std::vector<std::string> loadedMapMenuOptions;
		for (int i = 0, n = loadedMaps.size(); i < n; ++i) {
			loadedMapMenuOptions.push_back(loadedMaps[i]->getName() + "\n" + loadedMaps[i]->drawToString());
		}
		loadedMapMenuOptions.push_back("Cancel");
		int deleteIndex = menu(loadedMapMenuOptions, "Which map do you want to delete?") - 1;
		if (deleteIndex == loadedMapMenuOptions.size() - 1)
			return;
		switch (menu(yesNoOptions, "Are you sure you want to delete " + loadedMaps[deleteIndex]->getName() + "?")) {
		case 1:
			loadedMaps.erase(loadedMaps.begin() + deleteIndex);
			saveMaps(loadedMaps);
			break;
		case 2:
			break;
		}
	}
	else {
		std::cout << "There are no saved maps to delete!" << std::endl << std::endl;
		std::cout << "Press any key to continue..." << std::endl;
		_getch();
		system("cls");
	}
}


void deleteCharacter() {
	std::vector<Character*> loadedCharacters = loadCharacters();
	if (loadedCharacters.size() > 0) {
		std::vector<std::string> loadedCharacterMenuOptions;
		for (int i = 0, n = loadedCharacters.size(); i < n; ++i) {
			loadedCharacterMenuOptions.push_back(loadedCharacters[i]->getName() + ", Level: " + std::to_string(loadedCharacters[i]->getLvl()));
		}
		loadedCharacterMenuOptions.push_back("Cancel");
		int deleteIndex = menu(loadedCharacterMenuOptions, "Which character do you want to delete?") - 1;
		if (deleteIndex == loadedCharacterMenuOptions.size() - 1)
			return;
		switch (menu(yesNoOptions, "Are you sure you want to delete " + loadedCharacters[deleteIndex]->getName() + "?")) {
		case 1:
			loadedCharacters.erase(loadedCharacters.begin() + deleteIndex);
			saveCharacters(loadedCharacters);
			break;
		case 2:
			break;
		}
	}
	else {
		std::cout << "There are no saved characters to delete!" << std::endl << std::endl;
		std::cout << "Press any key to continue..." << std::endl << std::endl;
		_getch();
		system("cls");
	}
}

void deleteItem() {
	std::vector<Item*> loadedItems = loadItems().getItemArchive();
	if (loadedItems.size() > 0) {
		std::vector<std::string> loadedItemMenuOptions;
		for (int i = 0, n = loadedItems.size(); i < n; ++i) {
			loadedItemMenuOptions.push_back(loadedItems[i]->toString());
		}
		loadedItemMenuOptions.push_back("Cancel");
		int deleteIndex = menu(loadedItemMenuOptions, "Which item do you want to delete?") - 1;
		if (deleteIndex == loadedItemMenuOptions.size() - 1)
			return;
		switch (menu(yesNoOptions, "Are you sure you want to delete " + loadedItems[deleteIndex]->getName() + "?")) {
		case 1:
			loadedItems.erase(loadedItems.begin() + deleteIndex);
			saveItems(loadedItems);
			break;
		case 2:
			break;
		}
	}
	else {
		std::cout << "There are no saved items to delete!" << std::endl << std::endl;
		std::cout << "Press any key to continue..." << std::endl << std::endl;
		_getch();
		system("cls");
	}
}



//Save
void saveCharacter(Character * character) {
	std::vector<Character*> appendedCharacters = loadCharacters();
	appendedCharacters.push_back(character);
	std::ofstream outfilestream("saved_characters.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << appendedCharacters;
	std::cout << character->getName() << " was saved!" << std::endl << std::endl;
}

void saveCharacters(std::vector<Character*> characters) {
	std::ofstream outfilestream("saved_characters.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << characters;
}

void saveItem(Item* item) {
	ItemArchive appendedItems = loadItems();
	appendedItems.addItem(item);
	std::ofstream outfilestream("saved_items.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << appendedItems;
}

void saveItems(std::vector<Item*> items) {
	ItemArchive itemArchive(items);
	std::ofstream outfilestream("saved_items.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << itemArchive;
}

void saveMap(Map* map) {
	std::vector<Map*> appendedMaps = loadMaps();
	appendedMaps.push_back(map);
	std::ofstream outfilestream("saved_maps.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << appendedMaps;
	std::cout << map->getName() << " was saved!" << std::endl << std::endl;
}
void saveMaps(std::vector<Map*> maps) {
	std::ofstream outfilestream("saved_maps.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << maps;
}

void saveCampaign(Campaign* campaign) {
	std::vector<Campaign*> appendedCampaigns = loadCampaigns();
	appendedCampaigns.push_back(campaign);
	std::ofstream outfilestream("saved_campaigns.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << appendedCampaigns;
	std::cout << campaign->getName() << " was saved!" << std::endl << std::endl;
}
void saveCampaigns(std::vector<Campaign*> campaigns) {
	std::ofstream outfilestream("saved_campaigns.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << campaigns;
}