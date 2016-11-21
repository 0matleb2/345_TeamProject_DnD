#pragma once
#include "Character.h"
#include "Item.h"
#include "ItemArchive.h"


extern std::vector<Character*> loadCharacters();
extern ItemArchive loadItems();
extern void loadMaps();

extern void saveCharacter(Character* character);
extern void saveItem(Item* item);
extern void saveMap();