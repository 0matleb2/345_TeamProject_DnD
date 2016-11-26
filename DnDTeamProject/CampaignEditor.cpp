#include "CampaignEditor.h"
#include "Menu.h"
#include "FileIO.h"
#include "MapEditor.h"
#include "Names.h"
#include "Dice.h"
#include <conio.h>



CampaignEditor::CampaignEditor() : _loadedCampaigns(std::vector<Campaign*>()) {
}

CampaignEditor::~CampaignEditor() {
}

Campaign* CampaignEditor::getCampaign() {
	return _campaign;
}

void CampaignEditor::setCampaign(Campaign * campaign) {
	_campaign = campaign;
}


void CampaignEditor::newCampaign() {

	_campaign = new Campaign();

	std::cout << "Creating a new campaign..." << std::endl << std::endl;
	std::string campaignName;
	bool choosingRandomName = true;
	switch (menu(builderNameOptions, "What is the campaign called?")) {
	case 1:
		while (choosingRandomName) {
			campaignName = campaignNames[Dice::roll("d" + std::to_string((campaignNames.size()))) - 1];
			std::cout << "The campaign is called " << campaignName << std::endl << std::endl;
			if (menu(yesNoOptions, "Are you happy with this campaign name?") == 1) {
				choosingRandomName = false;
				_campaign->setName(campaignName);
			}
		}
		break;
	case 2:
		std::cout << "Enter a name: ";
		_campaign->setName(getUserInputString());
		std::cout << "The campaign is called " << _campaign->getName() << "." << std::endl << std::endl;
		break;
	}
	editCampaign();
}

void CampaignEditor::editCampaign() {

	bool editingCampaign = true;
	while (editingCampaign) {

		bool choosingRandomName = true;
		std::vector<Map*>& campaignMapsRef = _campaign->getCampaign();
		std::vector<Map*> campaignMaps, loadedMaps;
		std::vector<std::string> campaignMapsMenuOptions, loadedMapMenuOptions;
		MapEditor mapEditor;
		Map* newMap;
		int removeIndex, editIndex;
		std::string campaignName;

		std::cout << "Editing " << _campaign->getName() << "..." << std::endl << std::endl;
		switch (menu(campaignEditorOptions, "What do you want to do?")) {
		case 1: //Change name
			switch (menu(builderNameOptions, "What is the campaign called?")) {
			case 1:
				while (choosingRandomName) {
					campaignName = campaignNames[Dice::roll("d" + std::to_string((campaignNames.size()))) - 1];
					std::cout << "The campaign is called " << campaignName << std::endl << std::endl;
					if (menu(yesNoOptions, "Are you happy with this campaign name?") == 1) {
						choosingRandomName = false;
						_campaign->setName(campaignName);
					}
				}
				break;
			case 2:
				std::cout << "Enter a name: ";
				_campaign->setName(getUserInputString());
				std::cout << "The campaign is called " << _campaign->getName() << "." << std::endl << std::endl;
				break;
			}
			break;
		case 2: //Add a new map
			mapEditor.newMap();
			newMap = mapEditor.getMap();
			_campaign->addMap(newMap);
			system("cls");
			std::cout << newMap->getName() << " was saved and added to " << _campaign->getName() << "." << std::endl << std::endl;
			break;
		case 3: //Add a saved map
			loadedMaps = loadMaps();
			if (loadedMaps.size() > 0) {
				std::cout << "Which map do you want to add?" << std::endl;
				for (int i = 0, n = loadedMaps.size(); i < n; ++i) {
					loadedMapMenuOptions.push_back(loadedMaps[i]->getName() + '\n' + loadedMaps[i]->drawToString());
				}
				int addedMapIndex = menu(loadedMapMenuOptions) - 1;
				_campaign->addMap(loadedMaps[addedMapIndex]);
				std::cout << loadedMaps[addedMapIndex]->getName() << " was added to " << _campaign->getName() << "." << std::endl << std::endl;
			}
			else {
				std::cout << "There are no saved maps!" << std::endl;
			}
			break;
		case 4: //Edit a map
			if (campaignMapsRef.size() > 0) {
				for (int i = 0, n = campaignMapsRef.size(); i < n; ++i) {
					campaignMapsMenuOptions.push_back(campaignMapsRef[i]->getName() + "\n" + campaignMapsRef[i]->drawToString());
				}
				editIndex = menu(campaignMapsMenuOptions, "Which map do you want to edit?") - 1;
				mapEditor.setMap(campaignMapsRef[editIndex]);
				mapEditor.editMap();
			}
			else {
				std::cout << "This campaign does not have any maps yet!" << std::endl;
			}
			break;
		case 5: //Remove a map
			campaignMaps = _campaign->getCampaign();
			for (int i = 0, n = campaignMaps.size(); i < n; ++i) {
				campaignMapsMenuOptions.push_back(campaignMaps[i]->getName() + "\n" + campaignMaps[i]->drawToString());
			}
			removeIndex = menu(campaignMapsMenuOptions, "Which map do you want to remove?") - 1;
			std::cout << _campaign->getCampaign()[removeIndex]->getName() << " was removed from " << _campaign->getName() << "." << std::endl << std::endl;
			_campaign->removeMap(removeIndex);
			break;
		case 6: //View campaign
			std::cout << _campaign->toString() << "Press any key to continue." << std::endl;
			_getch();
			system("cls");
			break;
		case 7: //Finished
			editingCampaign = false;
			if (_loadedCampaigns.size() > 0)
				saveCampaigns(_loadedCampaigns);
			else
				saveCampaign(_campaign);
			std::cout << _campaign->getName() << " was saved!" << std::endl << std::endl;
			break;
		}
	}
}

bool CampaignEditor::loadCampaign() {
	_loadedCampaigns = loadCampaigns();
	if (_loadedCampaigns.size() > 0) {
		std::vector<std::string> loadedCampaignsMenuOptions;
		for (int i = 0, n = _loadedCampaigns.size(); i < n; ++i) {
			loadedCampaignsMenuOptions.push_back(_loadedCampaigns[i]->getName() + ", " + std::to_string(_loadedCampaigns[i]->getCampaign().size()) + 
				((_loadedCampaigns[i]->getCampaign().size() > 1) ? " levels" : " level"));
		}
		loadedCampaignsMenuOptions.push_back("Cancel");
		int editIndex = menu(loadedCampaignsMenuOptions, "Which campaign do you want to edit?") - 1;
		if (editIndex == loadedCampaignsMenuOptions.size() - 1)
			return false;
		_campaign = _loadedCampaigns[menu(loadedCampaignsMenuOptions, "Which campaign do you want to edit?") - 1];
		return true;
	}
	else {
		std::cout << "There are no saved campaigns to edit!" << std::endl << std::endl;
		std::cout << "Press any key to continue..." << std::endl;
		_getch();
		system("cls");
		return false;
	}
}
