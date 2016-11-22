#pragma once
#include <vector>
#include <boost/serialization/vector.hpp>
#include "Map.h"


class Campaign {

public:
	Campaign();
	~Campaign();

	std::string getName();
	std::vector<Map*> getCampaign();

	void setName(std::string name);
	void setCampaign(std::vector<Map*> campaign);
	void addMap(Map*);
	void removeMap(int index);

private:

	std::string _name;
	std::vector<Map*> _campaign;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & _name;
		ar & _campaign;
	}

};

