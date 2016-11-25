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




int main(int argc, char** argv) { 
	
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL);

	GameDirector::instance()->mainMenu();

}


