#pragma once
#include "Campaign.h"
#include "Character.h"
#include "Menu.h"



class GameDirector {

public:
	~GameDirector();
	static GameDirector* instance(); //Singleton pattern

	Character* getPlayer();
	Campaign* getCampaign();

	void setPlayer(Character* character);
	void setCampaign(Campaign* campaign);

	void mainMenu();
	
private:

	GameDirector();

	static GameDirector* _gameDirectorInstance;

	Character* _player;
	std::vector<Character*> _loadedCharacters;
	Campaign* _campaign;

	void playMenu();
	void creatorMenu();
	void credits();

	void startGame();

	bool playLevel(Character * playerCharacter, Map * level);

	void printLogo();

};