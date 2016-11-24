#pragma once
#include "Campaign.h"


class CampaignEditor {

public:

	CampaignEditor();
	~CampaignEditor();

	Campaign* getCampaign();

	void setCampaign(Campaign* campaign);

	void editCampaign();
	void loadCampaign();

private:

	Campaign* _campaign;
	std::vector<Campaign*> _loadedCampaigns;

};

