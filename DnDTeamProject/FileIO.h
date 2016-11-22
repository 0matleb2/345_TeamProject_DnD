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

extern void saveCharacter(Character* character);
extern void saveItem(Item* item);
extern void saveMap(Map* map);
extern void saveCampaign(Campaign* campaign);