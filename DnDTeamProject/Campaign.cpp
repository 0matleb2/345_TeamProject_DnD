#include "Campaign.h"


Campaign::Campaign() {
}


Campaign::~Campaign() {
}

std::string Campaign::getName() {
	return _name;
}

std::vector<Map*>& Campaign::getCampaign() {
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

std::string Campaign::toString() {
	std::string s;
	s += "Campaign: " + _name + "\n\n";
	for (int i = 0, n = _campaign.size(); i < n; ++i) {
		s += "Level " + std::to_string(i + 1) + ": " + _campaign[i]->getName() + "\n";
		s += _campaign[i]->drawToString() + "\n";
	}
	return s;
}

bool Campaign::operator ==(const Campaign & campaign) const {
	return _name == campaign._name &&
		_campaign == campaign._campaign;
}
