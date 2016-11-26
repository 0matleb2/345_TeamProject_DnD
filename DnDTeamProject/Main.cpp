#include <iostream>
#include <fstream>
#include <vector>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "Character.h"
#include "ItemBuilder.h"
#include "ItemArchive.h"
#include "FileIO.h"
#include "CampaignEditor.h"
#include "MapEditor.h"
#include "CharacterEditor.h"
#include "Menu.h"
#include "GameDirector.h"
#include <Windows.h>
#include <conio.h>




int main(int argc, char** argv) { 
	
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL);

	GameDirector::instance()->mainMenu();
}


