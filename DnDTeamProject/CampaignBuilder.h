#pragma once
#include "Campaign.h"



class CampaignBuilder {

public:

	CampaignBuilder();
	~CampaignBuilder();

	Campaign* getCampaign();

	void construct();

private:

	Campaign* _campaign;

	void buildName();
	void buildCampaign();

};

