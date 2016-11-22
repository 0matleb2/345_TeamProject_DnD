#include "Campaign.h"



Campaign::Campaign() {
}


Campaign::~Campaign() {
}

std::string Campaign::getName() {
	return _name;
}

std::vector<Map*> Campaign::getCampaign() {
	return _campaign;
}

void Campaign::setName(std::string name) {
	_name = name;
}

void Campaign::setCampaign(std::vector<Map*> campaign) {
	_campaign = campaign;
}

void Campaign::addMap(Map* map) {
	_campaign.push_back(map);
}

void Campaign::removeMap(int index) {
	_campaign.erase(_campaign.begin() + index);
}
