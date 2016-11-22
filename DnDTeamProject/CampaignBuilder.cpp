#include "CampaignBuilder.h"
#include "Menu.h"
#include "Names.h"
#include "Dice.h"
#include "FileIO.h"
#include "MapBuilder.h"




CampaignBuilder::CampaignBuilder() {
}


CampaignBuilder::~CampaignBuilder() {
}

Campaign* CampaignBuilder::getCampaign() {
	return _campaign;
}

void CampaignBuilder::construct() {
	_campaign = new Campaign();
	std::cout << "Creating a new campaign..." << std::endl << std::endl;
	buildName();
	buildCampaign();

}

void CampaignBuilder::buildName() {
	std::string mapName;
	bool choosingRandomName = true;
	std::cout << "What is the campaign called?" << std::endl;
	switch (menu(builderNameOptions)) {
	case 1:
		while (choosingRandomName) {
			mapName = campaignNames[Dice::roll("d" + std::to_string((campaignNames.size()))) - 1];
			std::cout << "The campaign is called " << mapName << std::endl << std::endl;
			std::cout << "Are you happy with this campaign name?" << std::endl;
			if (menu(yesNoOptions) == 1) {
				choosingRandomName = false;
				_campaign->setName(mapName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		_campaign->setName(getUserInputString());
		std::cout << "The campaign is called " << _campaign->getName() << "." << std::endl << std::endl;
		break;
	}
}

void CampaignBuilder::buildCampaign() {
	bool buildingCampaign = true;
	while (buildingCampaign) {
		std::cout << "Add some maps to the campagin." << std:: endl;
		std::vector<Map*> loadedMaps, campaignMaps;
		std::vector<std::string> loadedMapMenuOptions, campaignMapMenuOptions;
		MapBuilder mapBuilder;
		switch (menu(campaignBuilderOptions)) {
		case 1: //Add a saved map
			loadedMaps = loadMaps();
			if (loadedMaps.size() > 0) {
				std::cout << "Which map do you want to add?" << std::endl;
				for (int i = 0, n = loadedMaps.size(); i < n; ++i) {
					loadedMapMenuOptions.push_back(loadedMaps[i]->getName() + '\n' + loadedMaps[i]->drawToString());
				}
				_campaign->addMap(loadedMaps[menu(loadedMapMenuOptions) - 1]);
			}
			break;
		case 2: //Add a new map
			mapBuilder.construct();
			_campaign->addMap(mapBuilder.getMap());
			break;
		case 3: //Remove a map
			campaignMaps = _campaign->getCampaign();
			if (campaignMaps.size() > 0) {
				std::cout << "Which map do you want to remove?" << std::endl;
				for (int i = 0, n = campaignMaps.size(); i < n; ++i) {
					campaignMapMenuOptions.push_back(campaignMaps[i]->getName() + '\n' + campaignMaps[i]->drawToString());
				}
				_campaign->removeMap(menu(campaignMapMenuOptions) - 1);
			}
			break;
		case 4: //Finished
			buildingCampaign = false;
			saveCampaign(_campaign);
			break;
		}
	}
}
