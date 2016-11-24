#include <iostream>
#include <fstream>
#include <vector>
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "Character.h"
#include "CharacterBuilder.h"
#include "ItemBuilder.h"
#include "ItemArchive.h"
#include "FileIO.h"
#include "MapBuilder.h"
#include "CampaignBuilder.h"
#include "CampaignEditor.h"
#include "MapEditor.h"
#include "CharacterEditor.h"


int main(int argc, char** argv) {

	CampaignEditor campaignEditor;
	campaignEditor.loadCampaign();
	campaignEditor.editCampaign();


	std::cout << std::endl << "End of program." << std::endl << "Enter any key to exit program: ";
	getchar();
}