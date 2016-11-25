#pragma once
#include "Character.h"
#include "Item.h"
#include "Map.h"
#include "ItemArchive.h"
#include "Campaign.h"


extern std::vector<Character*> loadCharacters();
extern ItemArchive loadItems();
extern std::vector<Map*> loadMaps();
extern std::vector<Campaign*> loadCampaigns();

extern void deleteCampaign(Campaign* campaign);

extern void saveCharacter(Character* character);
extern void saveCharacters(std::vector<Character*> characters);
extern void saveItem(Item* item);
extern void saveItems(std::vector<Item*> items);
extern void saveMap(Map* map);
extern void saveMaps(std::vector<Map*> maps);
extern void saveCampaign(Campaign* campaign);
extern void saveCampaigns(std::vector<Campaign*> campaigns);

//logging-related
extern void writeLog(std::string line, std::string fileName);
extern void readLog(std::string fileName);