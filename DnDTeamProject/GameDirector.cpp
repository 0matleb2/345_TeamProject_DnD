#include <conio.h>
#include "GameDirector.h"
#include "FileIO.h"
#include "CampaignEditor.h"
#include "MapEditor.h"
#include "CharacterEditor.h"
#include "ItemBuilder.h"
#include "Dice.h"
#include "CharacterObserver.h"


GameDirector::GameDirector() {
}

void GameDirector::startGame() {
	for (int i = 0, n = _campaign->getCampaign().size(); i < n; ++i) {
		Map* level = _campaign->getCampaign()[i];
		bool levelComplete = false;
		while (!levelComplete) {
			level->setDrawPrefix("Level " + std::to_string(i + 1) + ": " + level->getName());
			levelComplete = playLevel(_player, level);
		}
		_player->levelUp();
		saveCharacters(_loadedCharacters);
	}
	system("cls");
	std::cout << "Congratulations! You have completed " << _campaign->getName() << std::endl;
}

bool GameDirector::playLevel(Character* player, Map* level) {
	level->setPlayerCharacter(player);
	CharacterObserver characterObserver(player, level);
	player->setX(level->getEntry()->getX());
	player->setY(level->getEntry()->getY());
	level->setDrawModeLOS(true);

	while (true) {

		level->setDrawSuffix("<Move Phase>\n\n" + std::to_string(3) + " moves remaining...\n\nUse [W, A, S, D] or [Arrow keys] to move.\nPress [Esc] to continue without moving.");

		for (int i = 0; i < 3; ++i) {
			level->draw();
			level->setDrawSuffix("<Move Phase>\n\n" + std::to_string(2-i) + " moves remaining...\n\nUse [W, A, S, D] or [Arrow keys] to move.\nPress [Esc] to continue without moving.");
			player->move(level);
			if (player->getX() == level->getExit()->getX() && player->getY() == level->getExit()->getY())
				goto exitReached;
		}
		Character* target = player->selectAttackTarget(level);
		if (target) {
			player->attack(target, level);
		}
	}
exitReached:
	return true;


}

void GameDirector::printLogo() {
	for (int i = 0, n = dndLogo.size(); i < n; ++i) {
		std::cout << dndLogo[i] << std::endl;
	}
}


GameDirector* GameDirector::_gameDirectorInstance = new GameDirector();

GameDirector::~GameDirector() {
}

GameDirector * GameDirector::instance() {
	if (!_gameDirectorInstance)
		_gameDirectorInstance = new GameDirector();

	return _gameDirectorInstance;
} 
Character * GameDirector::getPlayer() {
	return _player;
}

Campaign * GameDirector::getCampaign() {
	return _campaign;
}

void GameDirector::setPlayer(Character * player) {
	_player = player;
}

void GameDirector::setCampaign(Campaign * campaign) {
	_campaign = campaign;
}

void GameDirector::mainMenu() {

	bool onMainMenu = true;
	while (onMainMenu) {
		printLogo();
		switch (menu(mainMenuOptions)) {
		case 1:
			playMenu();
			break;
		case 2:
			creatorMenu();
			break;
		case 3:
			credits();
			system("cls");
			break;
		case 4:
			onMainMenu = false;
			break;
		}
	}
}

