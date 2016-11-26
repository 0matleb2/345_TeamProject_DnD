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
#include "GameLogger.h"

int main(int argc, char** argv) { 
	
	/*
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL);

	GameDirector::instance()->mainMenu();
	*/
	
	GameLogger::instance();
	// turn off dice logging so character creation isnt registered
	GameLogger::instance()->loggingDice(false);

	Character* c1 = new Character();
	c1->setName("TestPC");

	Character* c2 = new Character();
	c2->setName("TestNPC1");

	Character* c3 = new Character();
	c3->setName("TestNPC2");

	Map* m1 = new Map(5, 5);
	
	m1->setPlayerCharacter(c1);
	m1->addNpcCharacter(c2);
	m1->addNpcCharacter(c3);

	GameLogger::instance()->setAll(m1);

	GameLogger::instance()->loggingAll(true);
	GameLogger::instance()->setFile("gameLoggerTest1.txt");
	
	Dice::roll("1d6");
	Dice::roll("2d8");
	c1->attack();
	//c2->attack();
	//c3->attack();
	m1->charMove(m1->getPlayerCharacter());
	
	GameLogger::instance()->loggingPC(false);

	m1->charMove(m1->getPlayerCharacter());
	//this should not log
	c1->attack();
	Dice::roll("1d12");

	GameLogger::instance()->printLog();

	system("PAUSE");

}


