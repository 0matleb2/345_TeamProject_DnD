#include <iostream>
#include <fstream>
#include <vector>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "Character.h"
#include "CharacterBuilder.h"
#include "ItemBuilder.h"
#include "ItemArchive.h"
#include "FileIO.h"
#include "MapBuilder.h"
#include "CampaignBuilder.h"
#include "CampaignEditor.h"
#include "MapEditor.h"
#include "CharacterEditor.h"
#include "Menu.h"
#include "GameDirector.h"
#include <Windows.h>

#include "Dice.h"
#include "CharacterLogger.h"

int main(int argc, char** argv) { 
	
	/*
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL);

	GameDirector::instance()->mainMenu();
	*/
	Dice::logging(false);

	Character c1 = Character();
	c1.setName("Test1");

	Character c2 = Character();
	c2.setName("Test2");

	CharacterLogger clog1 = CharacterLogger(&c1);
	CharacterLogger clog2 = CharacterLogger(&c2);

	clog1.setFile("charLog1.txt");
	clog2.setFile("charLog1.txt");

	c1.attack();
	c2.attack();
	c2.attack();

	clog2.logging(false);

	c2.attack();
	c1.attack();

	readLog("charLog1.txt");

	system("PAUSE");

}


