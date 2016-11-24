#include <fstream>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "FileIO.h"
#include "ItemArchive.h"



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

void deleteCampaign(Campaign* campaign) {
	std::vector<Campaign*> loadedCampaigns = loadCampaigns();
	for (int i = 0, n = loadedCampaigns.size(); i < n; ++i) {
		if (loadedCampaigns[i] == campaign)
			loadedCampaigns.erase(loadedCampaigns.begin() + i);
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
	std::cout << item->getName() << " was saved!" << std::endl << std::endl;
}

void saveItems(std::vector<Item*> items) {
	std::ofstream outfilestream("saved_items.txt");
	boost::archive::text_oarchive outarchive(outfilestream);
	outarchive << items;
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