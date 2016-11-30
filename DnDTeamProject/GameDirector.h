#pragma once
#include "Campaign.h"
#include "Character.h"
#include "Menu.h"



class GameDirector {

public:
	~GameDirector();
	static GameDirector* instance(); //Singleton pattern

	Character* getPlayerCharacter();
	Campaign* getCampaign();

	void setPlayerCharacter(Character* character);
	void setCampaign(Campaign* campaign);

	void mainMenu();

	//logging related
	
	// turn director logging on/off
	void logDir(bool choice);
	// set file to log to
	void setFile(std::string fileName);
	// get log filename
	std::string getFile();
	// log start of campaign
	void campaignStartLog();
	// log map loading
	void mapStartLog(std::string mapName);
	// log player/enemy phase switch
	void phaseLog(bool ePhase);
	// clear log file contents
	void clearLog();

private:

	GameDirector();

	static GameDirector* _gameDirectorInstance;

	Character* _playerCharacter;
	Campaign* _campaign;

	void playMenu();
	void creatorMenu();
	void credits();

	void startGame();

	bool playLevel(Character * playerCharacter, Map * level);

	void printLogo();

	// logging-related
	std::string _destination;
	bool _isLogging = false;
};