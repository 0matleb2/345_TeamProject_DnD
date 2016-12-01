#pragma once
#include <iostream>
#include "Menu.h"




int getUserInputInteger() {
	while (true) {
		int tmp;
		std::cin >> tmp;
		if (!std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			fflush(stdin);
			return tmp;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		fflush(stdin);
		std::cout << std::endl << "Invalid input!" << std::endl;
	}
}



std::string getUserInputString() {
	std::string tmp;
	getline(std::cin, tmp);
	std::cin.clear();
	fflush(stdin);
	std::cout << std::endl;
	return tmp;
}



int menu(std::vector<std::string> options, std::string title) {
	if (title != "") {
		std::cout << "[?] " << title << std::endl;
	}
	for (int i = 0, n = options.size(); i < n; ++i) {
		std::cout << "   [" << i + 1 << "]\t" << options[i] << std::endl;
	}
	while (true) {
		std::cout << "Choose an option: ";
		std::string choice = getUserInputString();
		try {
			unsigned int intChoice = std::stoi(choice);
			if (intChoice >= 1 && intChoice <= options.size()) {
				system("cls");
				return intChoice;
			}
			else {
				std::cout << "Invalid choice. Out of range!" << std::endl;
				continue;
			}
		}
		catch (const std::exception& e) {
			(void)e;
		}
		if (options[0].substr(0, 3) == "Yes") {
			if (choice == "y" || choice == "Y") {
				system("cls");
				return 1;
			}
			if (choice == "n" || choice == "N") {
				system("cls");
				return 2;
			}
		}
		std::cout << "Invalid choice. Unrecognized input!" << std::endl;
	}
}
