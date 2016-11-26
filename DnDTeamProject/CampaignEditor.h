#pragma once
#include "Campaign.h"


class CampaignEditor {

public:

	CampaignEditor();
	~CampaignEditor();

	Campaign* getCampaign();

	void setCampaign(Campaign* campaign);

	void newCampaign();

	void editCampaign();
	void loadCampaign();
	void deleteCampaign();

private:

	Campaign* _campaign;
	std::vector<Campaign*> _loadedCampaigns;

};

