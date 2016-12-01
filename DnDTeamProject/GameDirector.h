#pragma once
#include "Campaign.h"
#include "Character.h"
#include "Menu.h"

#include "CursorObserver.h"



class GameDirector {

public:
	~GameDirector();
	static GameDirector* instance(); //Singleton pattern

	Character* getPlayerCharacter();
	Campaign* getCampaign();

	void setPlayerCharacter(Character* character);
	void setCampaign(Campaign* campaign);

	void mainMenu();
	
private:

	GameDirector();

	static GameDirector* _gameDirectorInstance;

	Character* _playerCharacter;
	std::vector<Character*> _loadedCharacters;
	Campaign* _campaign;

	void playMenu();
	void creatorMenu();
	void credits();

	void startGame();

	bool playLevel(Character * playerCharacter, Map * level);

	void printLogo();

	//actions
	Map::Cell* selectMode(Map* lvl);

};