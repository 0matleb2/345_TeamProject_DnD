#include <iostream>
#include <fstream>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "Character.h"
#include "CharacterBuilder.h"
#include "ItemBuilder.h"
#include "ItemArchive.h"
#include "FileIO.h"
#include "MapBuilder.h"


int main(int argc, char** argv) {

	/*
	std::cout << "<<< CHARACTER SAVE FILE CONTENTS >>>" << std::endl << std::endl;
	std::vector<Character*> loadedCharacters = loadCharacters();
	for (int i = 0, n = loadedCharacters.size(); i < n; ++i) {
		std::cout << loadedCharacters[i]->toString() << std::endl;
		std::cout << "##############################################################################" << std::endl << std::endl;
	}


	std::vector<Item*> loadedItems = loadItems().getItemArchive();
	std::cout << "<<< ITEM SAVE FILE CONTENTS >>>" << std::endl << std::endl;
	for (int i = 0, n = loadedItems.size(); i < n; ++i) {
		std::cout << loadedItems[i]->toString() << std::endl << std::endl;

	}
	std::cout << "##############################################################################" << std::endl << std::endl << std::endl;


	CharacterBuilder builder;
	builder.construct();

	*/


	MapBuilder mapBuilder;
	mapBuilder.construct();

	std::cout << std::endl << "Enter any key to exit program: ";
	getchar();
}