void GameDirector::playMenu() {

	bool onPlayMenu = true;
	while (onPlayMenu) {
		printLogo();
		std::vector<std::string> playMenuOptions;
		playMenuOptions.push_back("Campaign:\t" + (_campaign ? _campaign->getName() + ", " + std::to_string(_campaign->getCampaign().size()) + " levels" : ""));
		playMenuOptions.push_back("Character:\t" + (_player ? _player->getName() + ", Level: " + std::to_string(_player->getLvl()) : ""));
		playMenuOptions.push_back("Start game!");
		playMenuOptions.push_back("Create a new character");
		playMenuOptions.push_back("Return to main menu");

		std::vector<Campaign*> loadedCampaigns;
		std::vector<std::string> loadedCampaignMenuOptions;
		std::vector<std::string> loadedCharacterMenuOptions;
		CharacterEditor characterEditor;
		switch (menu(playMenuOptions, "Choose a campaign and a character to play")) {
		case 1:
			loadedCampaigns = loadCampaigns();
			if (loadedCampaigns.size() > 0) {
				for (int i = 0, n = loadedCampaigns.size(); i < n; ++i) {
					loadedCampaignMenuOptions.push_back(loadedCampaigns[i]->getName() + ", " + std::to_string(loadedCampaigns[i]->getCampaign().size()) + " levels");
				}
				loadedCampaignMenuOptions.push_back("Cancel");
				int playIndex = menu(loadedCampaignMenuOptions, "Which campaign do you want to play?") - 1;
				if (playIndex == loadedCampaignMenuOptions.size() - 1)
					break;
				_campaign = loadedCampaigns[playIndex];
			}
			else {
				std::cout << "There are no saved campaigns to play!" << std::endl;
			}
			break;
		case 2:
			_loadedCharacters = loadCharacters();
			if (_loadedCharacters.size() > 0) {
				for (int i = 0, n = _loadedCharacters.size(); i < n; ++i) {
					loadedCharacterMenuOptions.push_back(_loadedCharacters[i]->getName() + ", Level: " + std::to_string(_loadedCharacters[i]->getLvl()));
				}
				loadedCharacterMenuOptions.push_back("Cancel");
				
				int playIndex = menu(loadedCharacterMenuOptions, "Which character do you want to play?") - 1;
				if (playIndex == loadedCharacterMenuOptions.size() - 1)
					break;
				_player = _loadedCharacters[playIndex];
			}
			else {
				std::cout << "There are no saved characters to play!" << std::endl;
			}
			break;
		case 3:
			if (_player && _campaign) {
				startGame();
			}
			else {
				std::cout << "A character and a campaign must be selected to play!" << std::endl;
			}
			break;
		case 4:
			characterEditor.newCharacter();
			_player = characterEditor.getCharacter();
			break;
		case 5:
			onPlayMenu = false;
			break;
		}
	}
}

void GameDirector::creatorMenu() {
	
	bool onCreatorMenu = true;
	while (onCreatorMenu) {
		printLogo();
		CampaignEditor campaignEditor;
		MapEditor mapEditor;
		CharacterEditor characterEditor;
		ItemBuilder itemBuilder;
		switch (menu(creatorMenuOptions, "What do you want to do?")) {
		case 1: //Create a new campaign
			campaignEditor.newCampaign();
			break;
		case 2: //Create a new map
			mapEditor.newMap();
			break;
		case 3: //Create a new character
			characterEditor.newCharacter();
			break;
		case 4: //Create a mew item
			itemBuilder.newItem();
			break;
		case 5: //Edit an existing campaign
			if (campaignEditor.loadCampaign())
				campaignEditor.editCampaign();
			break;
		case 6: //Edit an exisiting map
			if (mapEditor.loadMap())
				mapEditor.editMap();
			break;
		case 7: //Edit an exisiting character
			if (characterEditor.loadCharacter())
				characterEditor.editCharacter();
			break;
		case 8: //Delete a saved campaign
			deleteCampaign();
			break;
		case 9: //Delete a saved map
			deleteMap();
			break;
		case 10: //Delete a saved character
			deleteCharacter();
			break;
		case 11: //Delete a saved item
			deleteItem();									
			break;
		case 12: //Return to main menu
			onCreatorMenu = false;
			break;
		}
	}
}

void GameDirector::credits() {

	for (int i = 0, n = encsLogo.size(); i < n; ++i) {
		std::cout << encsLogo[i] << std::endl;
	}

	std::cout << "\tConcordia University" << std::endl;
	std::cout << "\tFaculty of Engineering and Computer Science" << std::endl;
	std::cout << "\tDepartment of Computer Science & Software Engineering" << std::endl;
	std::cout << "\t1515 St. Catherine W., EV 3.139" << std::endl;
	std::cout << "\tMontreal, Quebec, Canada" << std::endl;
	std::cout << "\tH3G 2W1" << std::endl << std::endl;

	std::cout << "\tDeveloped for: " << std::endl << std::endl;
	std::cout << "\t\tCOMP 345" << std::endl;
	std::cout << "\t\tAdvanced Program Design with C++" << std::endl;
	std::cout << "\t\tInstructor: Dr. Mohamed Taleb" << std::endl;
	std::cout << "\t\tFall 2016" << std::endl << std::endl;

	std::cout << "\tDeveloped by:" << std::endl << std::endl;
	std::cout << "\t\tCharles Boudreau" << std::endl;
	std::cout << "\t\tEric Morgan" << std::endl;
	std::cout << "\t\tMathieu Leblanc" << std::endl;
	std::cout << "\t\tRobert Nguyen" << std::endl << std::endl << std::endl;

	std::cout << "Press any key to return to the Main Menu..." << std::endl;
	_getch();
}
